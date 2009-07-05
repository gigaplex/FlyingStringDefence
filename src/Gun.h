/** \file Gun.h
 * \brief Header file for Gun class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef GUN_H
#define GUN_H

#include "PlayerItem.h"

#include "enum.h"

/** \brief The players Gun class.
 *
 * The Gun class inherits from PlayerItem and has barrels that aim at a
 * target. The Window class uses the location of the mouse as the target.
 * The Guns can only aim in a 180 degree arc, facing upwards. The guns
 * also allow acces to a list of all the guns and the guns alone.
 */
class Gun : public PlayerItem
{
public:
	Gun(double x, double y, double width);
	virtual ~Gun();

	static const vector<Gun*>& guns();
	virtual void target(double x, double y);
	virtual double target_x();
	virtual double target_y();
	virtual bool target_valid();
	virtual double barrel_width();
	virtual void barrel_width(double width);
protected:
	virtual void draw();
private:
	static vector<Gun*> guns_;
	virtual void draw_gun();
	double target_x_;
	double target_y_;
	double theta;
	double barrel_width_;
	bool valid_target;
};

#endif

