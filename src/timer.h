/** \file timer.h
 * \brief Header file for time functions.
 *
 * The timer code is used to get the current time in seconds, type double,
 * and includes code to make it cross-platform between POSIX and Windows
 * systems.
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef TIMER_H
#define TIMER_H

double get_time();

#ifdef WIN32
#include <windows.h>
#include <winsock.h>

int gettimeofday(timeval *tv, timeval *tz);

#else
#include <sys/time.h>
#endif

#endif
