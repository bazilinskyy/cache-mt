/*
 ============================================================================================
 Name        : conf.h
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

 Description : The project configuration.
 ============================================================================================
 */

#ifndef CONF_H_
#define CONF_H_

// Configure test
#define MORE_EXPERIMENTS // Run a large number of experiments (refer to test_env.c)
#define TIMING 2 // 1 for RDTSC or 2 for clock_gettime
#define START_AFTER 1 // 1 for TIMER_TICK or 2 for TIME_INTERRUPT. Used with clock_gettime
// Configure experiment (each test consists of a number of experiments == TIMES_RUN_EXPERIMENT)
#define MAX_POWER 24
#define SET_HIGHEST_PRIORITY
#define WARM_CACHE
#define WARM_STRINGS_WITH_FILES
#define PROCESS_AFFINITY PIN_TO_ONE_CPU
#define PIN_TO_CPU 0
#define TIMES_RUN_TEST 3
#define TIMES_RUN_EXPERIMENT 10
// Every time reads a file it generates 1
#define ALLOWED_INTERRUPTS 5
#define ALLOWED_CONTEXT_SWITCHES 0
#define ALLOWED_PAGEFAULTS_MINOR 6
#define ALLOWED_PAGEFAULTS_MAJOR 0

// Output
#define DEBUG
//#define DETAILED_DEBUG
#define SHOW_RESULTS
#define OUTPUT_TO_FILE // Output measurements into CSV files.

#define BILLION  1000000000L
#define LONG_TO_ADD 1l
#define BIG_BUFFER_SIZE (8*1024) // For storying files as strings
#ifdef __APPLE__
#define CSV_FILE_CLEAN "results/test_1_i7_clean"
#define CSV_FILE_DIRTY "results/test_1_i7_dirty"
#else
#define CSV_FILE_CLEAN "results/test_1_xeon_clean"
#define CSV_FILE_DIRTY "results/test_1_xeon_dirty"
#endif
#endif /* CONF_H_ */
