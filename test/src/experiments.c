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

 Description : The experiments.
 Target		 : MacBook Air with i7 and Xeon 5130
 ============================================================================================
 */

#include "experiments.h"

/*
 * EXPERIMENT 0
 *
 * Measuring latncy of registers.
 */

// Test 0 (Control)
void experiment_0() {
	printf ("Test with registers\n");
	register long x = 10;
	long y = 0;
	x = y;
}

/*
 * EXPERIMENT 0
 *
 * Measuring cycle-level latency.
 */

// Test 1 ()
void experiment_1(int n) {
	long *testAr = malloc(sizeof(long) * n * 2);
	// test& = 0xFFFFFFD0; Align data
	if (testAr == NULL) { // Array for manipulating data
		printf("Error with allocating space for the array\n");
		exit(1);
	}
	long testLong = 0; // 4 bytes of data

	int i;
	for (i = 0; i < n; i++) { // Write and read 1 byte n times
		testAr[(int) n] = LONG_TO_ADD; // Write 1 byte
		testLong += testAr[(int) n]; // Read 1 byte
	}
	free(testAr);
}

//TODO fix pthreads on Mac OS. OLD CODE for pthreads.
//#ifndef __APPLE__
//	pthread_t thread1;
//	int rc;
//
//	// Run in pthread
//	rc = pthread_create(&thread1, NULL, pthread_main, (void *)NULL);
//	if (rc) {
//		printf("ERROR; return code from pthread_create() is %d\n", rc);
//		exit(-1);
//	}
//	pthread_join(thread1, NULL);
//#else
//	pthread_main((void *) 1);
//#endif

/*
 * EXPERIMENT 2
 *
 */
void experiment_2(int n) {
	pthread_t thread1, thread2;
	int rc;

	long *testAr = malloc(sizeof(long) * n);
	if (testAr == NULL) { // Array for manipulating data
		printf("Error with allocating space for the array\n");
		exit(1);
	}

	// Wrap information that has to be passed to a pthread
	struct argStructType * argStruct = malloc(sizeof(struct argStructType));
	argStruct->experimentId = 2;
	argStruct->n = n;
	argStruct->testAr = testAr;

	pthread_mutex_init(&mut, NULL); // Initialise the mutex.

	// Create pthreads
	pthread_mutex_lock(&mut); // Lock mutex.
	rc = pthread_create(&thread1, NULL, e2_pthread_main1, (void *) argStruct);
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	pthread_mutex_unlock(&mut); // Lock mutex.

	pthread_mutex_lock(&mut); // Lock mutex.
	rc = pthread_create(&thread2, NULL, e2_pthread_main2, (void *) argStruct);
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	pthread_mutex_unlock(&mut); // Lock mutex.

	// Join threads
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// Finish
	free(testAr);
	free(argStruct); // Free memory allocated for generic argument struct
	pthread_mutex_destroy(&mut);
}

// Sender. This thread sends data
void *e2_pthread_main1(void * argStruct) {
	pin_thread_to_core(0); // Pin to the first core of the first CPU.

	struct argStructType *args = (struct argStructType *) argStruct; 	// Unpack arguments


	// Work with  shared data
	int i = 0;
	for (i = 0; i < args->n; ++i) {
		args->testAr[i] = 3l;
	}

	return ((void *) 1);
}

void *e2_pthread_main2(void * argStruct) {
	pin_thread_to_core(0); // Pin to the first core of the first CPU.

	struct argStructType *args = (struct argStructType *) argStruct; 	// Unpack arguments

	// Work with  shared data
	int i = 0;
	long temp; // For assignment of values from the therad
	for (i = 0; i < args->n; ++i) {
		temp = args->testAr[i];
	}

	return ((void *) 1);
}

/*
 * EXPERIMENT 3
 *
 */
