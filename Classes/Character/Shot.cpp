
#include "Shot.h"

Shot::Shot() {
	// TODO �����������ꂽ�R���X�g���N�^�[�E�X�^�u
	mUsed = false;
	mVector = ccp(0,0);
}

Shot::~Shot() {
	// TODO Auto-generated destructor stub
}

void Shot::update(float dt){
}

void Shot::Use(CCPoint in_vector){
	mUsed = true;
	mVector = (in_vector.normalize()*SPEED);
}
