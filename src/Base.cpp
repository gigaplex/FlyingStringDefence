/** \file Base.cpp
 * \brief Code implementation for Base class
 * 
 * \author Tim Boundy
 * \date May 2007
 */
#include "Base.h"

#include <Fl/fl_draw.h>

/** \brief Global vector of pointers to all Base objects.
 *
 * This vector stores pointers to all Base objects. It is self-managed.
 * When a Base object is created, it adds itself to the vector and when
 * it is destroyed it removes itself from the vector.
 */
vector<Base*> Base::bases_;

/** \brief Constructor for Base.
 *
 * The constructor adds the Base object to the global vector of bases.
 * To create an object, use "new Base(...)" and the object can be 
 * accessed via the Base::bases() function.
 */
Base::Base(double x, double y) : PlayerItem(x, y, BASE_RADIUS)
{
	bases_.push_back(this);
}

/** \brief Destructor for Base.
 *
 * The destructor searches through the vector for the 'this' item and
 * removes it from the vector.
 */
Base::~Base()
{
	vector<Base*>::iterator it;
	for (it = bases_.begin(); it != bases_.end(); it++)
	{
		if ((*it) == this)
		{
			bases_.erase(it);
			break;
		}
	}
}

/** \brief A function to return a const vector to the list of Base objects.
 *
 * This function returns a const vector to the list of Base objects so the
 * objects can be used. This is the only way of accessing the objects. To
 * access a member, use "Base::bases()[index]".
 * \return Returns a const vector of pointers to the Base objects.
 */
const vector<Base*>& Base::bases()
{
	return bases_;
}

/** \brief The interface to draw the Base.
 *
 * This protected draw() function calls the private draw_base() function
 * to draw the object
 */
void Base::draw()
{
	draw_base();
}

/** \brief The specialised drawing function for Base.
 *
 * The draw_base() function uses the FLTK routines to draw the Base in
 * the form of a house.
 */
void Base::draw_base()
{
#ifdef DEBUG // draw collision radius
	fl_color(FL_RED);
	fl_circle(x(), y(), radius());
#endif
	fl_color(FL_WHITE);
	fl_rectf((int)x()-20, (int)y()-15, 40, 30);
	fl_color(FL_BLACK);
	fl_rect((int)x()-20, (int)y()-15, 40, 30);
	fl_begin_polygon();
	fl_begin_loop();
	fl_vertex(x() - 30, y() - 15);
	fl_vertex(x(), y() - 25);
	fl_vertex(x() + 30, y() - 15);
	fl_end_loop();
	fl_end_polygon();
}
