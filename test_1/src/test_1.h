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

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
// Pthread
#include <pthread.h>
#include <sched.h>
#include <errno.h>
// Custom includes
#include "hr_timer.h"
#include "conf.h"
#include "file_worker.h"


// Process ID
#ifndef __APPLE__
	#include <sys/types.h>
	#include <unistd.h>
#endif

int main(void);
int pthread_main(int thread_num); // Main run in the pthread
void experiment (unsigned char *testAr, unsigned char testCh, int n);
unsigned long long average_time(unsigned long long *time, int timesRun); // Calculate average time of running experiment
int pin_thread_to_core(int coreId); // Pin pthread to core
int set_highest_process_priority(void); // Set priority of the current to be the highest
void test_interrupt_time (void); // Record how much time one interrupt takes on the testing system
int warm_strings_with_files(void); // Create two copies of each string used for storing files to fill in memory with this data.

#endif /* TEST_1_H_ */
