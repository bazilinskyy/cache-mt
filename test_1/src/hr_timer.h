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

// Get time in nanoseconds
int get_time_ns(struct timespec *timeStruct);
// From http://stackoverflow.com/questions/13950290/clock-gettime-nanoseconds-calculation
unsigned long long calculate_time_ns(struct timespec start, struct timespec end);

#endif /* HR_TIMER_H_ */
