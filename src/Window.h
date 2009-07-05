/** \file Window.h
 * \brief Header file for Window class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef WINDOW_H
#define WINDOW_H

#include <Fl/Fl_Double_Window.H>

#include "enum.h"

/** \brief The Window class, inherits from Fl_Double_Window
 *
 * The Window class controls the flow of the game and handles things like
 * drawing routines and handling events.
 */
class Window : public Fl_Double_Window
{
public:
	Window(int w, int h, const char *l);
	virtual ~Window();

	int handle(int e);
protected:
	virtual void draw();
	virtual void animate();
	virtual void start_game();
	virtual void cleanup();
private:
	int gamestate;
	int score;
	int level;
	double lasttime;
	double currenttime;
	string strlvl;
	string strscr;
	string strstatus;
	stringstream oss;
};

#endif
