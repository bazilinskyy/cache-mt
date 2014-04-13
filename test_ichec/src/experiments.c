/*
 ============================================================================================
 Name        : experiments.c
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

 Description : The experiments.
 Target		 : MacBook Air with i7 and Xeon 5130
 ============================================================================================
 */

#include "experiments.h"

// Test 1 (measuring cache latency)
void experiment_1(int n) {
	long *testAr = malloc(sizeof(long) * n * 2);
	if (testAr == NULL) { // Array for manipulating data
		printf("Error with allocating space for the array\n");
		exit(1);
	}
	long testLong = 0; // 4 bytes of data

	int i;
	for (i = 0; i < n; i++) { // Write and read 1 byte n times
		testAr[(int) n] = LONG_TO_ADD; // Write 1 byte
		testLong += testAr[(int) n]; // Read 1 byte
	}
	free(testAr);
}
