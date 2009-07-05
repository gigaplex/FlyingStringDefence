/** \file Projectile.h
 * \brief Header file for Projectile class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"

/** \brief The Projectile class.
 *
 * The Projectile class inherits from GameObject and extends it to allow for moving
 * objects. The projectiles are assumed to move in a straight line towards the target.
 * The Projectile class allows acces to a list of all the projectiles and the 
 * projectiles alone.
 */
class Projectile : public GameObject
{
public:
	Projectile(double startx, double starty, double endx, double endy, double r, double vel);
	virtual ~Projectile();

	static const vector<Projectile*>& projectiles();
	virtual double target_x();
	virtual double target_y();
	virtual double start_x();
	virtual double start_y();
	virtual double velocity();
	virtual int animate(double t);
protected:
	virtual void target(double x, double y);
	virtual void velocity(double v);
	virtual double angle();
	virtual void angle(double a);
private:
	static vector<Projectile*> projectiles_;
	double target_x_;
	double target_y_;
	double start_x_;
	double start_y_;
	double velocity_;
	double angle_;
};

#endif
