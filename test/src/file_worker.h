/*
 ============================================================================================
 Name        : file_worker.h
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

 Description : Header for file I/O for performance measurements
 ============================================================================================
 */
#ifndef FILE_WORKER_H_
#define FILE_WORKER_H_

#include <stdio.h>
#include "conf.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "test_env.h"
#include <errno.h>

// Based on code from Stephen Brown
struct proc_stats {
    int pid;			// %d
    char comm[256];		// %s
    char state;			// %c
    int ppid;			// %d
    int pgrp;			// %d
    int session;		// %d
    int tty_nr;			// %d
    int tpgid;			// %d
    unsigned long flags;	// %lu
    unsigned long long minflt;	// %lu
    unsigned long long cminflt;	// %lu
    unsigned long long majflt;	// %lu
    unsigned long long cmajflt;	// %lu
    unsigned long utime;	// %lu
    unsigned long stime; 	// %lu
    long cutime;		// %ld
    long cstime;		// %ld
    long priority;		// %ld
    long nice;			// %ld
    long num_threads;		// %ld
    long itrealvalue;		// %ld
    unsigned long starttime;	// %lu
    unsigned long vsize;	// %lu
    long rss;			// %ld
    unsigned long rlim;		// %lu
    unsigned long startcode;	// %lu
    unsigned long endcode;	// %lu
    unsigned long startstack;	// %lu
    unsigned long kstkesp;	// %lu
    unsigned long kstkeip;	// %lu
    unsigned long signal;	// %lu
    unsigned long blocked;	// %lu
    unsigned long sigignore;	// %lu
    unsigned long sigcatch;	// %lu
    unsigned long wchan;	// %lu
    unsigned long nswap;	// %lu
    unsigned long cnswap;	// %lu
    int exit_signal;		// %d
    int processor;		// %d
    unsigned long rt_priority;	// %lu
    unsigned long policy;	// %lu
    unsigned long long delayacct_blkio_ticks;	// %llu
};

// Structure for interrupts
struct proc_interrupts {
    unsigned long long i_0;
    unsigned long long i_1;
    unsigned long long i_6;
    unsigned long long i_7;
    unsigned long long i_9;
    unsigned long long i_12;
    unsigned long long i_14;
    unsigned long long i_15;
    unsigned long long i_18;
    unsigned long long i_19;
    unsigned long long i_20;
    unsigned long long i_21;
    unsigned long long i_22;
    unsigned long long i_40;
    unsigned long long i_41;
    unsigned long long i_42;
    unsigned long long i_43;
    unsigned long long i_44;
    unsigned long long i_NMI;
    unsigned long long i_LOC;
    unsigned long long i_SPU;
    unsigned long long i_RES;
    unsigned long long i_CAL;
    unsigned long long i_TLB;
    unsigned long long i_TRM;
    unsigned long long i_ERR;
    unsigned long long i_MIS;
};

void write_to_csv(unsigned long long *time, int type, int testId, int experimentsRun); // Output time array into a CSV file
unsigned long long search_in_file(char *f, char *str, int find_numeric); // Search for a string in the file fname
unsigned long long search_in_string(char *string, char *search_for, int find_numeric); // Search for a substring search_for in string.
unsigned long long find_num_in_str(char *str); // Find a numeric in a string
unsigned long get_page_fault(struct proc_stats statsData, int choice);
unsigned long get_page_fault_from_string(char * string, int choice);
int read_stat(char * filename, int pid, struct proc_stats *s);
char * file_to_string(char *f); // Create a string with contents of the file f.
struct proc_interrupts get_interrupts(int cpu);
struct proc_interrupts get_interrupts_from_string(char *str, int cpu);
unsigned long long get_interrupts_sum(char *f);
unsigned long long get_interrupts_sum_in_string(char *str);
struct proc_stats get_page_fault_file();

#endif /* FILE_WORKER_H_ */
