/** \file GameObject.cpp
 * \brief Code implementation for GameObject class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#include "GameObject.h"

/** \brief Constructor for Explosion.
 *
 * The constructor initialises its variables.
 */
GameObject::GameObject(double x, double y, double r)
{
	x_ = x;
	y_ = y;
	radius_ = r;
}

/** \brief Destructor for Explosion.
 *
 * The destructor does nothing fancy.
 */
GameObject::~GameObject()
{
}

/** \brief A function to allow repositioning of objects.
 *
 * \param x New x co-ordinate.
 * \param y New y co-ordinate.
 */
void GameObject::position(double x, double y)
{
	x_ = x;
	y_ = y;
}

/** \brief A function to return the x co-ordinate.
 *
 * \return Returns the x co-ordinate, type double.
 */
double GameObject::x()
{
	return x_;
}

/** \brief A function to return the y co-ordinate.
 *
 * \return Returns the y co-ordinate, type double.
 */
double GameObject::y()
{
	return y_;
}

/** \brief A function to return the radius of the object.
 *
 * \return Returns the radius, type double.
 */
double GameObject::radius()
{
	return radius_;
}

/** \brief A function to change the radius of the object.
 *
 * \param r The new radius, type double;
 */
void GameObject::radius(double r)
{
	radius_ = r;
}

/** \brief A function to execute stuff on object death.
 * 
 * This function does nothing and is to be overridden by child classes if that class
 * needs to do something on death, such as generate an explosion.
 */
void GameObject::on_death()
{
}
