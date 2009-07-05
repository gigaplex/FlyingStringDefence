/** \file Base.h
 * \brief Header file for Base class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef BASE_H
#define BASE_H

#include "PlayerItem.h"

/** \brief The players Base class.
 *
 * The Base class simply adds the specialised draw() function for the
 * bases to the PlayerItem class that the player needs to defend. The
 * class also allows access to a list of all the bases and the bases 
 * alone.
 */
class Base : public PlayerItem
{
public:
	Base(double x, double y);
	virtual ~Base();

	static const vector<Base*>& bases();
protected:
	virtual void draw();
private:
	static vector<Base*> bases_;
	virtual void draw_base();
};

#endif
