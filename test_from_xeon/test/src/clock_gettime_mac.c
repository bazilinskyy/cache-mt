/*
 ============================================================================================
 Name        : clock_gettime_mac.c
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

 Description : clock_gettime for Mac OS
 Based on	 : http://stackoverflow.com/questions/11680461/monotonic-clock-on-osx
 ============================================================================================
 */
#ifdef __APPLE__
	#include "clock_gettime_mac.h"
	#include <mach/mach_time.h>

	#define MT_NANO (+1.0E-9)
	#define MT_GIGA UINT64_C(1000000000)

	static double mt_timebase = 0.0;
	static uint64_t mt_timestart = 0;

	int clock_gettime(clockid_t clk_id, struct timespec *tp)
	{
		kern_return_t retval = KERN_SUCCESS;
		if( clk_id == TIMER_ABSTIME)
		{
			if (!mt_timestart) {
				mach_timebase_info_data_t tb = { 0 };
				mach_timebase_info(&tb);
				mt_timebase = tb.numer;
				mt_timebase /= tb.denom;
				mt_timestart = mach_absolute_time();
			}

			double diff = (mach_absolute_time() - mt_timestart) * mt_timebase;
			tp->tv_sec = diff * MT_NANO;
			tp->tv_nsec = diff - (tp->tv_sec * MT_GIGA);
		}
		else // other clk_ids are mapped to the coresponding mach clock_service
		{
			clock_serv_t cclock;
			mach_timespec_t mts;

			host_get_clock_service(mach_host_self(), clk_id, &cclock);
			retval = clock_get_time(cclock, &mts);
			mach_port_deallocate(mach_task_self(), cclock);

			tp->tv_sec = mts.tv_sec;
			tp->tv_nsec = mts.tv_nsec;
		}

		return retval;
	}
#endif
