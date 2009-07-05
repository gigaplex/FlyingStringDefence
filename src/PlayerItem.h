/** \file PlayerItem.h
 * \brief Header file for PlayerItem class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include "GameObject.h"

/** \brief The PlayerItem class.
 *
 * The PlayerItem class inherits from GameObject as all player items are treated
 * as stationary objects. The PlayerItem class allows acces to a list of all the
 * player items and the player items alone.
 */
class PlayerItem : public GameObject
{
public:
	PlayerItem(double x, double y, double r);
	virtual ~PlayerItem();
	
	static const vector<PlayerItem*>& playeritems();
private:
	static vector<PlayerItem*> playeritems_;
};

#endif

