/*
 ============================================================================================
 Name        : test.c
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

 Description  : The main file for preparing the testing environment and executing
 experiments.
 Target		 : MacBook Air with i7 and Xeon 5130
 ============================================================================================
 */

#include "test.h"

static int experiment_id = 0;

int main(int argc, char *argv[]) {
	// argc should be of length 2 for correct execution
	if (argc != 2) {
		// Print argv[0] assuming it is the program name
		printf("Missing arguments. Usage: %s test_id\n", argv[0]);
		exit(1);
	} else {
		sscanf(argv[1], "%d", &experiment_id);
	}

	/* Testing different aspects of the system/testing environment */

	// Test clock_gettime
	//test_clock_gettime();
	// Test clock_getres
	//test_clock_getres();
	// Testing interrupt time. Not for Mac.
	//test_interrupt_time();
	// Testing rdrsc
	//test_rdtsc();

	/* Set process priority to the highest possible value */
#ifdef SET_HIGHEST_PRIORITY
	set_highest_process_priority();
#endif

	// TODO fix pthreads on Mac OS
#ifndef __APPLE__
	pthread_t thread1;
	int rc;

	// Run in pthread
	rc = pthread_create(&thread1, NULL, pthread_main, (void *)NULL);
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	pthread_join(thread1, NULL);
#else
	pthread_main((void *) 1);
#endif
	// Everything is good, return Success code
	return EXIT_SUCCESS;
}

