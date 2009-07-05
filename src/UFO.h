/** \file UFO.h
 * \brief Header file for UFO class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef UFO_H
#define UFO_H

#include "EnemyItem.h"

/** \brief The UFO class.
 *
 * The UFO class is an EnemyItem that flys across the screen randomly shooting
 * Missile objects. The UFO was supposed to generate powerup objects when shot,
 * however the powerup class has not been implemented. The UFO class allows acces
 * to a list of all the UFOs and the UFOs alone.
 */
class UFO : public EnemyItem
{
public:
	UFO(double startx, double starty, double endx, double endy, double vel);
	virtual ~UFO();
	
	static const vector<UFO*>& ufos();
	virtual int animate(double t, int level = 1);
protected:
	virtual void draw();
private:
	static vector<UFO*> ufos_;
	virtual void draw_ufo();
};

#endif
