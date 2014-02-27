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

#include "test_1.h"

int main(void) {
	unsigned long long time[MAX_POWER];
	struct timespec start, stop;
	int i = 0;
	long n;
	for (n = 1.0; n < pow(2.0, (double) MAX_POWER); n *= 2.0) {

#ifdef DEBUG
		printf("%d. %ld ", i+1, n);
#endif
		// Calculate start time
		//get_time_ns(start);
		if( clock_gettime( CLOCK_MONOTONIC, &start) == -1 ) {
			perror( "clock gettime" );
			return 0;
		}

		// Run experiment
		unsigned char testAr[(int) n]; // Array for manipulating data
		unsigned char testCh; // 1 byte of data
		int j;
		for (j = 0; j < n; j++) { // Write and read 1 byte n times
			testAr[(int) n] = CHAR_TO_ADD; // Write 1 byte
			testCh = testAr[(int) n]; // Read 1 byte
		}

		// Calculate finish time
		//get_time_ns(stop);
		if( clock_gettime( CLOCK_MONOTONIC, &stop) == -1 ) {
			perror( "clock gettime" );
			return 0;
		}

		// Record difference
		time[(int) i] = calculate_time_ns(start, stop);
		i++; // Iterate for easier access to array
	}

	// Output results
#ifdef SHOW_RESULTS
	printf("\nRESULTS:\n");
	for (i = 0; i < MAX_POWER; ++i) {
		printf("%.0f,%llu\n", pow(2.0, (double) i), time[i]);
	}
#endif

#ifdef OUTPUT_TO_FILE
	// Write to file
	write_to_csv(time, "N", "Time");
#endif

	// Everything is good, return Success code
	return EXIT_SUCCESS;
}


