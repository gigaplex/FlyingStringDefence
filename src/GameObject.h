/** \file GameObject.h
 * \brief Header file for GameObject class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Fl/Fl_Widget.H>

#include "enum.h"

/** \brief The GameObject class. The class all objects derive from.
 *
 * The GameObject class grants friend privileges to the Window class
 * for access to private functions such as draw().
 */
class GameObject
{
public:
	GameObject(double x, double y, double r);
	virtual ~GameObject();

	friend class Window;

	virtual double x();
	virtual double y();
	virtual double radius();
	virtual void on_death();
protected:
	virtual void position(double x, double y);
	virtual void draw() = 0;
	virtual void radius(double r);
private:
	double x_;
	double y_;
	double radius_;
};

#endif
