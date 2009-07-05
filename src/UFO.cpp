/** \file UFO.cpp
 * \brief Code implementation for UFO class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#include "UFO.h"
#include "Missile.h"
#include "PlayerItem.h"

#include <Fl/fl_draw.h>

/** \brief Global vector of pointers to all UFO objects.
 *
 * This vector stores pointers to all UFO objects. It is self-managed.
 * When a UFO object is created, it adds itself to the vector and when
 * it is destroyed it removes itself from the vector.
 */
vector<UFO*> UFO::ufos_;

/** \brief Constructor for UFO.
 *
 * The constructor adds the UFO object to the global vector of shells.
 * To create an object, use "new UFO(...)" and the object can be 
 * accessed via the UFO::ufos() function.
 */
UFO::UFO(double startx, double starty, double endx, double endy, double vel) : EnemyItem(startx, starty, endx, endy, UFO_RADIUS, vel)
{
	ufos_.push_back(this);
}

/** \brief Destructor for UFO.
 *
 * The destructor searches through the vector for the 'this' item and
 * removes it from the vector.
 */
UFO::~UFO()
{
	vector<UFO*>::iterator it;
	for (it = ufos_.begin(); it != ufos_.end(); it++)
	{
		if ((*it) == this)
		{
			ufos_.erase(it);
			break;
		}
	}
}

/** \brief A function to return a const vector to the list of UFO objects.
 *
 * This function returns a const vector to the list of UFO objects so the 
 * objects can be used. This is the only way of accessing the objects. To
 * access a member, use "UFO::ufos()[index]".
 * \return Returns a const vector of pointers to the UFO objects.
 */
const vector<UFO*>& UFO::ufos()
{
	return ufos_;
}

/** \brief The animate function for the UFO.
 *
 * This function extends the projectile animate() function call to allow for firing of
 * Missile objects.
 * \param t is the amount of time in seconds that has passed since last
		animation call.
 * \param level Optional: Current level, defaults to 1.
 * \return Returns 1 if Projectile::animate returns 1, else return 0
 */
int UFO::animate(double t, int level)
{
	if (Projectile::animate(t))
	{
		return 1;
	}
	else if ((rand() % (int)(UFO_FIRE_RATE/LEVEL_SCALE) == 0) && (Missile::missiles().size() < MAX_MISSILES))
	{
		if ((PlayerItem::playeritems().size() != 0) && (x() < WIN_WIDTH))
		{
			int index = rand() % PlayerItem::playeritems().size();
			PlayerItem *target = PlayerItem::playeritems()[index];
			new Missile(x(), y(), target->x(), target->y(), MISSILE_VELOCITY*LEVEL_SCALE);
		}
	}
	return 0;
}

/** \brief The interface to draw the UFO.
 *
 * This protected draw() function calls the private draw_ufo() function
 * to draw the object
 */
void UFO::draw()
{
	draw_ufo();
}

/** \brief The specialised drawing function for UFO.
 *
 * The draw_ufo() function uses the FLTK routines to draw the UFO in
 * the form of a flying saucer.
 */
void UFO::draw_ufo()
{
	fl_color(FL_BLACK);
	fl_begin_polygon();
	fl_begin_loop();
	fl_vertex(x(), y());
	fl_vertex(x() - 10, y());
	fl_vertex(x() - 20, y() + 10);
	fl_vertex(x() - 10, y() + 20);
	fl_vertex(x() + 10, y() + 20);
	fl_vertex(x() + 20, y() + 10);
	fl_vertex(x() + 10, y());
	fl_end_loop();
	fl_end_polygon();
	fl_color(FL_GRAY);
	fl_pie((int)(x() - 10), (int)(y() - 10), 20, 20, 0, 180);
#ifdef DEBUG
	fl_color(FL_RED);
	fl_circle(x(), y(), radius());
#endif
}
