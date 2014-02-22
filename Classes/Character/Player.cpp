/*
 * Player.cpp
 *
 *  Created on: 2013/11/09
 *      Author: gameprogram
 */

#include "Player.h"

Player::Player() {
	// TODO 自動生成されたコンストラクター・スタブ
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

bool Player::load(const char* filename){
	return Character::load(filename);
}

void Player::update(float dt){

}