// Function run in the thread
void *pthread_main(void *params) {
	int i = 0;
	long n;

	int threadId = (int) params; // Get the thread ID

	// Set up thread affinity.
#if PROCESS_AFFINITY == PIN_TO_ONE_CPU
	pin_thread_to_core(PIN_TO_CPU); // Pin this pthread to the PIN_TO_CPU
#endif

	unsigned long long *time = malloc(sizeof(unsigned long long) * MAX_POWER * 10); // Record time for clean runs.
	if (time == NULL) {
		printf("Error with allocating space for the array\n");
		exit(1);
	}
	unsigned long long *timeDirty = malloc(sizeof(unsigned long long) * MAX_POWER * 10); // Record time for dirty runs.
	if (timeDirty == NULL) {
		printf("Error with allocating space for the array\n");
		exit(1);
	}

	unsigned long long *currentTime = malloc(sizeof(unsigned long long) * TIMES_RUN_EXPERIMENT); // Record times of experiments in the run.
	if (time == NULL) {
		printf("Error with allocating space for the array\n");
		exit(1);
	}
	unsigned long long *currentTimeDirty = malloc(sizeof(unsigned long long) * TIMES_RUN_EXPERIMENT); // Record times of experiments in the run.
	if (time == NULL) {
		printf("Error with allocating space for the array\n");
		exit(1);
	}

	int testId = 0; // ID of the test. Used for output.
	for (testId = 0; testId < TIMES_RUN_TEST; ++testId) { // Run tests=

		// Reset arrays
		memcpy(&time[0], &(typeof(time)){ 0 }, sizeof time);
		memcpy(&timeDirty[0], &(typeof(timeDirty)){ 0 }, sizeof timeDirty);
		printf ("%llu time[1]\n", time[1]);


		// Run experiments
		int experimentsRun = 0;
		for (n = 1.0; n < pow(2.0, (double) MAX_POWER);) {
			experimentsRun++;

#ifdef WARM_CACHE //Warm up cache
			experiment_1(0); // Call experiment function once to warm up cache
#endif
#ifdef WARM_STRINGS_WITH_FILES // Create two copies of each string used for storing files to fill in memory with this data.
			warm_strings_with_files();
#endif

			// Run each experiment for TIMES_RUN_EXPERIMENT times
			int expId = 0; // The ID of the experiment
			int experimentsRunSuccessfully = 0; // Record how many times the experiment was run successfully
			for (expId = 0; expId < TIMES_RUN_EXPERIMENT; ++expId) { // Run experiments in the test


#ifdef DETAILED_DEBUG
					printf("* Test: %d Experiment: %d\n", testId + 1, expId + 1);
#endif

				// Values for gethering data about the environment
				unsigned long long interruptsBefore = 0;
				unsigned long long interruptsAfter = 0;
				unsigned long long pageFaultsMinorBefore = 0;
				unsigned long long pageFaultsMinorAfter = 0;
				unsigned long long pageFaultsMajorBefore = 0;
				unsigned long long pageFaultsMajorAfter = 0;
				unsigned long long contextSwitchesBefore = 0;
				unsigned long long contextSwitchesAfter = 0;

#ifndef __APPLE__
				// Strings for storing contents of the files
				char *interruptsBeforeString;
				char *pageFaultsBeforeString;
				char *contextSwitchesBeforeString;

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

				// Save files with information on interrupts, page faults, and context switches into strings

				interruptsBeforeString = file_to_string("/proc/interrupts");

				// Add stat to the name of the file
				char fileNameStat[100];
				snprintf(fileNameStat, 100, "%s%s", fileName, "/stat");
				pageFaultsBeforeString = file_to_string(fileNameStat);

				// Add status to the name of the file
				char fileNameStatus[100];
				snprintf(fileNameStatus, 100, "%s%s", fileName, "/status");
				contextSwitchesBeforeString = file_to_string(fileNameStatus);
#else
				//TODO read for Mac OS
#endif
				/* Prepare for running the experiment. */

#if TIMING == RDTSC // Use RDTSC to measure time
				// Use RDTSC to measure time
				unsigned long long timeBefore, timeAfter;


				// ******** RUN EXPERIMENT ***********
				int j;
				for (j = 0; j < 2; j++) {
					usleep(10);
					timeBefore = rdtsc();
					if (experiment_id == 1) {
						experiment_1(n);
					}
					timeAfter = rdtsc();
				}
				// Decide which experiment to run


				// ******** FINISH EXPERIMENT ********

#elif TIMING == CLOCK_GETTIME // Use clock_gettime

#if START_AFTER == TIMER_TICK
				// Start after the timer ticks.
				struct timespec temp_time1, start;

				get_time_ns(&temp_time1);
				get_time_ns(&start);

				while (start.tv_sec == temp_time1.tv_sec && temp_time1.tv_nsec == start.tv_nsec) {
					get_time_ns(&start);
				}
#elif START_AFTER == TIME_INTERRUPT
				// Start after the time interrupt
				unsigned long long interrupts1 = search_in_file("/proc/interrupts", "LOC:", 1);
				unsigned long long interrupts2 = search_in_file("/proc/interrupts", "LOC:", 1);

				while (interrupts1 == interrupts2) {
					interrupts2 = search_in_file("/proc/interrupts", "LOC:", 1);
					printf("%llu %llu\n", interrupts1, interrupts2);
				}
				// Calculate the start time
				struct timespec start;
				get_time_ns(&start);
#endif
				// ******** RUN EXPERIMENT ***********

				// Decide which experiment to run
				if (experiment_id == 1) {
					experiment_1(n);
				}

				// ******** FINISH EXPERIMENT ********
				struct timespec stop;
				get_time_ns(&stop); // Calculate finish time
#endif



				// Get readings on interrupts, pagefaults and context switched before running the experiment
#ifndef __APPLE__
//				interruptsAfter = search_in_file("/proc/interrupts", "LOC:", 1);
				interruptsAfter = get_interrupts_sum("/proc/interrupts");
				// Get file once to avoid getting one extra minor page fault
				struct proc_stats stat_file = get_page_fault_file();
				pageFaultsMinorAfter = get_page_fault(stat_file, 1);
				pageFaultsMajorAfter = get_page_fault(stat_file, 2);
				contextSwitchesAfter = search_in_file(fileNameStatus, "voluntary_ctxt_switches:", 1);

				// Retrieve information from saved into strings files.
//				interruptsBefore = search_in_string(interruptsBeforeString, "LOC:", 1);
				interruptsBefore = get_interrupts_sum_in_string(interruptsBeforeString);
				pageFaultsMinorBefore = get_page_fault_from_string(pageFaultsBeforeString, 1);
				pageFaultsMajorBefore = get_page_fault_from_string(pageFaultsBeforeString, 2);
				contextSwitchesBefore = search_in_string(contextSwitchesBeforeString, "voluntary_ctxt_switches:", 1);

#ifdef DETAILED_DEBUG
				printf("INT B: %llu :: ", interruptsBefore);
				printf("PF Min B: %llu :: ", pageFaultsMinorBefore);
				printf("PF Maj B: %llu :: ", pageFaultsMajorBefore);
				printf("CS B: %llu\n", contextSwitchesBefore);
				printf("INT A: %llu :: ", interruptsAfter);
				printf("PF Min A: %llu :: ", pageFaultsMinorAfter);
				printf("PF Maj A: %llu :: ", pageFaultsMajorAfter);
				printf("CS A: %llu\n", contextSwitchesAfter);
#endif

#else
				//TODO read for Mac OS
#endif
				// Record the time difference.
				// Use RDTSC
#if TIMING == RDTSC
				unsigned long long tempTime = timeAfter - timeBefore; // Calculate how much time this run took
#elif TIMING == CLOCK_GETTIME
				unsigned long long tempTime = calculate_time_ns(start, stop); // Calculate how much time this run took
#endif
				// Record dirty time.
				currentTimeDirty[expId] = tempTime; // Record how much time this iteration took

				// Disregard experiment if comparison of it with MIN and MAX makes it invalid
				//TODO verify with Stephen
				unsigned long long minTime = n * 1; // Lower bound for the duration of the run
				unsigned long long maxTime = n * 100000; // Upper bound for the duration of the run
				if (tempTime < minTime || tempTime > maxTime) { // Disregard this run if it does not meet timing requirements
					continue;
				} else if (pageFaultsMinorAfter - pageFaultsMinorBefore > ALLOWED_PAGEFAULTS_MINOR) { // Disregard this run if minor pagefaults were detected
#ifdef DEBUG
					printf("PFMIN. TEST: %ld. EXP: %d DIFF: %llu LIMIT: %d\n", n, expId + 1, pageFaultsMinorAfter - pageFaultsMinorBefore,
					ALLOWED_PAGEFAULTS_MINOR);
#endif
					continue;
				} else if (pageFaultsMajorAfter - pageFaultsMajorBefore > ALLOWED_PAGEFAULTS_MAJOR) { // Disregard this run if major pagefaults were detected
#ifdef DEBUG
					printf("PFMAJ. TEST: %ld. EXP: %d DIFF: %llu LIMIT: %d\n", n, expId + 1, pageFaultsMajorAfter - pageFaultsMajorBefore,
					ALLOWED_PAGEFAULTS_MAJOR);
#endif
					continue;
				} else if (contextSwitchesAfter - contextSwitchesBefore > ALLOWED_CONTEXT_SWITCHES) { // Disregard this run if voluntary context switches were detected
#ifdef DEBUG
					printf("CS. TEST: %ld. EXP: %d DIFF: %llu LIMIT: %d\n", n, expId + 1, contextSwitchesAfter - contextSwitchesBefore,
					ALLOWED_CONTEXT_SWITCHES);
#endif
					continue;
				} else if (interruptsAfter - interruptsBefore > ALLOWED_INTERRUPTS) { // Disregard this run if interrupts were detected
#ifdef DEBUG
					printf("INT. TEST: %ld. EXP: %d DIFF: %llu LIMIT: %d\n", n, expId + 1, interruptsAfter - interruptsBefore,
					ALLOWED_INTERRUPTS);
#endif
					continue;
				} else { // Everything it fine, record this run as successful
					currentTime[experimentsRunSuccessfully] = tempTime; // Record how much time this iteration took
					experimentsRunSuccessfully++;
				}
			}
			// Calculate average time of running the experiment
			time[(int) i] = average_time(currentTime, experimentsRunSuccessfully); // 0 denotes a failed experiment (number of successful runs = 0)
			//printf("time: %llu aver: %llu\n ", time[(int) i], average_time(currentTime, experimentsRunSuccessfully));

			// TODO bug with time showing as 0 starting from the 2nd test on Mac.
//			if (testId == 1)
//				printf("%llu\n ", time[(int) i]);
			timeDirty[(int) i] = average_time(currentTimeDirty, TIMES_RUN_EXPERIMENT); // 0 denotes a failed experiment (number of successful runs = 0)
			i++; // Iterate for easier access to array

			// Determine next value for n based on the current value
			n = calculate_n(n);

		} // End of the experiment loop.

		// Output results
#ifdef SHOW_RESULTS
		printf("\n%d. RESULTS Clean - %d:\n", testId, experimentsRun);
		long n = 1;
//		 See bug above: bug with time showing as 0 starting from the 2nd test on Mac.
//		if (testId == 1)
//			printf("%llu\n ", time[1]);
		for (i = 1; i <= experimentsRun; ++i) {
			printf("%d. %lu - %llu\n", i, n * sizeof(long), time[i - 1]);
			n = calculate_n(n);
		}

		n = 1;
		printf("\n%d. RESULTS Dirty - %d:\n", testId, experimentsRun);
		for (i = 1; i <= experimentsRun; ++i) {
			printf("%d. %lu - %llu\n", i, n * sizeof(long), timeDirty[i - 1]); // Assuming that we write longs.
			n = calculate_n(n);
		}
#endif

#ifdef OUTPUT_TO_FILE
		// Write to file
		write_to_csv(time, 1, testId, experimentsRun);
		write_to_csv(timeDirty, 2, testId, experimentsRun);
#endif

	} // End of the test loop.

	// Free memory and exit
	free(timeDirty);
	free(time);
	free(currentTime);
	free(currentTimeDirty);

	return (void *) 1;
}

// Pin thread to a particular core
int pin_thread_to_core(int coreId) {
#ifndef __APPLE__
	int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
	if (coreId < 0 || coreId >= num_cores)
	return EINVAL;

	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(coreId, &cpuset);

	pthread_t current_thread = pthread_self();
	return pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
#else
	// TODO set affinity on Mac.
	return -1;
#endif
}

// Set priority of the current to be the highest
// From: http://stackoverflow.com/questions/29621/change-own-process-priority-in-c
// man http://linux.die.net/man/3/setpriority
// TODO set to FIFO real time process
int set_highest_process_priority(void) {
	setpriority(PRIO_PROCESS, 0, -20);
	return 1;
}
