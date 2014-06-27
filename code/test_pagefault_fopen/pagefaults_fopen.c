/*
 ============================================================================================
 Name        : pagefaults_fopen.c
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

 Description: Test different scenarios involving opening files to attempt to predict occurance
 			  of minor page faults.
 Run instructions: compile with gcc. No special flags needed.
 ============================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

unsigned long long get_page_fault(int choice); // Function to get a counter of page faults
char * file_to_string(char *f); // Return contents of the file f as a string.
 
 /*
 * Struct for information from the stat file.
 * Based on code from Stephen Brown.
 */
struct proc_stats {		// Type of data stored
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

/*
 * The main entry point of the programme.
 */
int main(int argc, const char ** argv) {
	unsigned long long pageFaultsB = get_page_fault(1); // 1 - minor page faults

	FILE *fp; // Pointer to a file

	// Open file
	if ((fp = fopen("/proc/interrupts", "r")) == NULL) {
		return (-1);
	}

	// Close file if still open.
	if (fp) {
		fclose(fp);
	}
	// Finished reading file

	unsigned long long pageFaultsA = get_page_fault(1);

	printf("1st time /proc/interrupts: Before: %llu After: %llu\n", pageFaultsB, pageFaultsA);

	pageFaultsB = get_page_fault(1);

	// Open file
	if ((fp = fopen("/proc/interrupts", "r")) == NULL) {
		return (-1);
	}

	// Close file if still open.
	if (fp) {
		fclose(fp);
	}
	// Finished reading file

	pageFaultsA = get_page_fault(1);

	printf("2nd time /proc/interrupts: Before: %llu After: %llu\n", pageFaultsB, pageFaultsA);

	pageFaultsB = get_page_fault(1);

	// Open file
	if ((fp = fopen("/proc/iomem", "r")) == NULL) {
		return (-1);
	}

	//Close the file if still open.
	if (fp) {
		fclose(fp);
	}
	// Finished reading file

	pageFaultsA = get_page_fault(1);

	printf("1st time /proc/iomem: Before: %llu After: %llu\n", pageFaultsB, pageFaultsA);

	pageFaultsB = get_page_fault(1);

	// Open file.
	if ((fp = fopen("/proc/iomem", "r")) == NULL) {
		return (-1);
	}

	//Close the file if still open.
	if (fp) {
		fclose(fp);
	}
	// Finished reading file

	pageFaultsA = get_page_fault(1);

	printf("2nd time /proc/iomem: Before: %llu After: %llu\n", pageFaultsB, pageFaultsA);

	char * str1 = file_to_string("/proc/interrupts");
	char * str2;


	while (strcmp(str1, str2) != 0) {
		pageFaultsB = get_page_fault(1);
		str2 = file_to_string("/proc/interrupts");
		pageFaultsA = get_page_fault(1);
	}

	printf("/proc/interrupts changed: Before: %llu After: %llu\n", pageFaultsB, pageFaultsA);
}

/*
 * Read information from the stat file (including data on detected page faults).
 * Based on code from Stephen Brown.
 */
int read_stat(char * filename, int pid, struct proc_stats *s) {
#ifndef __APPLE__ // Does not work on Mac OS
	const char *format =
			"%d %s %c %d %d %d %d %d %lu %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %lu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %lu %lu %llu";
	FILE *fp;

	fp = fopen(filename, "r");
	if (fp) {
		if (42
				== fscanf(fp, format, &s->pid, s->comm, &s->state, &s->ppid, &s->pgrp, &s->session, &s->tty_nr, &s->tpgid, &s->flags, &s->minflt, &s->cminflt,
						&s->majflt, &s->cmajflt, &s->utime, &s->stime, &s->cutime, &s->cstime, &s->priority, &s->nice, &s->num_threads, &s->itrealvalue,
						&s->starttime, &s->vsize, &s->rss, &s->rlim, &s->startcode, &s->endcode, &s->startstack, &s->kstkesp, &s->kstkeip, &s->signal,
						&s->blocked, &s->sigignore, &s->sigcatch, &s->wchan, &s->nswap, &s->cnswap, &s->exit_signal, &s->processor, &s->rt_priority, &s->policy,
						&s->delayacct_blkio_ticks)) {
			if (fp) {
				fclose(fp);
			}
			return 1;
		} else {
			if (fp) {
				fclose(fp);
			}
			return 0;
		}
	} else {
		return 0;
	}
#else
	return -1;
#endif
}

/*
 * Read counts of page faults from a proc_stats struct.
 * choice: 1 - minor, 2 - major
 */
unsigned long long get_page_fault(int choice) {
#ifndef __APPLE__
	struct proc_stats statsData;
	int self = getpid(); // Process ID

	char buf[256];
	sprintf(buf, "/proc/%d/stat", self);

	// Read data from the stats file
	read_stat(buf, self, &statsData);

	if (choice == 1) {
		return statsData.minflt;
	} else if (choice == 2) {
		return statsData.majflt;
	}

#else
	return -1;
#endif
}

static char result[8][8 * 1024]; 	// For storing contents of the file.
static int cycle = 0; 				// Counter of how many files have been stored in result.

/*
 * Save contents of a file in a string.
 */
char * file_to_string(char *f) {
	FILE *fp;			// File pointer
	char temp[512];		// Buffer for storing contents of a file

	cycle++;
	if (cycle == 8)
		cycle = 0;

	// Open file.
	if ((fp = fopen(f, "r")) == NULL) {
		return (char *) (-1);
	}

	// Initialise the result
	result[cycle][0] = 0;

	// Search for str and extract numeric.
	while (fgets(temp, 512, fp) != NULL) {
		strcat(result[cycle], temp);
	}

	// Check if ther eis a memory leak. This code may not work on machines with more than 4 cores.
	if (strlen(result[cycle]) > 8 * 1024) {
		printf("Memory error - strlen(result)==%lu, file size==%d\n", strlen(result[cycle]), 8 * 1024);
		if (fp) {
			fclose(fp);
		}
		exit(1);
	}

	//Close the file if still open.
	if (fp) {
		fclose(fp);
	}

	return &result[cycle][0];
}
