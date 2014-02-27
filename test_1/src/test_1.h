/*
 ============================================================================================
 Name        : test_1.h
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

 Description : Configuration of the experiment
 ============================================================================================
 */
#ifndef TEST_1_H_
#define TEST_1_H_

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
// Custom includes
#include "hr_timer.h"
#include "conf.h"
#include "file_worker.h"

int main(void);
int get_time_ns(struct timespec timeStruct);
unsigned long long calculate_time_ns(struct timespec timeStructStart, struct timespec timeStructFinish);

#endif /* TEST_1_H_ */
