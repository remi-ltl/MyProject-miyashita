
#ifndef __GAME_MANAGER__
#define __GAME_MANAGER__

#include "cocos2d.h"

class GameManager {
public:
	GameManager();
	virtual ~GameManager();

	static GameManager* sharedInstance();

	inline int getStageId(){return stage_id;}
	inline void setStageId(int in_id){ stage_id = in_id;}

	bool init();

private:
	int stage_id;
};

#endif /* __GAME_MANAGER__ */
