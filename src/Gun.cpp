/** \file Gun.cpp
 * \brief Code implementation for Gun class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#include "Gun.h"

#include <Fl/fl_draw.h>
#include <math.h>

/** \brief Global vector of pointers to all Gun objects.
 *
 * This vector stores pointers to all Gun objects. It is self-managed.
 * When a Gun object is created, it adds itself to the vector and when
 * it is destroyed it removes itself from the vector.
 */
vector<Gun*> Gun::guns_;

/** \brief Constructor for Gun.
 *
 * The constructor adds the Gun object to the global vector of guns.
 * To create an object, use "new Gun(...)" and the object can be 
 * accessed via the Gun::guns() function. The constructor also initialises
 * its variables.
 */
Gun::Gun(double x, double y, double width) : PlayerItem(x, y, GUN_RADIUS)
{
	target_x_ = 0;
	target_y_ = 0;
	barrel_width_ = width;
	valid_target = false;
	guns_.push_back(this);
}

/** \brief Destructor for Gun.
 *
 * The destructor searches through the vector for the 'this' item and
 * removes it from the vector.
 */
Gun::~Gun()
{
	vector<Gun*>::iterator it;
	for(it = guns_.begin(); it != guns_.end(); it++)
	{
		if((*it) == this)
		{
			guns_.erase(it);
			break;
		}
	}
}

/** \brief A function to return a const vector to the list of Gun objects.
 *
 * This function returns a const vector to the list of Gun objects so the
 * objects can be used. This is the only way of accessing the objects. To
 * access a member, use "Gun::guns()[index]".
 * \return Returns a const vector of pointers to the Gun objects.
 */
const vector<Gun*>& Gun::guns()
{
	return guns_;
}

/** \brief A function to change the target location of the Gun.
 *
 * This function accepts the x and y co-ordinates of the new target for
 * the gun.
 * \param x The x co-ordinate of the new target, type double.
 * \param y The y co-ordinate of the new target, type double.
 */
void Gun::target(double x, double y)
{
	target_x_ = x;
	target_y_ = y;
}

/** \brief A function to read the x co-ordinate of the target.
 *
 * \return Returns the x co-ordinate of the target, type double.
 */
double Gun::target_x()
{
	return target_x_;
}

/** \brief A function to read the y co-ordinate of the target.
 *
 * \return Returns the y co-ordinate of the target, type double.
 */
double Gun::target_y()
{
	return target_y_;
}

/** \brief A function to read if the target is valid.
 *
 * \return Returns the validity of the target (bool true, false).
 */
bool Gun::target_valid()
{
	return valid_target;
}

/** \brief A function to read the value of the barrel_width.
 *
 * \return Returns width of the barrel, type double.
 */
double Gun::barrel_width()
{
	return barrel_width_;
}

/** \brief A function to set the value of the barrel_width.
 *
 * \param width The width of the barrel, type double.
 */
void Gun::barrel_width(double width)
{
	barrel_width_ = width;
} 

/** \brief The interface to draw the Gun.
 *
 * This protected draw() function calls the private draw_gun() function
 * to draw the object
 */
void Gun::draw()
{
	draw_gun();
}

/** \brief The specialised drawing function for Gun.
 *
 * The draw_gun() function uses the FLTK routines to draw the Gun in
 * the form of a turret. It checks to see if the target is valid and
 * sets the valid_target flag appropriately.
 */
void Gun::draw_gun()
{
#ifdef DEBUG // draw collision radius
	fl_color(FL_RED);
	fl_circle(x(), y(), radius());
#endif
	if (target_y() - y() < 0) // gun can't aim down
	{
		theta = atan((double)(target_x() - x()) / (double)(target_y() - y()));
		valid_target = true;
	}
	else
	{
		valid_target = false;
	}
	
	fl_color(FL_BLACK);
	fl_begin_polygon(); // draw barrel
	fl_begin_loop();
	fl_vertex(x()+barrel_width()/2*cos(theta),y()-barrel_width()/2*sin(theta));
	fl_vertex(x()-barrel_width()/2*cos(theta),y()+barrel_width()/2*sin(theta));
	fl_vertex(x()-barrel_width()/2*cos(theta)-BARREL_LENGTH*sin(theta), y()+barrel_width()/2*sin(theta)-BARREL_LENGTH*cos(theta));
	fl_vertex(x()+barrel_width()/2*cos(theta)-BARREL_LENGTH*sin(theta), y()-barrel_width()/2*sin(theta)-BARREL_LENGTH*cos(theta));
	fl_end_loop();
	fl_end_polygon();
	
	fl_color(FL_DARK_GREY);
	// draw base of gun
	fl_pie((int)x()-GUN_BASE_RADIUS/2, (int)y()-GUN_BASE_RADIUS/4, GUN_BASE_RADIUS, GUN_BASE_RADIUS, 0, 180);
	fl_color(FL_BLACK);
	fl_circle(x(),y(),2); // draw pivot pin
}
