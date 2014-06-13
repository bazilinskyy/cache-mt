/*
 ============================================================================================
 Name        : conf.h
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

 Description : The project configuration. To disable certain constants, comment their
 	 	 	   declarations
 ============================================================================================
 */

#ifndef CONF_H_
#define CONF_H_

/*
 * Defining strings for using with preprocessor.
 */
#define RDTSC 1 			// 1 for RDTSC for TIMING.
#define CLOCK_GETTIME 2 	// 2 for CLOCK_GETTIME for TIMING.
#define TIMER_TICK 1 		// 1 for TIMER_TICK for START_AFTER (used together with CLOCK_GETTIME).
#define TIME_INTERRUPT 2 	// 2 for TIME_INTERRUPT for START_AFTER.

/*
 * Configure experiments.
 */
#define MORE_EXPERIMENTS 		// Run a large number of experiments (refer to test_env.c).
#define TIMES_RUN_EXPERIMENT 1	// A number of times that each experiment is executed.
#define TIMING RDTSC 			// 1 for RDTSC or 2 for clock_gettime.
//#define USE_RDTSCP 			// Use RDTSCP instead of RDTSC.
#define START_AFTER TIMER_TICK 	// 1 for TIMER_TICK or 2 for TIME_INTERRUPT. Used with clock_gettime.

/*
 * Configure sub-experiments (each experiment consists of a number of sub-experiments; number == TIMES_RUN_EXPERIMENT).
 */
#define MAX_POWER 24				// The upper bound for the amount of data exchange in an experiment.
#define SET_HIGHEST_PRIORITY		// Set the highest priority to the experiment's process.
#define WARM_CACHE					// Warm up cache.
#define WARM_STRINGS_WITH_FILES		// Warm up loading files with information about interrupts and page faults.
//#define ALIGN_DATA 				// Align arrays that are used in inter-thread communication.
#define PROCESS_AFFINITY NA 		// Affinity of a process.
#define PIN_TO_CPU 0				// ID of a CPU that threads are pinned to initially.
#define TIMES_RUN_SUB_EXPERIMENT 10 // A number of times that each sub-experiment is executed. Average values are reported.
//#define CONSIDER_TIMEOUT			// Put a constraint on the execution time.
#define ALLOWED_INTERRUPTS 0		// A number of interrupts allowed in filtered data.
#define ALLOWED_CONTEXT_SWITCHES 0	// A number of context switches allowed in filtered data.
#define ALLOWED_PAGEFAULTS_MINOR 3 	// A number of minor page faults allowed in filtered data.
									// Every time reads a file one interrupt is generated.
#define ALLOWED_PAGEFAULTS_MAJOR 0  // A number of minor page faults allowed in filtered data.

/*
 * Output.
 */
//#define DEBUG						// Show debugging information.
//#define DETAILED_DEBUG			// Show extra (more detailed) information for debugging.
#define SHOW_RESULTS				// Output results to the console.
#define OUTPUT_TO_FILE 				// Output results as CSV files.

#define BILLION  1000000000L		// Definition for a billion.
#define LONG_TO_ADD 1l				// Quantum of data exchanged between threads.
#define BIG_BUFFER_SIZE (8*1024) 	// Buffer for storying files as strings.

/*
 * Names of CSV files for outputting results.
 */
#ifdef __APPLE__
	#define CSV_FILE_CLEAN "results/i7_clean"
	#define CSV_FILE_DIRTY "results/i7_dirty"
#else
	#define CSV_FILE_CLEAN "results/xeon_clean"
	#define CSV_FILE_DIRTY "results/xeon_dirty"
#endif
#endif /* CONF_H_ */
