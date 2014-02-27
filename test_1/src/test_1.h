/*
 * test_1.h
 *
 *  Created on: Feb 24, 2014
 *  Author: Pavlo Bazilinskyy <pavlo.bazilinskyy@gmail.com>
 */
#ifndef TEST_1_H_
#define TEST_1_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#ifdef __APPLE__
	#include "mach_gettime.h"
#elif __linux // For future use
    // linux
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif
#include "hr_timer.h"
#include "conf.h"

int main(void);
int get_time_ns(struct timespec timeStruct);
unsigned long long calculate_time_ns(struct timespec timeStructStart, struct timespec timeStructFinish);

#endif /* TEST_1_H_ */
