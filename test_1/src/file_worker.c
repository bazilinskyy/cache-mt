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

// Output time array into a CSV file
void write_to_csv(unsigned long long time[]) {
	// Open filestream
	FILE *f = fopen(CSV_FILE, "wb+");
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
		printf("Finished writing to file.\n");
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
