/** \file Shell.cpp
 * \brief Code implementation for Shell class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#include "Shell.h"
#include "ShellExplosion.h"

#include <Fl/fl_draw.h>

/** \brief Global vector of pointers to all Shell objects.
 *
 * This vector stores pointers to all Shell objects. It is self-managed.
 * When a Shell object is created, it adds itself to the vector and when
 * it is destroyed it removes itself from the vector.
 */
vector<Shell*> Shell::shells_;

/** \brief Constructor for Shell.
 *
 * The constructor adds the Shell object to the global vector of shells.
 * To create an object, use "new Shell(...)" and the object can be 
 * accessed via the Shell::shells() function.
 */
Shell::Shell(double startx, double starty, double endx, double endy, double radius) : Projectile(startx, starty, endx, endy, radius, SHELL_VELOCITY)
{
	shell_blast_radius_ = radius*SHELL_BLAST_FACTOR;
	shells_.push_back(this);
}

/** \brief Destructor for Shell.
 *
 * The destructor searches through the vector for the 'this' item and
 * removes it from the vector.
 */
Shell::~Shell()
{
	vector<Shell*>::iterator it;
	for (it = shells_.begin(); it != shells_.end(); it++)
	{
		if ((*it) == this)
		{
			shells_.erase(it);
			break;
		}
	}
}

/** \brief A function to return a const vector to the list of Shell objects.
 *
 * This function returns a const vector to the list of Shell objects so the
 * objects can be used. This is the only way of accessing the objects. To
 * access a member, use "Shell::shells()[index]".
 * \return Returns a const vector of pointers to the Shell objects.
 */
const vector<Shell*>& Shell::shells()
{
	return shells_;
}

/** \brief A function to generate explosions on death.
 *
 * This function should be called whenever a shell is deleted during the game.
 * This is not called in the destructor as it would cause problems on cleanup.
 * The function generates a ShellExplosion at the current location of the Shell.
 */
void Shell::on_death()
{
	new ShellExplosion(x(), y(), shell_blast_radius_);
}

/** \brief The interface to draw the Shell.
 *
 * This protected draw() function calls the private draw_shell() function
 * to draw the object
 */
void Shell::draw()
{
	draw_shell();
}

/** \brief The specialised drawing function for Shell.
 *
 * The draw_shell() function uses the FLTK routines to draw the Shell in
 * the form of a ball.
 */
void Shell::draw_shell()
{
	fl_color(GREY);
	fl_pie((int)(x()-radius()), (int)(y()-radius()), (int)(radius()*2), (int)(radius()*2), 0, 360);
#ifdef DEBUG
	fl_color(FL_RED);
	fl_circle(target_x(), target_y(), shell_blast_radius_);
	fl_color(FL_GRAY);
	fl_circle(target_x(), target_y(), radius());
#endif
}
