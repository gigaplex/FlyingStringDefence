/** \file Projectile.cpp
 * \brief Code implementation for Projectile class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#include "Projectile.h"

#include <stdlib.h>
#include <math.h>

/** \brief Global vector of pointers to all Projectile objects.
 *
 * This vector stores pointers to all Projectile objects. It is self-managed.
 * When a Projectile object is created, it adds itself to the vector and when
 * it is destroyed it removes itself from the vector.
 */
vector<Projectile*> Projectile::projectiles_;

/** \brief Constructor for Projectile.
 *
 * The constructor adds the Projectile object to the global vector of projectiles.
 * To create an object, use "new Projectile(...)" and the object can be 
 * accessed via the Projectile::projectiles() function.
 */
Projectile::Projectile(double startx, double starty, double endx, double endy, double r, double vel) : GameObject(startx, starty, r)
{
	projectiles_.push_back(this);
	start_x_ = startx;
	start_y_ = starty;
	target_x_ = endx;
	target_y_ = endy;
	velocity_ = vel;
	angle_ = atan((double)(endx - startx) / (double)(endy - starty));
	if ((endy - starty) >= 0)
	{
		angle_ = angle_ + M_PI;
	}
}

/** \brief Destructor for Projectile.
 *
 * The destructor searches through the vector for the 'this' item and
 * removes it from the vector.
 */
Projectile::~Projectile()
{
	vector<Projectile*>::iterator it;
	for (it = projectiles_.begin(); it != projectiles_.end(); it++)
	{
		if ((*it) == this)
		{
			projectiles_.erase(it);
			break;
		}
	}
}

/** \brief A function to return a const vector to the list of Projectile objects.
 *
 * This function returns a const vector to the list of Projectile objects so the
 * objects can be used. This is the only way of accessing the objects. To
 * access a member, use "Projectile::projectiles()[index]".
 * \return Returns a const vector of pointers to the Projectile objects.
 */
const vector<Projectile*>& Projectile::projectiles()
{
	return projectiles_;
}

/** \brief A function to return the value of the x co-ordinate of the target.
 *
 * \return Returns the x co-ordinate of the target, type double.
 */
double Projectile::target_x()
{
	return target_x_;
}

/** \brief A function to return the value of the y co-ordinate of the target.
 *
 * \return Returns the y co-ordinate of the target, type double.
 */
double Projectile::target_y()
{
	return target_y_;
}

/** \brief A function to set the target of the projectile.
 *
 * \param x The x co-ordinate of the target, type double.
 * \param y The y co-ordinate of the target, type double.
 */
void Projectile::target(double x, double y)
{
	target_x_ = x;
	target_y_ = y;
}

/** \brief A function to return the value of the x co-ordinate of the start location.
 *
 * \return Returns the y co-ordinate of the start location, type double.
 */
double Projectile::start_x()
{
	return start_x_;
}

/** \brief A function to return the value of the y co-ordinate of the start location.
 *
 * \return Returns the y co-ordinate of the start location, type double.
 */
double Projectile::start_y()
{
	return start_y_;
}

/** \brief A function to return the value of the velocity of the projectile.
 *
 * \return Returns the velocity of the projectile, type double.
 */
double Projectile::velocity()
{
	return velocity_;
}

/** \brief A function to set the velocity of the projectile.
 *
 * \param v The velocity to be assigned to the projectile, type double.
 */
void Projectile::velocity(double v)
{
	velocity_ = v;
}

/** \brief A function to return the angle the projectile is travelling at.
 *
 * \return Returns the angle the projectile is travelling at, type double.
 */
double Projectile::angle()
{
	return angle_;
}

/** \brief A function to set the value of the angle the projectile is travelling in.
 *
 * \param a The angle to be assigned to the projectile, type double.
 */
void Projectile::angle(double a)
{
	angle_ = a;
}

/** \brief A function to animate the Projectile.
 *
 * A function to animate the projectile. This moves the projectile in the direction
 * determined by its angle at a rate determined by its velocity.
 * \param t is the amount of time in seconds that has passed since last
		animation call.
 * \return Returns 1 if the object has reached its target.
 * \return Returns 0 otherwise.
 */
int Projectile::animate(double t)
{
	double error_x = x() - target_x();
	double error_y = y() - target_y();
	double sign_x = (start_x() - target_x()) >= 1 ? 1 : -1;
	double sign_y = (start_y() - target_y()) >= 1 ? 1 : -1;

	if ((error_x*sign_x <= 10) && (error_y*sign_y <= 10)) // if within 10 pixels
	{
		return 1;
	}
	position(x() - sin(angle())*velocity()*t, y() - cos(angle())*velocity()*t);

	return 0;
}
