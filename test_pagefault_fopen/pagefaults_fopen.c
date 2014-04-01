#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned long long get_page_fault(int choice);

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

int main(int argc, const char ** argv) {
	unsigned long long pageFaultsB = get_page_fault(1);

	// Read file
	FILE *fp;

	// Open file.
	if ((fp = fopen("/proc/interrupts", "r")) == NULL) {
		return (-1);
	}

	//Close the file if still open.
	if (fp) {
		fclose(fp);
	}
	// Finished reading file

	unsigned long long pageFaultsA = get_page_fault(1);

	printf("1st time /proc/interrupts: Before: %llu After: %llu\n", pageFaultsB, pageFaultsA);

	pageFaultsB = get_page_fault(1);

	// Open file.
	if ((fp = fopen("/proc/interrupts", "r")) == NULL) {
		return (-1);
	}

	//Close the file if still open.
	if (fp) {
		fclose(fp);
	}
	// Finished reading file

	pageFaultsA = get_page_fault(1);

	printf("2nd time /proc/interrupts: Before: %llu After: %llu\n", pageFaultsB, pageFaultsA);

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
}

// Based on code from Stephen Brown
int read_stat(char * filename, int pid, struct proc_stats *s) {
#ifndef __APPLE__
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

// 1 - minor, 2 - major
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
//		return statsData->cminflt);

	} else if (choice == 2) {
		return statsData.majflt;
//	    return statsData->cmajflt;
	}

#else
	return -1;
#endif
}
