/*
 * Character.h
 *
 *  Created on: 2013/11/09
 *      Author: gameprogram
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "cocos2d.h"
#include "Character.h"
using namespace cocos2d;

class Enemy  : public Character
{
public:
	static const int ATTACK_TIME = 30;
private:
	int			mCount;
protected:

	CCSize		mSize;

	CCPoint		mAdd;
	float		mSpeed;

	bool		mHit;
public:
	Enemy();
	virtual ~Enemy();
	virtual bool load(const char* filename);
	virtual void update(float dt);

	inline float getSpeed(){return mSpeed;}
	inline void setSpeed(float in_speed){mSpeed = in_speed;}

	inline bool getHit(){return mHit;}
	inline void setHit(bool in_hit){mHit = in_hit;}

//	inline CC getHit(){return mHit;}
	inline void setVector(CCPoint in_add){mAdd = in_add;}

	inline int getCount(){return mCount;}
	bool getAttackTiming();
};

#endif /* CHARACTER_H_ */
