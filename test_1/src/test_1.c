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

//	while (1 == 1) {
//		printf("My current process id/pid is %d\n", getpid());
//	}

	// Run experiments
	for (n = 1.0; n < pow(2.0, (double) MAX_POWER); n *= 2.0) {
		unsigned char testAr[(int) n]; // Array for manipulating data
		unsigned char testCh = ' '; // 1 byte of data
		//Warm up cache
#ifdef WARM_CACHE
		experiment(testAr, testCh, 0);
#endif
		// Run each experiment for TIMES_RUN_EXPERIMENT times
		int expI = 0;
		unsigned long long currentTime[TIMES_RUN_EXPERIMENT];
		int experimentsRunSuccessfully = 0; // Record how many times the experiment was run successfully
		for (expI = 0; expI < TIMES_RUN_EXPERIMENT; ++expI) {
			int j;
			unsigned long long interruptsBefore = 0;
			unsigned long long interruptsAfter = 0;
			unsigned long long pageFaultsMinorBefore = 0;
			unsigned long long pageFaultsMinorAfter = 0;
			unsigned long long pageFaultsMajorBefore = 0;
			unsigned long long pageFaultsMajorAfter = 0;
			unsigned long long contextSwitchesBefore = 0;
			unsigned long long contextSwitchesAfter = 0;
#ifndef __APPLE__
			// Get process ID
			int processId = getpid();

			// Create path to the proc/PID file
			char fileName[100];
			char buf[100];
			char buf2[100] = "/proc/";
			snprintf(buf, 100, "%d", processId);
			snprintf(fileName, 100, "%s%s", buf2, buf);

			// Get readings on interrupts, pagefaults and context switched before running the experiment

			//Info: http://www.centos.org/docs/5/html/Deployment_Guide-en-US/s1-proc-topfiles.html
			interruptsBefore = search_in_file("/proc/interrupts", "LOC:", 1);
			pageFaultsMinorBefore = search_in_file("/proc/vmstat", "pgfault:", 1);
			pageFaultsMajorBefore = search_in_file("/proc/vmstat", "pgmajfault:", 1);
			// Add status to the name of the file
			char fileNameStatus[100];
			snprintf(fileNameStatus, 100, "%s%s", fileName, "/status");
			contextSwitchesBefore = search_in_file(fileNameStatus, "voluntary_ctxt_switches:", 1);
#else
			//TODO read for Mac OS
#endif
			// Run experiment
			// Calculate start time
			get_time_ns(&start);
			for (j = 0; j < n; j++) { // Write and read 1 byte n times
				experiment(testAr, testCh, n);
			}

			// Calculate finish time
			get_time_ns(&stop);
			// Get readings on interrupts, pagefaults and context switched before running the experiment
#ifndef __APPLE__
			interruptsAfter = search_in_file("/proc/interrupts", "LOC:", 1);
			pageFaultsMinorAfter = search_in_file("/proc/vmstat", "pgfault:", 1);
			pageFaultsMajorAfter = search_in_file("/proc/vmstat", "pgmajfault:", 1);
			contextSwitchesAfter = search_in_file(fileNameStatus, "voluntary_ctxt_switches:", 1);
#else
			//TODO read for Mac OS
#endif
			// Record difference
			unsigned long long tempTime = calculate_time_ns(start, stop); // Calculate how much time this run took

			// Disregard experiment if comparison of it with MIN and MAX makes it invalid
			//TODO verify with Stephen
			unsigned long long minTime = n * 1;   // Lower bound for the duration of the run
			unsigned long long maxTime = n * 10000; // Upper bound for the duration of the run
			if (tempTime < minTime || tempTime > maxTime) { // Disregard this run if it does not meet timing requirements
				continue;
			} else if (pageFaultsMinorAfter - pageFaultsMinorBefore > ALLOWED_PAGEFAULTS_MINOR) { // Disregard this run if minor pagefaults were detected
				continue;
			} else if (pageFaultsMajorAfter - pageFaultsMajorBefore > ALLOWED_PAGEFAULTS_MAJOR) { // Disregard this run if major pagefaults were detected
				continue;
			} else if (contextSwitchesAfter - contextSwitchesBefore > ALLOWED_CONTEXT_SWITCHES) { // Disregard this run if voluntary context switches were detected
				continue;
			} else if (interruptsAfter - interruptsBefore > ALLOWED_INTERRUPTS) { // Disregard this run if interrupts were detected
				continue;
			} else { // Everything it fine, record this run as successful
				currentTime[expI] = tempTime; // Record how much time this iteration took
				experimentsRunSuccessfully++;
			}
		}
		// Calculate average time of running the experiment
		time[(int) i] = average_time(currentTime, experimentsRunSuccessfully); // 0 denotes a failed experiment (number of successful runs = 0)
		i++; // Iterate for easier access to array
	}
	// Output results
#ifdef SHOW_RESULTS
	printf("\nRESULTS - %d:\n", MAX_POWER);
	for (i = 0; i < MAX_POWER; ++i) {
		printf("%d. %.0f - %llu\n", i+1, pow(2.0, (double) i), time[i]);
	}
#endif

#ifdef OUTPUT_TO_FILE
	// Write to file
	write_to_csv(time);
#endif

	// Everything is good, return Success code
	return EXIT_SUCCESS;
}

// Experiment itself, aslo used for warming up cache
void experiment (unsigned char *testAr, unsigned char testCh, int n) {
	testAr[(int) n] = CHAR_TO_ADD; // Write 1 byte
	testCh = testAr[(int) n]; // Read 1 byte
}

// Calculate average time of running the experiment
unsigned long long average_time(unsigned long long *time, int timesRun) {
	if (timesRun == 0) // avoid division
		return 0;
	// Loop through times of all runs of the experiment
	int i;
	unsigned long long avTime = 0;
	for (i = 0; i < timesRun; ++i) {
		avTime += time[i];
	}
	return avTime / timesRun;
}
