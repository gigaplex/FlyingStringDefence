/** \file timer.cpp
 * \brief Code implementation for time functions.
 *
 * The timer code is used to get the current time in seconds, type double,
 * and includes code to make it cross-platform between POSIX and Windows
 * systems.
 * \author Tim Boundy
 * \date May 2007
 */
#include "timer.h"

/** \brief Function to return current time in seconds.
*
* \return Returns current time in seconds, type double.
*/
double get_time()
{
	timeval t;
	gettimeofday(&t, 0);
	double time = t.tv_sec + (t.tv_usec/1000000.0);
	return time;
}

#ifdef WIN32
#ifndef EPOCHFILETIME
#define EPOCHFILETIME (116444736000000000LL)
#endif
/** \brief Reimplementation of gettimeofday for Windows systems.
 *
 * Example taken from http://www.koders.com/c/fid5E8683BBF95B4EA5751C20773A687E6A6868A233.aspx
 * \param tv Address of timeval to dump the results into.
 * \param tz Deprecated value, is ignored. Pass zero as the second argument.
 * \return Returns 0 if tv parameter is non-zero, else returns 1 to indicate failure.
 */
int gettimeofday(timeval *tv, timeval *tz)
{
	FILETIME ft;
	LARGE_INTEGER li;
	__int64 t;
	if (tv)
	{
		GetSystemTimeAsFileTime(&ft);
		li.LowPart  = ft.dwLowDateTime;
		li.HighPart = ft.dwHighDateTime;
		t  = li.QuadPart;       /* In 100-nanosecond intervals */
		t -= EPOCHFILETIME;     /* Offset to the Epoch time */
		t /= 10;                /* In microseconds */
		tv->tv_sec  = (long)(t / 1000000);
		tv->tv_usec = (long)(t % 1000000);
		return 0;
	}
	else
	{
		return 1;
	}
}

#endif
