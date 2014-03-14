/*
 ============================================================================================
 Name        : test_1.c
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

 Description : Test 1 (measuring cache latency)
 Target		 : MacBook Air with i7 and Xeon 5130
 ============================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include "file_worker.h"
#include "hr_timer.h"

#ifdef __APPLE__
#include "clock_gettime_mac.h"
#elif __linux // For future use
// linux
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif


#define BILLION  1000000000L

int main(void) {
	struct timespec time1, time2, time3, time4, time5;

	unsigned long long interrupts = search_in_file("/proc/interrupts", "LOC:", 1);


	if (clock_gettime( CLOCK_MONOTONIC, &time1) == -1) {
		perror("clock gettime");
		return 0;
	}

	unsigned long long pageFaultsMinorBefore = get_page_fault(1);
	unsigned long long pageFaultsMajorBefore = get_page_fault(2);

	if (clock_gettime( CLOCK_MONOTONIC, &time2) == -1) {
		perror("clock gettime");
		return 0;
	}

	while (time2.tv_sec == time1.tv_sec && time1.tv_nsec == time2.tv_nsec) {
		if (clock_gettime( CLOCK_MONOTONIC, &time2) == -1) {
			perror("clock gettime");
			return 0;
		}
	}





	if (clock_gettime( CLOCK_MONOTONIC, &time3) == -1) {
		perror("clock gettime");
		return 0;
	}

	while (time2.tv_sec == time3.tv_sec && time2.tv_nsec == time3.tv_nsec) {
		if (clock_gettime( CLOCK_MONOTONIC, &time3) == -1) {
			perror("clock gettime");
			return 0;
		}
	}

	if (clock_gettime( CLOCK_MONOTONIC, &time4) == -1) {
		perror("clock gettime");
		return 0;
	}

	interrupts = search_in_file("/proc/interrupts", "LOC:", 1);

	if (clock_gettime( CLOCK_MONOTONIC, &time5) == -1) {
		perror("clock gettime");
		return 0;
	}

	unsigned long long pageFaultsMinorAfter = get_page_fault(1);
	unsigned long long pageFaultsMajorAfter = get_page_fault(2);

	printf("t3 - t2: %llu\n", calculate_time_ns(time1, time2));
	printf("t4 - t3: %llu\n", calculate_time_ns(time3, time4));
	printf("t5 - t4: %llu\n", calculate_time_ns(time4, time5));

	printf("PF Maj B: %llu\n", pageFaultsMajorBefore);
	printf("PF Min B: %llu\n", pageFaultsMinorBefore);
	printf("PF Maj A: %llu\n", pageFaultsMajorAfter);
	printf("PF Min A: %llu\n", pageFaultsMinorAfter);

}
