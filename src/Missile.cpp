/** \file Missile.cpp
 * \brief Code implementation for Missile class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#include "Missile.h"
#include "PlayerItem.h"

#include <Fl/fl_draw.h>

/** \brief Global vector of pointers to all Missile objects.
 *
 * This vector stores pointers to all Missile objects. It is self-managed.
 * When a Missile object is created, it adds itself to the vector and when
 * it is destroyed it removes itself from the vector.
 */
vector<Missile*> Missile::missiles_;

/** \brief Constructor for Gun.
 *
 * The constructor adds the Gun object to the global vector of guns.
 * To create an object, use "new Missile(...)" and the object can be 
 * accessed via the Missile::missiles() function.
 */
Missile::Missile(double startx, double starty, double endx, double endy, double vel) : EnemyItem(startx, starty, endx, endy, MISSILE_RADIUS, vel)
{
	missiles_.push_back(this);
}

/** \brief Destructor for Missile.
 *
 * The destructor searches through the vector for the 'this' item and
 * removes it from the vector.
 */
Missile::~Missile()
{
	vector<Missile*>::iterator it;
	for (it = missiles_.begin(); it != missiles_.end(); it++)
	{
		if ((*it) == this)
		{
			missiles_.erase(it);
			break;
		}
	}
}

/** \brief A function to return a const vector to the list of Missile objects.
 *
 * This function returns a const vector to the list of Missile objects so the
 * objects can be used. This is the only way of accessing the objects. To
 * access a member, use "Missile::missiles()[index]".
 * \return Returns a const vector of pointers to the Missile objects.
 */
const vector<Missile*>& Missile::missiles()
{
	return missiles_;
}

/** \brief A function to check if the Missile has hit its target.
 *
 * This function checks to see if the Missile has hit its target, and if so it
 * destroys the target.
 * \return Returns boolean true if Missile has hit a target, false otherwise.
 */
bool Missile::collision_detect()
{
	bool ret = false;
	for (int i = 0; i < (int)PlayerItem::playeritems().size(); i++)
	{
		double x_diff = PlayerItem::playeritems()[i]->x() - x();
		double y_diff = PlayerItem::playeritems()[i]->y() - y();
		if (x_diff*x_diff + y_diff*y_diff <= (radius()+PlayerItem::playeritems()[i]->radius())*(radius()+PlayerItem::playeritems()[i]->radius()))
		{
#ifdef DEBUG
			cout << "missile interacted with player item " << i << endl;
#endif
			ret = true;
			PlayerItem::playeritems()[i]->on_death();
			delete PlayerItem::playeritems()[i];
			i--;
		}
	}
	return ret;
}

/** \brief The interface to draw the Missile.
 *
 * This protected draw() function calls the private draw_missile() function
 * to draw the object
 */
void Missile::draw()
{
	draw_missile();
}

/** \brief The specialised drawing function for Missile.
 *
 * The draw_missile() function uses the FLTK routines to draw the Missile as
 * a line from its start location to its current location.
 */
void Missile::draw_missile()
{
#ifdef DEBUG
	fl_color(FL_RED);
	fl_circle(x(), y(), radius());
#endif
	fl_color(FL_BLACK);
	fl_line((int)start_x(), (int)start_y(), (int)x(), (int)y());
}
