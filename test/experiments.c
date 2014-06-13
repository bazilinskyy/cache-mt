/*
 ============================================================================================
 Name        : experiments.c
 Author      : Pavlo Bazilinskyy
 Version     : 1.0
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

 Description : The experiments. This file contains code for all 5 experiments (Experiment 0 Ð
 	 	 	   Experiment 4). Experiments 0 - 1 are cycle-level experiments. Experiments 2 -
 	 	 	   4 are application-level experiments. Experiments 2 - 4 contain three functions
 	 	 	   each: one control thread, one "sending" thread, and one "receiving" thread.

 ============================================================================================
 */

#include "experiments.h"

pthread_t thread1, thread2; // POSIX-threads to be used in Experiments 1 - 4.
int rc; 					// Return value for pthread_create function.

/*
 * EXPERIMENT 0
 *
 * Cycle-level experiment. Measuring latency of registers. Two variables of type long, one stored
 * in a CPU register and one defined as a local variable are created. Value of the local variable
 * is assigned to the register-based variable.
 */
void experiment_0() {
	register long x = 10; 	// Store in the register
	long y = 0; 			// Normal local variable
	x = y; 					// Assign value of the local variable to the register-based variable
}

/*
 * EXPERIMENT 1
 *
 * Cycle-level experiment. Measuring latency of cache and main memory. Attempts to isolate
 * overhead of the OS (page faults and interrupts) were not successful and data received through
 * this function is overly pessimistic (reported latency is much higher that what may be expected).
 */
void experiment_1(int n) {
	// Array for manipulating data
	long *testAr = align_long_array(sizeof(long) * n); // Align array

	long testLong = 0; // 8 bytes of data (in the experimental environment)

	/*
	 * Write and read 8 bytes n times
	 */
	int i;
	for (i = 0; i < n; i++) {
		testAr[(int) n] = LONG_TO_ADD; 	// Write 8 bytes
		testLong += testAr[(int) n]; 	// Read 8 bytes
	}
	free(testAr); // Free memory
}

/*
 * EXPERIMENT 2
 *
 * Application-level experiment. Measuring latency of exchange of data that takes place between two
 * threads (writing and receiving threads). Both threads are pinned to the same core. It describes the
 * type 1 inter-thread communication (defined in the taxonomy). This experiment serves as the base case.
 *
 * Control thread.
 */
void experiment_2(int n) {
	// Array for manipulating data
	long *testAr = align_long_array(sizeof(long) * n); // Align array

	// Wrap information that has to be passed to a pthread
	struct argStructType * argStruct = malloc(sizeof(struct argStructType));
	argStruct->experimentId = 2; // ID of the experiment
	argStruct->n = n;			 // Amount of data to be exchanged between threads
	argStruct->testAr = testAr;	 // Pointer to the array used to store data

	pthread_mutex_init(&mut, NULL); // Initialise the mutex.

	// Create the sending thread.
	rc = pthread_create(&thread1, NULL, e2_pthread_main1, (void *) argStruct);
	if (rc) { // Return value must be non-positive, otherwise - error
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}

	// Join threads
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// Finish
	free(testAr);	 // Free memory allocated for the array with shared data
	free(argStruct); // Free memory allocated for the generic argument struct
	pthread_mutex_destroy(&mut); // The mutex is no longer needed
}

// Sending thread. This thread writes data into cache/main memory.
void *e2_pthread_main1(void * argStruct) {
	pin_thread_to_core(0); // Pin to the first core of the first CPU.

	struct argStructType *args = (struct argStructType *) argStruct; 	// Unpack arguments

	pthread_mutex_lock(&mut); // Lock mutex.

	// Create the receiving thread.
	rc = pthread_create(&thread2, NULL, e2_pthread_main2, (void *) argStruct);
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}

	// Work with shared data
	int i = 0;
	for (i = 0; i < args->n; ++i) {
		args->testAr[i] = 3l; // Assign a long
	}

	pthread_yield(); // Wait for the thread.
	pthread_mutex_unlock(&mut); // Unlock mutex.

	return ((void *) 1);
}

// Receiving thread. This thread reads data from cache/main memory.
void *e2_pthread_main2(void * argStruct) {
	pin_thread_to_core(0); // Pin to the first core of the first CPU.

	struct argStructType *args = (struct argStructType *) argStruct; 	// Unpack arguments

	pthread_mutex_lock(&mut); // Lock mutex.

	// Work with  shared data
	int i = 0;
	long temp; // For assignment of values from the thread.
	for (i = 0; i < args->n; ++i) {
		temp = args->testAr[i]; // Read data from the shared array.
	}

	pthread_mutex_unlock(&mut); // Unlock mutex.

	return ((void *) 1);
}

/*
 * EXPERIMENT 3
 *
 * Application-level experiment. Measuring latency of exchange of data that takes place between two
 * threads (writing and receiving threads). The threads are pinned to different cores on the same chip.
 * It describes the type 2 inter-thread communication (defined in the taxonomy). This experiment serves
 * as the base case.
 *
 * Control thread.
 */
void experiment_3(int n) {
	// Array for manipulating data
	long *testAr = align_long_array(sizeof(long) * n); // Align array

	// Wrap information that has to be passed to a pthread
	struct argStructType * argStruct = malloc(sizeof(struct argStructType));
	argStruct->experimentId = 3; // ID of the experiment
	argStruct->n = n;			 // Amount of data to be exchanged between threads
	argStruct->testAr = testAr;	 // Pointer to the array used to store data

	pthread_mutex_init(&mut, NULL); // Initialise the mutex.

	// Create the sending thread.
	rc = pthread_create(&thread1, NULL, e3_pthread_main1, (void *) argStruct);
	if (rc) { // Return value must be non-positive, otherwise - error
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}

	// Join threads
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// Finish
	free(testAr);	 // Free memory allocated for the array with shared data
	free(argStruct); // Free memory allocated for the generic argument struct
	pthread_mutex_destroy(&mut); // The mutex is no longer needed
}

