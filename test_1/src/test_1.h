/*
 * test_1.h
 *
 *  Created on: Feb 24, 2014
 *      Author: Pavlo Bazilinskyy <pavlo.bazilinskyy@gmail.com>
 */
#ifndef TEST_1_H_
#define TEST_1_H_

int main(void);
int get_time_ns(struct timespec timeStruct);
unsigned long long calculate_time_ns(struct timespec timeStructStart, struct timespec timeStructFinish);

#endif /* TEST_1_H_ */
