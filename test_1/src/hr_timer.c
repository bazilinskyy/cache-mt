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
	 if( clock_gettime( CLOCK_MONOTONIC, timeStruct) == -1 ) {
	      perror( "clock gettime" );
	      return 0;
	 }
	 return 1;
}

// Get time in nanoseconds
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

	return BILLION*temp.tv_sec + temp.tv_nsec;
}
