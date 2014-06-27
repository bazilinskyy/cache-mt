/*
 ============================================================================================
 Name        : clock-gettime_test.c
 Author      : Pavlo Bazilinskyy
 Version     : 0.1
 Copyright   : Copyright (c) 2014, Pavlo Bazilinskyy <pavlo.bazilinskyy@gmail.com>
 School of Computer Science, National University of Ireland, Maynooth

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 Description: Test to estimate overhead of using clock_gettime(3)
 Run instructions: compile with gcc. No special flags needed.
 ============================================================================================
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

 #define LOOPS 1024 // Number of iterations to run in the test

 /*
 * Get/set the process' ability to use the timestamp counter instruction
 */
#ifndef PR_GET_TSC
#define PR_GET_TSC 25
#define PR_SET_TSC 26
# define PR_TSC_ENABLE		1   // Allow the use of the timestamp counter
# define PR_TSC_SIGSEGV		2   // Throw a SIGSEGV instead of reading the TSC
#endif

const char *tsc_names[] = { [0] = "[not set]", [PR_TSC_ENABLE] = "PR_TSC_ENABLE", [PR_TSC_SIGSEGV] = "PR_TSC_SIGSEGV", };

 /*
 * Detect segmenation. Not used
 */
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

/*
 * The main entry point of the programme. clock_gettime(3) is tested LOOPS number of times. Results are outputted on the console.
 */
int main(int argc, char **argv) {
	int tsc_val = 0;
	struct timespec r1, r2, r3, r4, temp;
	struct timespec rs[LOOPS]; // Array to store results.
	int i, j;

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

	sleep(1); // Make sure there is no I/O pending from this process
	
	// Use 2 loops to preload the i-cache and make sure there will be no page faults on the rs array
	// If this is not doe, the first read will tkae a number of extra clock cycles.
	for (j = 0; j < 2; j++) {
		for (i = 0; i < LOOPS; i++) {
			get_time(&rs[i]);
		}
	}

	for (i = 1; i < LOOPS; i++)
		printf("%llu ", (unsigned long long) rs[i].tv_nsec - rs[i - 1].tv_nsec); // Output results
	printf("\n");

	// Finish
	fflush(stdout);
	exit(EXIT_SUCCESS);
}

/*
 * Get time with clock_gettime.
 */
int get_time(struct timespec *timeStruct) {
	if (clock_gettime(CLOCK_MONOTONIC, timeStruct) == -1) {
		perror("clock getres");
		return 0;
	}
	return 1;
}