/*
 * Player.h
 *
 *  Created on: 2013/11/09
 *      Author: gameprogram
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"

class Player : public Character{

private:

public:
	Player();
	virtual ~Player();
	virtual bool load(const char* filename);
	virtual void update(float dt);
};
#endif /* PLAYER_H_ */
