/*
 ============================================================================================
 Name        : hr_timer.c
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

 Description : Cross-platform high-resolution timer for performance measurements
 ============================================================================================
 */

#include "hr_timer.h"

// Get time in nanoseconds
int get_time_ns(struct timespec *timeStruct) {
	//TODO more hr function discussed by Brian, assembly code
	if (clock_gettime( CLOCK_MONOTONIC, timeStruct) == -1) {
		perror("clock gettime");
		return 0;
	}
	return 1;
}

//  Get timer resolution
int get_time_res(struct timespec *timeStruct) {
#ifndef __APPLE__
	if( clock_getres( CLOCK_MONOTONIC, timeStruct) == -1 ) {
		perror( "clock getres" );
		return 0;
	}
	return 1;
#else // Does not work on Mac OS
	return 0;
#endif
}

// Calculate a difference in nanoseconds between start and end.
unsigned long long calculate_time_ns(struct timespec start, struct timespec end) {
//	unsigned long long accum = ( timeStructFinish.tv_sec - timeStructStart.tv_sec ) + (double)( timeStructFinish.tv_nsec - timeStructStart.tv_nsec ) / (double)BILLION;
	struct timespec temp;
	if ((end.tv_nsec - start.tv_nsec) < 0) {
		temp.tv_sec = end.tv_sec - start.tv_sec - 1;
		temp.tv_nsec = BILLION + end.tv_nsec - start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec - start.tv_sec;
		temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}

	return BILLION * temp.tv_sec + temp.tv_nsec;
}

/*
 * Use RDTSC to measure time at nanosecond accuracy (if it is not disabled)
 * CPUID == 1 - use CPUID; CPUID == 1 - do not use CPUID
*/
unsigned long long rdtsc_old(int CPUID) {
	unsigned long a, b;
	unsigned long long temp;
	if (CPUID)
		__asm__ __volatile__("CPUID\nrdtsc" : "=a" (a), "=d" (b):: "memory", "%ebx", "%ecx");
	else
		__asm__ __volatile__("rdtsc" : "=a" (a), "=d" (b):: "memory", "%ebx", "%ecx");
	temp = b;
	temp = (temp << 32) | a;
	return temp;
}


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

void sigsegv_cb(int sig) {
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

}

// Calculate average time of running the experiment
unsigned long long average_time(unsigned long long *time, int timesRun) {
	if (timesRun == 0) // avoid division
		return 0;
	// Loop through times of all runs of the experiment
	int i;
	unsigned long long avTime = 0;
	for (i = 0; i < timesRun; ++i) {
		avTime += time[i];
	}
	return avTime / timesRun;
}

// Test clock_gettime
void test_clock_gettime(void) {
	struct timespec start1, start2, start3;
	get_time_ns(&start1);
	get_time_ns(&start2);
	get_time_ns(&start3);

	while (calculate_time_ns(start1, start2) == 0ull) {
		get_time_ns(&start2);
	}
	get_time_ns(&start3);
	while (calculate_time_ns(start2, start3) == 0ull) {
		get_time_ns(&start3);
	}

	printf("TIME. Time: %ld %ld %ld.", BILLION * start1.tv_sec + start1.tv_nsec,
	BILLION * start2.tv_sec + start2.tv_nsec,
	BILLION * start3.tv_sec + start3.tv_nsec);
	printf(" Diff: %llu %llu\n", calculate_time_ns(start1, start2), calculate_time_ns(start2, start3));
}

// Test clock_getres
void test_clock_getres(void) {
	struct timespec startres1;
	get_time_res(&startres1);
	printf("RESOLUTION. time: %ld\n",
	BILLION * startres1.tv_sec + startres1.tv_nsec);
}

// Test rdtsc
void test_rdtsc(void) {
	// With CPUID
	printf("TEST OF RDTSC with CPUID\n");

	unsigned long long t[32], prev;
	int i;
	for (i = 0; i < 32; i++)
		t[i] = rdtsc(1);

	prev = t[0];
	for (i = 1; i < 32; i++) {
		printf("%llu [%llu]\n", t[i], t[i] - prev);
		prev = t[i];
	}

	printf("Total=%llu\n", t[32 - 1] - t[0]);

	// Without CPUID
	printf("\nTEST OF RDTSC without CPUID\n");

	for (i = 0; i < 32; i++)
		t[i] = rdtsc(0);

	prev = t[0];
	for (i = 1; i < 32; i++) {
		printf("%llu [%llu]\n", t[i], t[i] - prev);
		prev = t[i];
	}

	printf("Total=%llu\n", t[32 - 1] - t[0]);
}
