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

#include <time.h>

/* Get/set the process' ability to use the timestamp counter instruction */
#ifndef PR_GET_TSC
#define PR_GET_TSC 25
#define PR_SET_TSC 26
# define PR_TSC_ENABLE		1   /* allow the use of the timestamp counter */
# define PR_TSC_SIGSEGV		2   /* throw a SIGSEGV instead of reading the TSC */
#endif

#define LOOPS 1024

const char *tsc_names[] = { [0] = "[not set]", [PR_TSC_ENABLE] = "PR_TSC_ENABLE", [PR_TSC_SIGSEGV] = "PR_TSC_SIGSEGV", };

void sigsegv_cb(int sig) {
	int tsc_val = 0;

	printf("[ SIG_SEGV ]\n");
	printf("prctl(PR_GET_TSC, &tsc_val); ");
	fflush(stdout);

	if (prctl(PR_GET_TSC, &tsc_val) == -1)
		perror("prctl");

	printf("tsc_val == %s\n", tsc_names[tsc_val]);
	printf("prctl(PR_SET_TSC, PR_TSC_ENABLE)\n");
	fflush(stdout);
	if (prctl(PR_SET_TSC, PR_TSC_ENABLE) == -1)
		perror("prctl");

	printf("clock_gettime() == ");
}

int main(int argc, char **argv) {
	int tsc_val = 0;
	struct timespec r1, r2, r3, r4, temp;
	struct timespec rs[LOOPS];
	int i, j;

//	signal(SIGSEGV, sigsegv_cb);
//	get_time(&temp);
//	printf("rdtsc() == %llu\n", (unsigned long long) temp.tv_nsec);
//	printf("prctl(PR_GET_TSC, &tsc_val); ");
//	fflush(stdout);
//
//	if (prctl(PR_GET_TSC, &tsc_val) == -1)
//		perror("prctl");
//
//	printf("tsc_val == %s\n", tsc_names[tsc_val]);
//	get_time(&temp);
//	printf("rdtsc() == %llu\n", (unsigned long long) temp.tv_nsec);
//	printf("prctl(PR_SET_TSC, PR_TSC_ENABLE)\n");
//	fflush(stdout);
//
//	if (prctl(PR_SET_TSC, PR_TSC_ENABLE) == -1)
//		perror("prctl");
//
//	get_time(&temp);
//	printf("rdtsc() == %llu\n", (unsigned long long) temp.tv_nsec);
//	printf("prctl(PR_SET_TSC, PR_TSC_SIGSEGV)\n");
//	fflush(stdout);
//
//	if (prctl(PR_SET_TSC, PR_TSC_SIGSEGV) == -1)
//		perror("prctl");
//
//	printf("clock_gettime() == ");
//	fflush(stdout);

	sleep(1); // make sure there is no I/O pending from this process
	get_time(&r1);
	get_time(&r2);
	get_time(&r3);
	get_time(&r4);
	usleep(10); // this (might) ensure that we have a full time quantum to execute in - as we get re-scheduled after the sleep
	// the next few instructions seem to get pre-loaded into i-cache so no loop here to do that
	get_time(&r1);
	get_time(&r2);
	get_time(&r3);
	get_time(&r4);

	printf("%llu %llu %llu %llu\n", (unsigned long long) r1.tv_nsec, (unsigned long long) r2.tv_nsec, (unsigned long long) r3.tv_nsec, (unsigned long long) r4.tv_nsec);
	printf("%llu %llu %llu\n", (unsigned long long) (r2.tv_nsec - r1.tv_nsec), (unsigned long long) (r3.tv_nsec - r2.tv_nsec), (unsigned long long) (r4.tv_nsec - r3.tv_nsec));

	printf("clock_gettime() == ");
	fflush(stdout);

	sleep(1);  // make sure there is no I/O pending from this process
	// use 2 loops to preload the i-cache and makes sure there will be no page faults on the rs array
	// if you don't, the first read takes 9 extra clock cycles on a Q6600 CPU
	for (j = 0; j < 2; j++) {
		usleep(10);
		for (i = 0; i < LOOPS; i++) {
			get_time(&rs[i]);
		}
	}

	for (i = 1; i < LOOPS; i++)
		printf("%llu ", (unsigned long long) rs[i].tv_nsec - rs[i - 1].tv_nsec);

	printf("\n");
	fflush(stdout);

	exit(EXIT_SUCCESS);
}

//  Get timer resolution
int get_time(struct timespec *timeStruct) {
	if (clock_gettime(CLOCK_MONOTONIC, timeStruct) == -1) {
		perror("clock getres");
		return 0;
	}
	return 1;
}

