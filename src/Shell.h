/** \file Shell.h
 * \brief Header file for Shell class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef SHELL_H
#define SHELL_H

#include "Projectile.h"

/** \brief The Shell class.
 *
 * The Shell class inherits from Projectile. It is not considered to be either
 * a PlayerItem or an EnemyItem. The Shell class allows acces to a list of all
 * the shells and the shells alone.
 */
class Shell : public Projectile
{
public:
	Shell(double startx, double starty, double endx, double endy, double radius);
	virtual ~Shell();

	static const vector<Shell*>& shells();
	virtual void on_death();
protected:
	virtual void draw();
private:
	static vector<Shell*> shells_;
	virtual void draw_shell();
	double shell_blast_radius_;
};

#endif
