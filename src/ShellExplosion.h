/** \file ShellExplosion.h
 * \brief Header file for ShellExplosion class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef SHELLEXPLOSION_H
#define SHELLEXPLOSION_H

#include "Explosion.h"

/** \brief The Shell class.
 *
 * The ShellExplosion class inherits from Explosion. The ShellExplosion
 * destroys all EnemyItem objects within the blast radius on initial impact,
 * and creates an expanding fireball which lingers for 1 second destroying all
 * enemy items that touch it. The ShellExplosion class allows acces to a list
 * of all the shell explosions and the shell explosions alone.
 */
class ShellExplosion : public Explosion
{
public:
	ShellExplosion(double x, double y, double radius);
	virtual ~ShellExplosion();

	static const vector<ShellExplosion*>& shellexplosions();
	virtual int collision_detect(int scr = 0);
protected:
	void draw();
private:
	static vector<ShellExplosion*> shellexplosions_;
	void draw_shellexplosion();
	double max_radius_;
};

#endif
