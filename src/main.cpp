/** \file main.cpp
 * \brief Main file for Flying String Defence project
 *
 * \author Tim Boundy
 * \date May 2007
 */
#include <Fl/Fl.H>
#include <stdlib.h>

#include "Window.h"

void timer_callback(void*);

/** \brief Program entry point.
 */
int main (int argc, char **argv) {
	Window win(WIN_WIDTH, WIN_HEIGHT, "Flying String Defence");
	Fl::add_timeout(1/FPS, timer_callback);
	win.show(argc, argv);
	return Fl::run();
}

/** \brief Timer callback to create timed events.
 */
void timer_callback(void*)
{
	if (Fl::first_window())
	{
		Fl::first_window()->handle(TIMER_CALLBACK);
		Fl::repeat_timeout(1/FPS, timer_callback);
	}
}

