/** \file Explosion.h
 * \brief Header file for Explosion class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.h"
#include "timer.h"

/** \brief The Explosion class. This class is an abstract class.
 *
 * The Explosion class is an abstract class that provides a framework for
 * other explosions to inherit from. Explosions have a creation time saved
 * as explosions only have a finite duration. A loop should run through to 
 * clean up stale explosions, a good place to do this is in an animation
 * routine that monitors current time. The Explosion class allows acces to
 * a list of all the explosions and the explosions alone.
 */
class Explosion : public GameObject
{
public:
	Explosion(double x, double y, double r);
	virtual ~Explosion();
	
	static const vector<Explosion*>& explosions();
	virtual double timealive();
	virtual int collision_detect(int scr) = 0;
	virtual int animate(double timediff);
private:
	static vector<Explosion*> explosions_;
	double timealive_;
};

#endif
