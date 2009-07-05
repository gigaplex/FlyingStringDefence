/** \file EnemyItem.h
 * \brief Header file for EnemyItem class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef ENEMYITEM_H
#define ENEMYITEM_H

#include "Projectile.h"

/** \brief The EnemyItem class. All enemy items are projectiles.
 *
 * The EnemyItem class inherits from Projectile as all enemy items are treated
 * as projectiles. The EnemyItem class allows acces to a list of all the enemy
 * items and the enemy items alone.
 */
class EnemyItem : public Projectile
{
public:
	EnemyItem(double startx, double starty, double endx, double endy, double r, double vel);
	virtual ~EnemyItem();
	
	static const vector<EnemyItem*>& enemyitems();
private:
	static vector<EnemyItem*> enemyitems_;
};

#endif

