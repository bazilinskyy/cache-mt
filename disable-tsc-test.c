/*
 * Tests for prctl(PR_GET_TSC, ...) / prctl(PR_SET_TSC, ...)
 *
 * Basic test to test behaviour of PR_GET_TSC and PR_SET_TSC
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <inttypes.h>

#include <cpuid.h>

#include <sys/prctl.h>
#include <linux/prctl.h>

/* Get/set the process' ability to use the timestamp counter instruction */
#ifndef PR_GET_TSC
#define PR_GET_TSC 25
#define PR_SET_TSC 26
# define PR_TSC_ENABLE		1   /* allow the use of the timestamp counter */
# define PR_TSC_SIGSEGV		2   /* throw a SIGSEGV instead of reading the TSC */
#endif

#define LOOPS 1024

const char *tsc_names[] =
{
	[0] = "[not set]",
	[PR_TSC_ENABLE] = "PR_TSC_ENABLE",
	[PR_TSC_SIGSEGV] = "PR_TSC_SIGSEGV",
};

uint64_t rdtsc() {
uint32_t lo, hi;
/* We cannot use "=A", since this would use %rax on x86_64 */
__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
return (uint64_t)hi << 32 | lo;
}

void sigsegv_cb(int sig)
{
	int tsc_val = 0;

	printf("[ SIG_SEGV ]\n");
	printf("prctl(PR_GET_TSC, &tsc_val); ");
	fflush(stdout);

	if ( prctl(PR_GET_TSC, &tsc_val) == -1)
		perror("prctl");

	printf("tsc_val == %s\n", tsc_names[tsc_val]);
	printf("prctl(PR_SET_TSC, PR_TSC_ENABLE)\n");
	fflush(stdout);
	if ( prctl(PR_SET_TSC, PR_TSC_ENABLE) == -1)
		perror("prctl");

	printf("rdtsc() == ");
}

int main(int argc, char **argv)
{
	int tsc_val = 0;
        unsigned long long r1, r2, r3, r4;
        unsigned long long rs[LOOPS];
        int i, j;

	signal(SIGSEGV, sigsegv_cb);

	printf("rdtsc() == %llu\n", (unsigned long long)rdtsc());
	printf("prctl(PR_GET_TSC, &tsc_val); ");
	fflush(stdout);

	if ( prctl(PR_GET_TSC, &tsc_val) == -1)
		perror("prctl");

	printf("tsc_val == %s\n", tsc_names[tsc_val]);
	printf("rdtsc() == %llu\n", (unsigned long long)rdtsc());
	printf("prctl(PR_SET_TSC, PR_TSC_ENABLE)\n");
	fflush(stdout);

	if ( prctl(PR_SET_TSC, PR_TSC_ENABLE) == -1)
		perror("prctl");

	printf("rdtsc() == %llu\n", (unsigned long long)rdtsc());
	printf("prctl(PR_SET_TSC, PR_TSC_SIGSEGV)\n");
	fflush(stdout);

	if ( prctl(PR_SET_TSC, PR_TSC_SIGSEGV) == -1)
		perror("prctl");

	printf("rdtsc() == ");
	fflush(stdout);

        sleep(1); // make sure there is no I/O pending from this process
        r1 = (unsigned long long)rdtsc();
        r2 = (unsigned long long)rdtsc();
        r3 = (unsigned long long)rdtsc();
        r4 = (unsigned long long)rdtsc();
        usleep(10); // this (might) ensure that we have a full time quantum to execute in - as we get re-scheduled after the sleep
        // the next few instructions seem to get pre-loaded into i-cache so no loop here to do that
        r1 = (unsigned long long)rdtsc();
        r2 = (unsigned long long)rdtsc();
        r3 = (unsigned long long)rdtsc();
        r4 = (unsigned long long)rdtsc();

	printf("%llu %llu %llu %llu\n", r1, r2, r3, r4);
	printf("%llu %llu %llu\n", (r2-r1), (r3-r2), (r4-r3) );

	printf("rdtsc() == ");
	fflush(stdout);

        sleep(1);  // make sure there is no I/O pending from this process
        // use 2 loops to preload the i-cache and makes sure there will be no page faults on the rs array
        // if you don't, the first read takes 9 extra clock cycles on a Q6600 CPU
        for (j=0; j<2; j++) {
           usleep(10);
           for (i=0; i<LOOPS; i++)
             rs[i] = rdtsc();
        }
 
        for (i=1; i<LOOPS; i++)
           printf("%llu ", rs[i]-rs[i-1]);

	printf("\n");
	fflush(stdout);

	exit(EXIT_SUCCESS);
}

