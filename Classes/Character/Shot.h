

#ifndef SHOT_H_
#define SHOT_H_

#include "cocos2d.h"
using namespace cocos2d;

class Shot : public Character{

public:
	static const float SPEED = 5;
private:
	bool mUsed;
	CCPoint mVector;
public:
	Shot();
	virtual ~Shot();

	virtual void Use(CCPoint in_vector);

	virtual void update(float dt);

	inline CCPoint getVector(){return mVector;}
	inline bool getUsed(){return mUsed;}
	inline void setUsed(bool in_flag){mUsed = in_flag;}
};

#endif /* SHOT_H_ */
