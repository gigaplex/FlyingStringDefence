/** \file Explosion.cpp
 * \brief Code implementation for Explosion class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#include "Explosion.h"

#include <Fl/fl_draw.h>

/** \brief Global vector of pointers to all Explosion objects.
 *
 * This vector stores pointers to all Explosion objects. It is self-managed.
 * When an Explosion object is created, it adds itself to the vector and when
 * it is destroyed it removes itself from the vector.
 */
vector<Explosion*> Explosion::explosions_;

/** \brief Constructor for Explosion.
 *
 * The constructor adds the Explosion object to the global vector of enemy items.
 * The constructor also records the creation time of the Explosion object.
 * To create an object, use "new Explosion(...)" and the object can be accessed 
 * via the Explosion::explosions() function.
 */
Explosion::Explosion(double x, double y, double r) : GameObject(x, y, r)
{
	timealive_ = 0;
	explosions_.push_back(this);
}

/** \brief Destructor for Explosion.
 *
 * The destructor searches through the vector for the 'this' item and
 * removes it from the vector.
 */
Explosion::~Explosion()
{
	vector<Explosion*>::iterator it;
	for(it = explosions_.begin(); it != explosions_.end(); it++)
	{
		if((*it) == this)
		{
			explosions_.erase(it);
			break;
		}
	}
}

/** \brief A function to return a const vector to the list of Explosion objects.
 *
 * This function returns a const vector to the list of Explosion objects so the
 * objects can be used. This is the only way of accessing the objects. To
 * access a member, use "Explosion::explosions()[index]".
 * \return Returns a const vector of pointers to the Explosion objects.
 */
const vector<Explosion*>& Explosion::explosions()
{
	return explosions_;
}

/** \brief A function to read the value of timealive.
 *
 * \return Returns the value of timealive.
 */
double Explosion::timealive()
{
	return timealive_;
}

/** \brief A function to animate the Explosion.
 *
 * A function to animate the Explosion. This simply increments the time that the
 * Explosion has been alive for. If the explosion has been alive for more than one
 * second, return a value to indicate it is ready to be destroyed.
 * \param timediff is the amount of time in seconds that has passed since last
		animation call.
 * \return Returns 1 if the object is ready to be destroyed.
 * \return Returns 0 otherwise.
 */
int Explosion::animate(double timediff)
{
	timealive_ = timealive_ + timediff;
	if (timealive_ > 1)
	{
		return 1;
	}
	return 0;
}
