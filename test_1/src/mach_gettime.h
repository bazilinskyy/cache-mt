/*
 ============================================================================================
 Name        : mach_gettime.h
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

 Description : Header for the clock_gettime for Mac OS
 Based on	 : http://stackoverflow.com/questions/11680461/monotonic-clock-on-osx
 ============================================================================================
 */
#ifdef __APPLE__

	#include <sys/types.h>
	#include <sys/_types/_timespec.h>
	#include <mach/mach.h>
	#include <mach/clock.h>

	#ifndef mach_time_h
	#define mach_time_h

	/* The opengroup spec isn't clear on the mapping from REALTIME to CALENDAR
	 being appropriate or not.
	 http://pubs.opengroup.org/onlinepubs/009695299/basedefs/time.h.html */

	// XXX only supports a single timer
	#define TIMER_ABSTIME -1
	#define CLOCK_REALTIME CALENDAR_CLOCK
	#define CLOCK_MONOTONIC SYSTEM_CLOCK

	typedef int clockid_t;

	/* the mach kernel uses struct mach_timespec, so struct timespec
		is loaded from <sys/_types/_timespec.h> for compatability */
	// struct timespec { time_t tv_sec; long tv_nsec; };

	int clock_gettime(clockid_t clk_id, struct timespec *tp);

	#endif
#endif
