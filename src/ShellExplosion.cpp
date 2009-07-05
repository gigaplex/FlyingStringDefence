/** \file ShellExplosion.cpp
 * \brief Code implementation for ShellExplosion class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#include "ShellExplosion.h"
#include "EnemyItem.h"

#include <Fl/fl_draw.h>

/** \brief Global vector of pointers to all ShellExplosion objects.
 *
 * This vector stores pointers to all ShellExplosion objects. It is self-managed.
 * When a ShellExplosion object is created, it adds itself to the vector and when
 * it is destroyed it removes itself from the vector.
 */
vector<ShellExplosion*> ShellExplosion::shellexplosions_;

/** \brief Constructor for ShellExplosion.
 *
 * The constructor adds the ShellExplosion object to the global vector of shells.
 * To create an object, use "new ShellExplosion(...)" and the object can be 
 * accessed via the ShellExplosion::shellexplosions() function.
 */
ShellExplosion::ShellExplosion(double x, double y, double r) : Explosion(x, y, r)
{
	max_radius_ = r;
	shellexplosions_.push_back(this);
}

/** \brief Destructor for ShellExplosion.
 *
 * The destructor searches through the vector for the 'this' item and
 * removes it from the vector.
 */
ShellExplosion::~ShellExplosion()
{
	vector<ShellExplosion*>::iterator it;
	for (it = shellexplosions_.begin(); it != shellexplosions_.end(); it++)
	{
		if ((*it) == this)
		{
			shellexplosions_.erase(it);
			break;
		}
	}
}

/** \brief A function to return a const vector to the list of ShellExplosion objects.
 *
 * This function returns a const vector to the list of ShellExplosion objects so
 * the objects can be used. This is the only way of accessing the objects. To
 * access a member, use "ShellExplosion::shellexplosions()[index]".
 * \return Returns a const vector of pointers to the ShellExplosion objects.
 */
const vector<ShellExplosion*>& ShellExplosion::shellexplosions()
{
	return shellexplosions_;
}

/** \brief The interface to draw the ShellExplosion.
 *
 * This protected draw() function calls the private draw_shellexplosion() function
 * to draw the object
 */
void ShellExplosion::draw()
{
	draw_shellexplosion();
}

/** \brief The specialised drawing function for ShellExplosion.
 *
 * The draw_shell() function uses the FLTK routines to draw the explosion in
 * the form of an expanding fireball. The initial shockwave is invisible, so do
 * not draw if within initial period.
 */
void ShellExplosion::draw_shellexplosion()
{
	if (timealive() > SE_INITIAL_PERIOD)
	{
		fl_color(FL_RED);
		fl_pie((int)(x() - radius()), (int)(y() - radius()), (int)(radius()*2), (int)(radius()*2), 0, 360);
	}
}

/** \brief The collision detection function that destroys EnemyItem objects.
 *
 * The collision detecion function increments the radius of the fireball and then destroys
 * all EnemyItem objects that touch the explosion. Score is incremented by 1 for each item
 * that the explosion destroys.
 * \param scr Optional: The current score of the game, defaults to zero if unspecified.
 * \return Returns the new score.
 */
int ShellExplosion::collision_detect(int scr)
{
	int score = scr;

	if ((timealive() < 1) && (timealive() > SE_INITIAL_PERIOD))
	{
		radius(max_radius_*timealive());
	}
	else
	{
		radius(max_radius_);
	}

	for (int i = 0; i < (int)EnemyItem::enemyitems().size(); i++)
	{
		double x_diff = EnemyItem::enemyitems()[i]->x() - x();
		double y_diff = EnemyItem::enemyitems()[i]->y() - y();
		if (x_diff*x_diff + y_diff*y_diff <= (radius()+EnemyItem::enemyitems()[i]->radius())*(radius()+EnemyItem::enemyitems()[i]->radius()))
		{
#ifdef DEBUG
			cout << "shell interacted with enemy item " << i << endl;
#endif
			EnemyItem::enemyitems()[i]->on_death();
			delete EnemyItem::enemyitems()[i];
			score = score + 1;
			i--;
		}
	}
	return score;
}
