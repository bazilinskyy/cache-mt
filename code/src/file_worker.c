/*
 ============================================================================================
 Name        : file_worker.c
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

 Description : Functions that do file I/O for supporting measuring performance and running
 	 	 	   experiments.
 ============================================================================================
 */

#include <sys/stat.h>
#include "file_worker.h"

static char result[8][8 * 5120]; 	// For storing contents of the file.
static int cycle = 0; 				// Counter of how many files have been stored in result.

/*
 * Structure for reading in information from the /proc/pid/stat file.
 * Based on code from Stephen Brown.
 */
int read_stat(char * filename, int pid, struct proc_stats *s) {
#ifndef __APPLE__ // Does not work on Mac OS
	const char *format = "%d %s %c %d %d %d %d %d %lu %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %lu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %lu %lu %llu";
	FILE *fp;

	fp = fopen(filename,"r");
	if (fp) {
		if (42==fscanf(fp, format,
						&s->pid,
						s->comm,
						&s->state,
						&s->ppid,
						&s->pgrp,
						&s->session,
						&s->tty_nr,
						&s->tpgid,
						&s->flags,
						&s->minflt,
						&s->cminflt,
						&s->majflt,
						&s->cmajflt,
						&s->utime,
						&s->stime,
						&s->cutime,
						&s->cstime,
						&s->priority,
						&s->nice,
						&s->num_threads,
						&s->itrealvalue,
						&s->starttime,
						&s->vsize,
						&s->rss,
						&s->rlim,
						&s->startcode,
						&s->endcode,
						&s->startstack,
						&s->kstkesp,
						&s->kstkeip,
						&s->signal,
						&s->blocked,
						&s->sigignore,
						&s->sigcatch,
						&s->wchan,
						&s->nswap,
						&s->cnswap,
						&s->exit_signal,
						&s->processor,
						&s->rt_priority,
						&s->policy,
						&s->delayacct_blkio_ticks
				)) {
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
 * Read information from the /proc/stat file.
 */
struct proc_stats get_page_fault_file() {
	struct proc_stats statsData; 	// Struct to hold data from the /proc/pid/stat file
	int self = getpid(); 			// Process ID

	char buf[256]; // Buffer for reading in content of the file

	// Read data from the stats file
	sprintf(buf, "/proc/%d/stat", self);
	read_stat(buf, self, &statsData);

	return statsData;
}

/*
 * Read counts of page faults from a proc_stats struct.
 * choice: 1 - minor, 2 - major
 */
unsigned long get_page_fault(struct proc_stats statsData, int choice) {
#ifndef __APPLE__
	if (choice == 1) {
		return statsData.minflt;

	} else {
		return statsData.majflt;
	}

#else
	return -1;
#endif
}

/*
 * Read counts of page faults from a string.
 * choice: 1 - minor, 2 - major
 */
unsigned long get_page_fault_from_string(char * string, int choice) {
#ifndef __APPLE__
	struct proc_stats statsData; // Stat for storing information from the /proc/pid/stat file
	int self = getpid(); // Process ID

	// First write string to a file.
	FILE *fp = fopen("temp", "wb+"); // Use a temporary file.
	if (fp != NULL)
	{
		fputs(string, fp);
		if (fp) {
			fclose(fp);
		}
	} else {
		printf("Error opening a temp file.\n");
	}

	// Read data from the stats file
	read_stat("temp", self, &statsData);

	// Return the count of detected page faults.
	if (choice == 1) {
		return statsData.minflt;

	} else {
		return statsData.majflt;
	}

#else
	return -1;
#endif
}

/*
 * Output time array into a CSV file. It takes in a number of arrays with information received when experiments were executed.
 * type: 1 - filtered, 2 - unfiltered.
 */
void write_to_csv(unsigned long long *time, unsigned long long *timeMin, int type, int testArg, int testId, int experimentsRun,
		unsigned long long interrupts[][TIMES_RUN_SUB_EXPERIMENT], unsigned long long pageFaultsMinor[][TIMES_RUN_SUB_EXPERIMENT],
		unsigned long long pageFaultsMajor[][TIMES_RUN_SUB_EXPERIMENT], unsigned long long contextSwitches[][TIMES_RUN_SUB_EXPERIMENT]) {


	FILE *fp; 				// Pointer to a file
	char fileName[100];		// Address of the file (name)

	/*
	 * Open the filestream.
	 */
	if (type == 1) {
		// Create file name for a new csv file
		snprintf(fileName, 100, "%s-%d-%d.csv", CSV_FILE_CLEAN, testArg, testId);
		fp = fopen(fileName, "wb+"); // Open the file
	} else {
		// Create file name for a new csv file
		snprintf(fileName, 100, "%s-%d-%d.csv", CSV_FILE_DIRTY, testArg, testId);
		fp = fopen(fileName, "wb+"); // Open the file
	}

	// If the file does not exist, create it
	if (fp == NULL)
	{
		printf("Error creating file.\n");
	}

	/*
	 * Write data into the file
	 */

	// Write headers
	fprintf(fp, "N,Time,TimMin"); // Header
	int j = 0;
	for (j = 0; j < TIMES_RUN_SUB_EXPERIMENT; ++j) { // For each sub-experiment.
		fprintf(fp, ",%d.INT,%d.PFMIN,%d.PFMAJ", j + 1, j + 1, j + 1);
	}

	// Write timing information
	int i = 0;
	long n = 1;
	for (i = 0; i < experimentsRun; ++i) { // For each processed experiment.
		fprintf(fp, "\n%lu,%llu,%llu", n * sizeof(long), time[i], timeMin[i]);

		int j = 0;
		for (j = 0; j < TIMES_RUN_SUB_EXPERIMENT; ++j) { // For each sub-experiment.
			fprintf(fp, ",%llu,%llu,%llu", interrupts[i][j], pageFaultsMinor[i][j], pageFaultsMajor[i][j]);
		}

		n = calculate_n(n); // Calculate the next amount of data exchanged.
	}

	// Close filestream
	if (fp) {
		fclose(fp);
	}
#ifdef DEBUG
	printf("Finished writing to file %d.\n", type);
#endif
}

/*
 * Search for substring *f in string *str.
 * find_numeric: find a numeric value in the result.
 */
unsigned long long search_in_file(char *f, char *str, int find_numeric) {
	FILE *fp;			// File pointer.
	char temp[512];		// Buffer for storing contents of a file.

	// Open file
	if ((fp = fopen(f, "r")) == NULL) {
		printf("Error: unable to open %s: %s\n", f, strerror(errno));
		return (-1);
	}

	// Search for f in str
	while (fgets(temp, 512, fp) != NULL) {
		if ((strstr(temp, str)) != NULL) {
			if (find_numeric) { // Extract a numeric value.
				unsigned long long number = find_num_in_str(temp);
				if (fp) {
					fclose(fp);
				}

				return number;
			} else { // Do not extract a numeric value, but output it.
				printf("A match found\n.");
				printf("\n%s\n", temp);
			}
		}
	}

	// Close the file if it still open.
	if (fp) {
		fclose(fp);
	}
	return (0);
}

/*
 * Search for *f in *str.
 * find_numeric: find a numeric value in the result.
 */
unsigned long long search_in_string(char *string, char *search_for, int find_numeric) {
	char *tmp = string;

	// Search for search_for and extract numeric.
	if ((strstr(string, search_for)) != NULL) {
		tmp = strstr(string, search_for);
		if (find_numeric) {
			char temp[30];
			memcpy(temp, &string[tmp - string], 30);
			unsigned long long number = find_num_in_str(temp);
			return number;
		} else {
			printf("A match found\n.");
		}
	}

	return (0);
}

/*
 * Save contents of a file in a string.
 */
char * file_to_string(char *f) {
	FILE *fp;			// File pointer
	char temp[512];		// Buffer for storing contents of a file

	// Cycles for reading in a file
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

	// Check if there is a memory leak. This code may not work on machines with more than 4 cores.
	if (strlen(result[cycle]) > 8 * 5120) {
		printf("Memory error - strlen(result)==%lu, file size==%d\n", strlen(result[cycle]), 8 * 1024);
		if (fp) {
			fclose(fp);
		}
		exit(1);
	}

	//Close the file if it still open.
	if (fp) {
		fclose(fp);
	}

	// Return a string with contents of a file.
	return &result[cycle][0];
}

/*
 * Find a numeric in a string
 */
unsigned long long find_num_in_str(char *str) {
	unsigned long long num = -1;	   // Support up to ull.
	sscanf(str, "%*[^0-9]%llu", &num); // Use regular expression.
	return num;
}

/*
 * Find all interrupts in a file f.
 */
struct proc_interrupts get_interrupts(int cpu) {
	char *interruptsString;
	interruptsString = file_to_string("/proc/interrupts"); // Read a file with interrupts into a string
	struct proc_interrupts result = get_interrupts_from_string(interruptsString, cpu);
	return result;
}

/*
 * Get all interrupts from a file f
 */
struct proc_interrupts get_interrupts_from_string(char *str, int cpu) {
	struct proc_interrupts result;
	result.i_LOC = search_in_string(str, "LOC:", 1);
	return result;
}

/*
 * Get a sum of all interrupts in the system
 */
unsigned long long get_interrupts_sum(char *f) {
	unsigned long long sum = 0;
	int n = 0;
	FILE *fp;			// File pointer
	char temp[512];		// Buffer for storing contents of a file

	// Open file
	if ((fp = fopen(f, "r")) == NULL) {
		printf("Error: unable to open /proc/interrupts: %s\n", strerror(errno));
		return (unsigned long long) (-1);
	}

	// Find numbers and add them to the sum
	while (fgets(temp, 512, fp) != NULL) {
		if (sscanf(&temp[5], "%d", &n) > 0) { // parse %d
			sum += n;
		}
	}

	//Close the file if still open. Close it.
	if (fp) {
		fclose(fp);
	}
	return sum;
}

/*
 * Get a sum of all interrupts in the system, from a previously saved string.
 */
unsigned long long get_interrupts_sum_in_string(char *str) {
	FILE *fp = fopen("temp", "wb+"); // Open the file

	if (fp != NULL) {
		fputs(str, fp); // Save the string str into the temp file
		if (fp) {
			fclose(fp);
		}
	} else {
		printf("Error opening a temp file.\n");
	}

	return get_interrupts_sum("temp"); // Pretend that the temp file is the interrupts file.
}
