/*
 ============================================================================================
 Name        : test_env.c
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

 Description : The testing environment.
 Target		 : MacBook Air with i7 and Xeon 5130
 ============================================================================================
 */

#include "test_env.h"

// Record how much time one interrupt takes on the testing system
void test_interrupt_time(void) {
#ifndef __APPLE__

	struct timespec start, stop;
	int run = 10;

	// Record time run times
	unsigned long long *time = malloc(sizeof(unsigned long long) * run);// Record times of experiments in the run.
	if (time == NULL) {
		printf("Error with allocating space for the array\n");
		exit(1);
	}

	int i = 0;
	for (i = 0; i < run; ++i) {
		unsigned long long interruptsBefore;
		unsigned long long interruptsAfter;

		// Warmup
		interruptsAfter = search_in_file("/proc/interrupts", "LOC:", 1);
		interruptsBefore = interruptsAfter;

		while (interruptsBefore == interruptsAfter)
		interruptsBefore = search_in_file("/proc/interrupts", "LOC:", 1);

		get_time_ns(&start);// Record time before causing the interrupt

		// Create interrupts
		do {
			interruptsAfter = search_in_file("/proc/interrupts", "LOC:", 1);
		}while (interruptsAfter - interruptsBefore == 0);

		get_time_ns(&stop); // Record time after causing the interrupt

		int numInterrupts = interruptsAfter - interruptsBefore;// How many interrupts occurred
		unsigned long long timeWithInterupts = calculate_time_ns(start, stop);// Record time with interrupts

		printf("Time %llu Num %d\n", timeWithInterupts, numInterrupts);
		time[i] = timeWithInterupts / numInterrupts;// Record time difference over a number of interrupts
	}
	printf("1 interrupt takes (average from %d runs): %llu\n", run, average_time(time, run));

	free(time);
#else
	printf("Measuring time that interrupts take is not supported on this system.\n");
#endif
}

// Create two copies of each string used for storing files to fill in memory with this data.
int warm_strings_with_files(void) {
	// Strings for storing contents of the files
	char *interruptsBeforeStringWarm1 = malloc(BIG_BUFFER_SIZE);
	if (interruptsBeforeStringWarm1 == NULL) {
		printf("Error with allocating space for the string interruptsBeforeString\n");
		exit(1);
	}
	char *pageFaultsBeforeStringWarm1 = malloc(BIG_BUFFER_SIZE);
	if (pageFaultsBeforeStringWarm1 == NULL) {
		printf("Error with allocating space for the string pageFaultsBeforeString\n");
		exit(1);
	}
	char *contextSwitchesBeforeStringWarm1 = malloc(BIG_BUFFER_SIZE);
	if (contextSwitchesBeforeStringWarm1 == NULL) {
		printf("Error with allocating space for the string contextSwitchesBeforeString\n");
		exit(1);
	}
	char *interruptsBeforeStringWarm2 = malloc(BIG_BUFFER_SIZE);
	if (interruptsBeforeStringWarm2 == NULL) {
		printf("Error with allocating space for the string interruptsBeforeString\n");
		exit(1);
	}
	char *pageFaultsBeforeStringWarm2 = malloc(BIG_BUFFER_SIZE);
	if (pageFaultsBeforeStringWarm2 == NULL) {
		printf("Error with allocating space for the string pageFaultsBeforeString\n");
		exit(1);
	}
	char *contextSwitchesBeforeStringWarm2 = malloc(BIG_BUFFER_SIZE);
	if (contextSwitchesBeforeStringWarm2 == NULL) {
		printf("Error with allocating space for the string contextSwitchesBeforeString\n");
		exit(1);
	}

	// Get process ID
	int processIdTemp = getpid();

	// Create path to the proc/PID file
	char fileNameTemp[100];
	char bufTemp[100];
	char buf2Temp[100] = "/proc/";
	snprintf(bufTemp, 100, "%d", processIdTemp);
	snprintf(fileNameTemp, 100, "%s%s", buf2Temp, bufTemp);

	// Get readings on interrupts, pagefaults and context switched before running the experiment
	//Info: http://www.centos.org/docs/5/html/Deployment_Guide-en-US/s1-proc-topfiles.html

	// Save files with information on interrupts, page faults, and context switches into strings
	interruptsBeforeStringWarm1 = file_to_string("/proc/interrupts");
	interruptsBeforeStringWarm2 = file_to_string("/proc/interrupts");

	// Add stat to the name of the file
	char fileNameStatTemp[100];
	snprintf(fileNameStatTemp, 100, "%s%s", fileNameStatTemp, "/stat");
	pageFaultsBeforeStringWarm1 = file_to_string(fileNameStatTemp);
	pageFaultsBeforeStringWarm2 = file_to_string(fileNameStatTemp);

	// Add status to the name of the file
	snprintf(fileNameStatTemp, 100, "%s%s", fileNameStatTemp, "/status");
	contextSwitchesBeforeStringWarm1 = file_to_string(fileNameStatTemp);
	contextSwitchesBeforeStringWarm2 = file_to_string(fileNameStatTemp);

	return 1;
}

// Calculate how many bytes are to be written during the experiment
long calculate_n(long n) {
	if (n < 1000) {
		n *= 2.0;
	} else if (n > 1000 && n < 10000) {
		n += 1024;
	} else if (n > 10000 && n < 100000) {
		n += 10240;
	} else if (n > 100000 && n < 1000000) {
		n += 102400;
	} else if (n > 1000000 && n < 10000000) {
		n += 1024000;
	} else if (n > 10000000 && n < 100000000) {
		n += 10240000;
	} else {
		n *= 2.0;
	}
	return n;

//	return n * 2.0;
}
