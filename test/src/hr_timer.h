/*
 ============================================================================================
 Name        : hr_timer.h
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

 Description : Header for the cross-platform high-resolution timer for performance measurements
 ============================================================================================
 */
#ifndef HR_TIMER_H_
#define HR_TIMER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <limits.h>
#ifdef __APPLE__
	#include "clock_gettime_mac.h"
#elif __linux // For future use
    // linux
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif
#include "conf.h"

// For RDTSC. Not supported by Mac OS.
#if TIMING == RDTSC
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
uint64_t rdtsc(); //  Get time with rdtsc. new version
void sigsegv_cb(int sig);
#endif

// Get time in nanoseconds
int get_time_ns(struct timespec *timeStruct);
// Get time resolution
int get_time_res(struct timespec *timeStruct);
// From http://stackoverflow.com/questions/13950290/clock-gettime-nanoseconds-calculation
unsigned long long calculate_time_ns(struct timespec start, struct timespec end);
unsigned long long rdtsc_old(int CPUID); //  Get time with rdtsc, if it is enabled in the kernel
unsigned long long average_time(unsigned long long *time, int timesRun); // Calculate average time of running an experiment
unsigned long long min_time(unsigned long long *time, int timesRun); // Calculate the minimum time of running an experiment
// Functions used for testing
void test_clock_gettime(void);
void test_clock_getres(void);
void test_rdtsc(void);

#endif /* HR_TIMER_H_ */
