/** \file PlayerItem.cpp
 * \brief Code implementation for PlayerItem class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#include "PlayerItem.h"

/** \brief Global vector of pointers to all PlayerItem objects.
 *
 * This vector stores pointers to all PlayerItem objects. It is self-managed.
 * When an PlayerItem object is created, it adds itself to the vector and when
 * it is destroyed it removes itself from the vector.
 */
vector<PlayerItem*> PlayerItem::playeritems_;

/** \brief Constructor for PlayerItem.
 *
 * The constructor adds the PlayerItem object to the global vector of player items.
 * To create an object, use "new PlayerItem(...)" and the object can be 
 * accessed via the PlayerItem::playeritems() function.
 */
PlayerItem::PlayerItem(double x, double y, double r) : GameObject(x, y, r)
{
	playeritems_.push_back(this);
}

/** \brief Destructor for PlayerItem.
 *
 * The destructor searches through the vector for the 'this' item and
 * removes it from the vector.
 */
PlayerItem::~PlayerItem()
{
	vector<PlayerItem*>::iterator it;
	for(it = playeritems_.begin(); it != playeritems_.end(); it++)
	{
		if((*it) == this)
		{
			playeritems_.erase(it);
			break;
		}
	}
}

/** \brief A function to return a const vector to the list of PlayerItem objects.
 *
 * This function returns a const vector to the list of PlayerItem objects so the
 * objects can be used. This is the only way of accessing the objects. To
 * access a member, use "PlayerItem::playeritems()[index]".
 * \return Returns a const vector of pointers to the PlayerItem objects.
 */
const vector<PlayerItem*>& PlayerItem::playeritems()
{
	return playeritems_;
}
