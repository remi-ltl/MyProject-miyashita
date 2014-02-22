#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class Title : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    // Layer


    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void buttonPushCallback(CCObject* pSender);

    void scenechangeCrossFadeCallback(CCObject* pSender);
    void scenechangeSplitRowsCallback(CCObject* pSender);
    void scenechangeFlipAngular(CCObject* pSender);
    void scenechangeFadeCallback(CCObject* pSender);
    void scenechangeJumpZoomCallback(CCObject* pSender);

//    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
//    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
 //   virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);

    virtual void update(float delta);

    void playSound(const char *filepath);

private:
    CCSprite* pSprite;

    CCDrawNode* dot;

    CCPoint mStartPos;
    CCPoint mDelta;


    CCPoint getTilePosition(CCPoint point, CCTMXTiledMap* map);
    int		getTileNum(CCPoint point, CCTMXTiledMap* map,char* layerName);
    // implement the "static node()" method manually
    CREATE_FUNC(Title);

};

#endif // __HELLOWORLD_SCENE_H__
