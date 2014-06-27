/*
 ============================================================================================
 Name        : clock_gettime_mac.h
 Author      : Pavlo Bazilinskyy
 Version     : 1.0
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

	#ifndef clock_gettime_mac_h
	#define clock_gettime_mac_h

	/* Documentation on mapping from REALTIME to CALENDAR is not clear.
	 http://pubs.opengroup.org/onlinepubs/009695299/basedefs/time.h.html */
	#define TIMER_ABSTIME -1
	#define CLOCK_REALTIME CALENDAR_CLOCK
	#define CLOCK_MONOTONIC SYSTEM_CLOCK

	typedef int clockid_t;

	int clock_gettime(clockid_t clk_id, struct timespec *tp); // Struct timespec needs to be loaded from sys/_types/_timespec.h

	#endif
#endif
