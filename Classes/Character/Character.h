/*
 * Character.h
 *
 *  Created on: 2013/11/09
 *      Author: gameprogram
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "cocos2d.h"
using namespace cocos2d;

class Character  : public CCSprite
{

protected:

	CCSize		mSize;
	float		mSpeed;

public:
	Character();
	virtual ~Character();
	virtual bool load(const char* filename);
	virtual void update(float dt);

	bool CollisionSprite(Character* target,bool pp);

	inline float getSpeed(){return mSpeed;}
	inline void setSpeed(float in_speed){mSpeed = in_speed;}
};

#endif /* CHARACTER_H_ */
