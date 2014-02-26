/*
 ============================================================================
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
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#ifdef __APPLE__
	#include "mach_gettime.h"
#elif __linux // For future use
    // linux
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif

#include "test_1.h"

#define MAX_POWER 24
#define BILLION  1000000000L
//#define DEBUG
#define SHOW_RESULTS
#define CHAR_TO_ADD 'a'

int main(void) {
	unsigned long long time[MAX_POWER];
	struct timespec start, stop;
	int i = 0;
	for (long n = 1.0; n < pow(2.0, (double) MAX_POWER); n *= 2.0) {

#ifdef DEBUG
		printf("%d. %ld ", i+1, n);
#endif
		// Calculate start time
		//get_time_ns(start);
		if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
			perror( "clock gettime" );
			return 0;
		}

		// Run experiment
		unsigned char testAr[(int) n];
		unsigned char testCh;
		for (double i = 0.0; i < n; i++) {
			testAr[(int) n] = CHAR_TO_ADD;
			testCh = testAr[(int) n];
		}

		// Calculate finish time
		//get_time_ns(stop);
		if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
			perror( "clock gettime" );
			return 0;
		}

		// Record difference
		time[i] = calculate_time_ns(start, stop);
		i++; // Iterate for easier access to array
	}

	// Output results
#ifdef SHOW_RESULTS
	printf("\nRESULTS:\n");
	for (int var = 0; var < MAX_POWER; ++var) {
		printf("%.0f,%llu\n", pow(2.0, (double) var), time[var]);
	}

#endif

	return EXIT_SUCCESS;
}

// Get time in nanoseconds
int get_time_ns(struct timespec timeStruct) {
	 if( clock_gettime( CLOCK_REALTIME, &timeStruct) == -1 ) {
	      perror( "clock gettime" );
	      return 0;
	 }
	 printf("Inside call: %ld ", timeStruct.tv_nsec);
	 return 1;
}

// From http://stackoverflow.com/questions/13950290/clock-gettime-nanoseconds-calculation
unsigned long long calculate_time_ns(struct timespec start, struct timespec end) {
//	unsigned long long accum = ( timeStructFinish.tv_sec - timeStructStart.tv_sec ) + (double)( timeStructFinish.tv_nsec - timeStructStart.tv_nsec ) / (double)BILLION;
	struct timespec temp;
	if ((end.tv_nsec - start.tv_nsec) < 0)
	{
			temp.tv_sec = end.tv_sec - start.tv_sec - 1;
			temp.tv_nsec = BILLION + end.tv_nsec - start.tv_nsec;
	}
	else
	{
			temp.tv_sec = end.tv_sec - start.tv_sec;
			temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}

#ifdef DEBUG
	printf("TIME: %lld.%.9ld\n", (long long)temp.tv_sec, temp.tv_nsec);
#endif

	return BILLION*temp.tv_sec + temp.tv_nsec;
}
