/*
 ============================================================================================
 Name        : file_worker.c
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

 Description : File I/O for performance measurements
 ============================================================================================
 */

#include "file_worker.h"

// Based on code from Stephen Brown
int read_stat(int pid, struct proc_stats *s) {
#ifndef __APPLE__
    const char *format = "%d %s %c %d %d %d %d %d %lu %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %lu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %lu %lu %llu";

    char buf[256];
    FILE *proc;
    sprintf(buf,"/proc/%d/stat",pid);
    proc = fopen(buf,"r");
    if (proc) {
        if (42==fscanf(proc, format,
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
	   fclose(proc);
	   return 1;
        } else {
	   fclose(proc);
	   return 0;
        }
     } else {
	return 0;
     }
#else
	return -1;
#endif
}

// 1 - minor, 2 - major
unsigned long get_page_fault(int choice) {
#ifndef __APPLE__
	struct proc_stats statsData;
	int self = getpid(); // Process ID

	// Read data from the stats file
	read_stat(self, &statsData);

	if (choice == 1) {
		return statsData.minflt;
//		return statsData->cminflt);

	} else if (choice == 2) {
		return statsData.majflt;
//	    return statsData->cmajflt;
	}


#else
	return -1;
#endif
}

// Output time array into a CSV file. Type: 1 - clean, 2 - dirty
void write_to_csv(unsigned long long *time, int type) {
	// Open filestream
	FILE *f;
	if (type == 1) {
		f = fopen(CSV_FILE_CLEAN, "wb+");
	} else {
		f = fopen(CSV_FILE_DIRTY, "wb+");
	}

	if(f == NULL) //if file does not exist, create it
	{
	    printf("Error creating file.\n");
	}

	// Write to file
	// Write headers
	fprintf(f, "N,Time");
	// Write timing information
	int i = 0;
	for (i = 0; i < MAX_POWER; ++i) {
		fprintf(f, "\n%.0f,%llu", pow(2.0, (double) i), time[i]);
	}

	// Close filestream
	fclose(f);
#ifdef DEBUG
		printf("Finished writing to file %d.\n", type);
#endif
}

unsigned long long search_in_file(char *f, char *str, int find_numeric) {
	FILE *fp;
	char temp[512];

	// Open file
	if((fp = fopen(f, "r")) == NULL) {
		return(-1);
	}

	// Search for str and extract numeric
	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			if (find_numeric) {
				unsigned long long number = find_num_in_str(temp);
				return number;
			} else {
				printf("A match found\n.");
				printf("\n%s\n", temp);
			}
		}
	}

	//Close the file if still open.
	if(fp) {
		fclose(fp);
	}
   	return(0);
}

// Find a numeric in a string
unsigned long long find_num_in_str(char *str) {
	unsigned long long num = -1;
	sscanf(str,"%*[^0-9]%llu", &num);
	return num;
}
