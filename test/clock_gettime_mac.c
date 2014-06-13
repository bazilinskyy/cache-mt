/*
 ============================================================================================
 Name        : clock_gettime_mac.c
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

 Description : clock_gettime for Mac OS
 Based on	 : http://stackoverflow.com/questions/11680461/monotonic-clock-on-osx
 ============================================================================================
 */

#ifdef __APPLE__ // For Mac OS only.
	#include "clock_gettime_mac.h"
	#include <mach/mach_time.h>

	/*
	 * Declarations.
	 */
	static double prefBase = 0.0; // Base of the timer
	static uint64_t prefStart = 0; // Starting point for the timer
	#define PREF_NANO (+1.0E-9) // Nano prefix
	#define PREF_GIGA UINT64_C(1000000000) // Giga prefix

	/*
	 * Port of clock_gettime(3) function for Mac OS.
	 */
	int clock_gettime(clockid_t clk_id, struct timespec *tp) {
		kern_return_t returnTime = KERN_SUCCESS; // Time difference to return

		// If click id equals to the timer's absolute time
		if (clk_id == TIMER_ABSTIME) {
			if (!prefStart) {
				mach_timebase_info_data_t tempTime = {0};
				mach_timebase_info(&tempTime); // Get a timestamp
				prefBase = tempTime.numer;
				prefBase /= tempTime.denom;
				prefStart = mach_absolute_time(); // Get absolute time
			}

			double diff = (mach_absolute_time() - prefStart) * prefBase;
			tp->tv_sec = diff * PREF_NANO; // Calculate seconds
			tp->tv_nsec = diff - (tp->tv_sec * PREF_GIGA); // Calculate nanoseconds
		}

		// If click id does not equal to the timer's absolute time
		else {
			clock_serv_t cclock;
			mach_timespec_t mts;

			host_get_clock_service(mach_host_self(), clk_id, &cclock);
			returnTime = clock_get_time(cclock, &mts); // Get a timestamp
			mach_port_deallocate(mach_task_self(), cclock);

			tp->tv_sec = mts.tv_sec; // Calculate seconds
			tp->tv_nsec = mts.tv_nsec; // Calculate nanoseconds
		}

		return returnTime; // Return the difference
	}
#endif