// Sending thread. This thread writes data into cache/main memory.
void *e3_pthread_main1(void * argStruct) {
	pin_thread_to_core(0); // Pin to the first core of the first CPU.

	struct argStructType *args = (struct argStructType *) argStruct; 	// Unpack arguments

	pthread_mutex_lock(&mut); // Lock mutex.

	// Create the receiving thread.
	rc = pthread_create(&thread2, NULL, e3_pthread_main2, (void *) argStruct);
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}

	// Work with  shared data
	int i = 0;
	for (i = 0; i < args->n; ++i) {
		args->testAr[i] = 3l; // Assign a long
	}

	pthread_yield(); // Wait for the thread.
	pthread_mutex_unlock(&mut); // Unlock mutex.

	return ((void *) 1);
}

// Receiving thread. This thread reads data from cache/main memory.
void *e3_pthread_main2(void * argStruct) {
	pin_thread_to_core(1); // Pin to the second core of the first CPU.

	struct argStructType *args = (struct argStructType *) argStruct; 	// Unpack arguments

	pthread_mutex_lock(&mut); // Lock mutex.

	// Work with  shared data
	int i = 0;
	long temp; // For assignment of values from the thread.
	for (i = 0; i < args->n; ++i) {
		temp = args->testAr[i]; // Read data from the shared array.
	}

	pthread_mutex_unlock(&mut); // Unlock mutex.

	return ((void *) 1);
}

/*
 * EXPERIMENT 4
 *
 * Application-level experiment. Measuring latency of exchange of data that takes place between two
 * threads (writing and receiving threads). The threads are pinned to different chips. It describes
 * the type 3 inter-thread communication (defined in the taxonomy). This experiment serves as the base
 * case.
 *
 * Control thread.
 */
void experiment_4(int n) {
	// Array for manipulating data
	long *testAr = align_long_array(sizeof(long) * n); // Align array

	// Wrap information that has to be passed to a pthread
	struct argStructType * argStruct = malloc(sizeof(struct argStructType));
	argStruct->experimentId = 4; // ID of the experiment
	argStruct->n = n;			 // Amount of data to be exchanged between threads
	argStruct->testAr = testAr;	 // Pointer to the array used to store data

	pthread_mutex_init(&mut, NULL); // Initialise the mutex.

	// Create the sending thread.
	rc = pthread_create(&thread1, NULL, e4_pthread_main1, (void *) argStruct);
	if (rc) { // Return value must be non-positive, otherwise - error
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}

	// Join threads
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// Finish
	free(testAr);	 // Free memory allocated for the array with shared data
	free(argStruct); // Free memory allocated for the generic argument struct
	pthread_mutex_destroy(&mut); // The mutex is no longer needed
}

// Sending thread. This thread writes data into cache/main memory.
void *e4_pthread_main1(void * argStruct) {
	pin_thread_to_core(0); // Pin to the first core of the first CPU.

	struct argStructType *args = (struct argStructType *) argStruct; 	// Unpack arguments

	pthread_mutex_lock(&mut); // Lock mutex.

	// Create the receiving thread.
	rc = pthread_create(&thread2, NULL, e4_pthread_main2, (void *) argStruct);
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}

	// Work with  shared data
	int i = 0;
	for (i = 0; i < args->n; ++i) {
		args->testAr[i] = 3l; // Assign a long
	}

	pthread_yield(); // Wait for the thread.
	pthread_mutex_unlock(&mut); // Unlock mutex.

	return ((void *) 1);
}

// Receiving thread. This thread reads data from cache/main memory.
void *e4_pthread_main2(void * argStruct) {
	int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
	//printf ("NUM CORES: %d\n", num_cores);
	pin_thread_to_core(num_cores - 1); // Pin to the last available core. We assume that there
									   // are two chips in the processor.

	struct argStructType *args = (struct argStructType *) argStruct; // Unpack arguments

	pthread_mutex_lock(&mut); // Lock mutex.

	// Work with  shared data
	int i = 0;
	long temp; // For assignment of values from the thread.
	for (i = 0; i < args->n; ++i) {
		temp = args->testAr[i]; // Read data from the shared array.
	}

	pthread_mutex_unlock(&mut); // Unlock mutex.

	return ((void *) 1);
}

/*
 * Pin thread to a particular core with ID == coreId.
 */
int pin_thread_to_core(int coreId) {
	int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
	// First check if coreId is within the bounds
	if (coreId < 0 || coreId >= num_cores)
		return EINVAL;

	// Receive the cpuset struct with information about the CPU
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(coreId, &cpuset);

	pthread_t current_thread = pthread_self(); // Get the ID of the current thread
	return pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset); // Pin thread to coreId
}

/*
 * Return a pointer to an aligned array of longs.
 */
long * align_long_array(int size) {
#ifdef ALIGN_DATA
	int cacheLine = 64 * 2; // Cache line size with extra space
	long x = malloc(size + cacheLine); // Malloc space for data + cacheLine
	if (x == NULL) { // Array for manipulating data
		printf("Error with allocating space.\n");
		exit(1);
	}
	return (unsigned long *) ((unsigned long long)
			(x + cacheLine) & 0xFFFFFFE0); // Return aligned array
#else
	return malloc(size); // If now alignment is required, just malloc enough space for data.
#endif
}
