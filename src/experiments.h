/*
 ============================================================================================
 Name        : experiments.c
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

 Description : The header for the experiments.
 Target		 : MacBook Air with i7 and Xeon 5130
 ============================================================================================
 */

#ifndef EXPERIMENTS_H_
#define EXPERIMENTS_H_

#define _GNU_SOURCE
#include "conf.h"

#include <stdio.h>
#include <stdlib.h>
// Pthread
#include <sched.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mut; // Mutex used for thread synchronisation.

/*
 * Structure used for a wrapper function used in pthread_create.
 */
struct argStructType {
	int experimentId;	// ID of an experiment.
	int n; 				// Size of data handled in the experiment.
	long * testAr; 		// Pointer to a shared between threads structure
};

// Main functions for running experiments.
void experiment_0();
void experiment_1(int n);
void experiment_2(int n);
void experiment_3(int n);
void experiment_4(int n);
//void experiment_5(int n);
//void experiment_6(int n);

// Functions to be run from inside of pthreads in the experiments.
void *e2_pthread_main1(void * argStruct);
void *e2_pthread_main2(void * argStruct);
void *e3_pthread_main1(void * argStruct);
void *e3_pthread_main2(void * argStruct);
void *e4_pthread_main1(void * argStruct);
void *e4_pthread_main2(void * argStruct);

long * align_long_array(int size); // Return a pointer to an aligned array of longs
int pin_thread_to_core(int coreId); // Pin pthread to core

#endif /* EXPERIMENTS_H_ */
