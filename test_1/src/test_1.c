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

#define MAX_POWER 20
#define BILLION  1000000000L;
#define DEBUG

int main(void) {
	unsigned long long time[MAX_POWER];
	struct timespec start, stop;
	int i = 0;
	for (long n = 1.0; n < pow(2.0, (double) MAX_POWER); n *= 2.0) {

#ifdef DEBUG
//		if (fmod(n, 100000.0) == 0) {
//			printf("%.0f ", n);
//		}
		printf("%ld ", n);
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
		time[i] = calculate_time_ns(start, stop);
		i++;
	}
#ifdef DEBUG
	printf("\nRESULTS:\n");
	for (int var = 1; var < MAX_POWER; ++var) {
		printf("%.0f,%llu\n", pow(2.0, (double) var), time[var]);
	}

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

unsigned long long calculate_time_ns(struct timespec timeStructStart, struct timespec timeStructFinish) {
	unsigned long long accum = ( timeStructFinish.tv_sec - timeStructStart.tv_sec ) + (double)( timeStructFinish.tv_nsec - timeStructStart.tv_nsec ) / (double)BILLION;
	return accum;
}
