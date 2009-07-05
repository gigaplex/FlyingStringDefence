/** \file Missile.h
 * \brief Header file for Missile class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef MISSILE_H
#define MISSILE_H

#include "EnemyItem.h"

/** \brief The enemy Missile class.
 *
 * The Missile class inherits from EnemyItem and adds the specialised draw() and
 * collision_detect() functions. The missiles also allow acces to a list of all
 * the missiles and the missiles alone.
 */
class Missile : public EnemyItem
{
public:
	Missile(double startx, double starty, double endx, double endy, double vel);
	virtual ~Missile();
	
	static const vector<Missile*>& missiles();
	virtual bool collision_detect();
protected:
	virtual void draw();
private:
	static vector<Missile*> missiles_;
	virtual void draw_missile();
};

#endif