void experiment_3(int n) {
	pthread_t thread1, thread2;
	int rc;

	long *testAr = malloc(sizeof(long) * n);
	if (testAr == NULL) { // Array for manipulating data
		printf("Error with allocating space for the array\n");
		exit(1);
	}

	// Wrap information that has to be passed to a pthread
	struct argStructType * argStruct = malloc(sizeof(struct argStructType));
	argStruct->experimentId = 2;
	argStruct->n = n;
	argStruct->testAr = testAr;

	pthread_mutex_init(&mut, NULL); // Initialise the mutex.

	// Create pthreads
	pthread_mutex_lock(&mut); // Lock mutex.
	rc = pthread_create(&thread1, NULL, e3_pthread_main1, (void *) argStruct);
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	pthread_mutex_unlock(&mut); // Lock mutex.
	pthread_mutex_lock(&mut); // Lock mutex.
	rc = pthread_create(&thread2, NULL, e3_pthread_main2, (void *) argStruct);
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	pthread_mutex_unlock(&mut); // Lock mutex.

	// Join threads
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// Finish
	free(argStruct); // Free memory allocated for generic argument struct
	pthread_mutex_destroy(&mut);
}

// Sender. This thread sends data
void *e3_pthread_main1(void * argStruct) {
	pin_thread_to_core(0); // Pin to the first core of the first CPU.

	struct argStructType *args = (struct argStructType *) argStruct; 	// Unpack arguments

	// Work with  shared data
	int i = 0;
	for (i = 0; i < args->n; ++i) {
		args->testAr[i] = 3l;
	}

	return ((void *) 1);
}

// Received. This thread receives data.
void *e3_pthread_main2(void * argStruct) {
	pin_thread_to_core(1); // Pin to the first core of the first CPU. We assumed that there is at least one CPU with at least 2 cores.

	struct argStructType *args = (struct argStructType *) argStruct; 	// Unpack arguments

	// Work with  shared data
	int i = 0;
	long temp; // For assignment of values from the therad
	for (i = 0; i < args->n; ++i) {
		temp = args->testAr[i];
	}

	return ((void *) 1);
}

/*
 * EXPERIMENT 4
 *
 */
void experiment_4(int n) {
	pthread_t thread1, thread2;
	int rc;

	long *testAr = malloc(sizeof(long) * n);
	if (testAr == NULL) { // Array for manipulating data
		printf("Error with allocating space for the array\n");
		exit(1);
	}

	// Wrap information that has to be passed to a pthread
	struct argStructType * argStruct = malloc(sizeof(struct argStructType));
	argStruct->experimentId = 2;
	argStruct->n = n;
	argStruct->testAr = testAr;

	pthread_mutex_init(&mut, NULL); // Initialise the mutex.

	// Create pthreads
	pthread_mutex_lock(&mut); // Lock mutex.
	rc = pthread_create(&thread1, NULL, e4_pthread_main1, (void *) argStruct);
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	pthread_mutex_unlock(&mut); // Lock mutex.
	pthread_mutex_lock(&mut); // Lock mutex.
	rc = pthread_create(&thread2, NULL, e4_pthread_main2, (void *) argStruct);
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	pthread_mutex_unlock(&mut); // Lock mutex.

	// Join threads
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// Finish
	free(argStruct); // Free memory allocated for generic argument struct
	pthread_mutex_destroy(&mut);
}

// Sender. This thread sends data
void *e4_pthread_main1(void * argStruct) {
	pin_thread_to_core(0); // Pin to the first core of the first CPU.

	struct argStructType *args = (struct argStructType *) argStruct; 	// Unpack arguments

	// Work with  shared data
	int i = 0;
	for (i = 0; i < args->n; ++i) {
		args->testAr[i] = 3l;
	}

	return ((void *) 1);
}

// Received. This thread receives data.
void *e4_pthread_main2(void * argStruct) {
	int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
	pin_thread_to_core(num_cores - 1); // Pin to the first core of the first CPU. Pin to the last available core.
									   // We assume that there are two chips in the processor

	struct argStructType *args = (struct argStructType *) argStruct; 	// Unpack arguments

	// Work with  shared data
	int i = 0;
	long temp; // For assignment of values from the therad
	for (i = 0; i < args->n; ++i) {
		temp = args->testAr[i];
	}

	return ((void *) 1);
}
/*
 * EXPERIMENT 5
 *
 */
void experiment_5(int n) {
}

/*
 * EXPERIMENT 6
 *
 */
void experiment_6(int n) {
}

// Pin thread to a particular core
int pin_thread_to_core(int coreId) {
	int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
	if (coreId < 0 || coreId >= num_cores)
	return EINVAL;

	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(coreId, &cpuset);

	pthread_t current_thread = pthread_self();
	return pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}
