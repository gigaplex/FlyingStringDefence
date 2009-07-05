/** \file EnemyItem.cpp
 * \brief Code implementation for EnemyItem class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#include "EnemyItem.h"

/** \brief Global vector of pointers to all EnemyItem objects.
 *
 * This vector stores pointers to all EnemyItem objects. It is self-managed.
 * When an EnemyItem object is created, it adds itself to the vector and when
 * it is destroyed it removes itself from the vector.
 */
vector<EnemyItem*> EnemyItem::enemyitems_;

/** \brief Constructor for EnemyItem.
 *
 * The constructor adds the EnemyItem object to the global vector of enemy items.
 * To create an object, use "new EnemyItem(...)" and the object can be 
 * accessed via the EnemyItem::enemyitems() function.
 */
EnemyItem::EnemyItem(double startx, double starty, double endx, double endy, double r, double vel) : Projectile(startx, starty, endx, endy, r, vel)
{
	enemyitems_.push_back(this);
}

/** \brief Destructor for EnemyItem.
 *
 * The destructor searches through the vector for the 'this' item and
 * removes it from the vector.
 */
EnemyItem::~EnemyItem()
{
	vector<EnemyItem*>::iterator it;
	for(it = enemyitems_.begin(); it != enemyitems_.end(); it++)
	{
		if((*it) == this)
		{
			enemyitems_.erase(it);
			break;
		}
	}

}

/** \brief A function to return a const vector to the list of EnemyItem objects.
 *
 * This function returns a const vector to the list of EnemyItem objects so the
 * objects can be used. This is the only way of accessing the objects. To
 * access a member, use "EnemyItem::enemyitems()[index]".
 * \return Returns a const vector of pointers to the EnemyItem objects.
 */
const vector<EnemyItem*>& EnemyItem::enemyitems()
{
	return enemyitems_;
}
