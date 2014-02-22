/*
 * Character.cpp
 *
 *  Created on: 2013/11/09
 *      Author: gameprogram
 */

#include "Enemy.h"


Enemy::Enemy() {
	// TODO 自動生成されたコンストラクター・スタブ
	setSpeed(0);
	mCount = 0;
}

Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
}

bool Enemy::load(const char* filename){
	return (this->initWithFile(filename));
}

void Enemy::update(float dt){
//	this->runAction(CCMoveBy::create(mSpeed,ccp(0,5)));


}

bool Enemy::getAttackTiming(){
	bool flag = false;
	mCount ++;
	if(this->getCount() > ATTACK_TIME){
		flag = true;
		mCount = 0;
	}
	return flag;
}
