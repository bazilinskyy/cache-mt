/*
 ============================================================================
 Name        : test_1.c
 Author      : Pavlo Bazilinskyy
 Version     :
 Copyright   :
 Description : Test 1
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "mach_gettime.h"
#include "test_1.h"

#define MAX_POWER 19
#define BILLION  1000000000L;
#define DEBUG

int main(void) {
	printf("POWER %1f \n", pow(2.0, MAX_POWER));

	double time[(int) pow(2.0, (double) MAX_POWER)];
	struct timespec start, stop;
	for (double n = 1.0; n < (int) pow(2.0, (double) MAX_POWER); n *= 2.0) {

#ifdef DEBUG
//		if (fmod(n, 100000.0) == 0) {
//			printf("%.0f ", n);
//		}
		printf("%.0f ", n);
#endif
		// Calculate start time
		get_time_ns(start);

		// Run experiment
		unsigned char testAr[(int) n];
		unsigned char testCh;
		for (double i = 0.0; i < n; i++) {
			testAr[(int) n] = 'a';
			testCh = testAr[(int) n];
		}

		// Calculate finish time
		get_time_ns(stop);

		// Record difference
		time[(int) n] = calculate_time_ns(start, stop);
	}
#ifdef DEBUG
	printf("\nSize %d", sizeof(time) / sizeof(time[0]));
#endif

	return EXIT_SUCCESS;
}

int get_time_ns(struct timespec timeStruct) {
	 if( clock_gettime( CLOCK_REALTIME, &timeStruct) == -1 ) {
	      perror( "clock gettime" );
	      return 0;
	 }
	 return 1;
}

double calculate_time_ns(struct timespec timeStructStart, struct timespec timeStructFinish) {
	double accum = ( timeStructFinish.tv_sec - timeStructStart.tv_sec ) + (double)( timeStructFinish.tv_nsec - timeStructStart.tv_nsec ) / (double)BILLION;
	return accum;
}
