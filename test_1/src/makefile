# ============================================================================
# Name        : makefile
# Author      : Pavlo Bazilinskyy
# Version     : 0.1
# Copyright   : Copyright (c) 2014, Pavlo Bazilinskyy <pavlo.bazilinskyy@gmail.com>
# 	 	 	   School of Computer Science, National University of Ireland, Maynooth
#
# 	 	 	   Permission is hereby granted, free of charge, to any person obtaining a copy
# 	 	 	   of this software and associated documentation files (the "Software"), to deal
# 	 	 	   in the Software without restriction, including without limitation the rights
# 	 	 	   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# 	 	 	   copies of the Software, and to permit persons to whom the Software is
# 	 	 	   furnished to do so, subject to the following conditions:
#
# 	 	 	   The above copyright notice and this permission notice shall be included in
# 	 	 	   all copies or substantial portions of the Software.
#
# 	 	 	   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# 	 	 	   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# 	 	 	   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# 	 	 	   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# 	 	 	   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# 	 	 	   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# 	 	 	   THE SOFTWARE.
#
# Description : Makefile fot Test 1 (measuring cache latency)
# Target 	  : MacBook Air with i7 and Xeon 5130
# ============================================================================


CC =gcc
IFLAGS =-I
WFLAG1 = -Wall
WFLAG2 = -Werror
WFLAG3 = -Wextra
#WFLAGS = $(WFLAG1) $(WFLAG2) $(WFLAG3)
#WFLAGS = $(WFLAG1)
OFLAGS = -g -O3
#SFLAG1 = -std=c99
SFLAG2 = -m64
SFLAGS = $(SFLAG1) $(SFLAG2)
DFLAGS = # -Doptions
UFLAGS = # Set on make command line only
CFLAGS = $(SFLAGS) $(DFLAGS) $(IFLAGS) $(OFLAGS) $(WFLAGS) $(UFLAGS)
LIBS =-lm
DEPS = test_1.h hr_timer.h
OBJ  = test_1.o hr_timer.o

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS += -lrt
endif
ifeq ($(UNAME_S),Darwin)
	DEPS += mach_gettime.h
	OBJ  += mach_gettime.o
endif

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

test_1: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~