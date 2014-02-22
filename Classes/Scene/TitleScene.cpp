#include "TitleScene.h"
#include "HelloWorldScene.h"
#include "GameManager.h"
#include "../CocosDenshion/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;

typedef enum {
	kTileMapTag = 99
}myNodeTag;


USING_NS_CC;

CCScene* Title::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Title *layer = Title::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Title::init()
{

    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCTMXTiledMap* pTiledMap = CCTMXTiledMap::create("Map/TestMap.tmx");
    this->addChild(pTiledMap);
    pTiledMap->setTag(kTileMapTag);

    //CCLayerGradient::initWithColor(ccc4(255,0,0,255),ccc4(0,0,255,100),ccp(0.0f,1.0f));

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

//    setTouchMode(kCCTouchesAllAtOnce);
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    CCLog("touchEnabled");
    this->setKeypadEnabled(true);
    CCLog("padEnabled");
    this->scheduleUpdate();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem[5];

    pCloseItem[0] = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(Title::scenechangeCrossFadeCallback));
    pCloseItem[1] = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(Title::scenechangeFadeCallback));
    pCloseItem[2] = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(Title::scenechangeJumpZoomCallback));
    pCloseItem[3] = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(Title::scenechangeFlipAngular));
    pCloseItem[4] = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(Title::scenechangeSplitRowsCallback));
    

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition(CCPointZero);
    for(int i = 0; i < 5; i++){
    	pCloseItem[i]->setPosition(ccp(origin.x + visibleSize.width/6 * (i+1),
                                    origin.y + visibleSize.height/2));
//    	pCloseItem[i]->setScale(1.0f);

    	pMenu->addChild(pCloseItem[i]);
    }
//    CCLayerColor *color = CCLayerColor::create(ccc4(100,100,255,100));

//    this->addChild(color,10);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    pSprite = CCSprite::create("Image/radish.png");


    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    pSprite->setScaleX(visibleSize.width/480);
    pSprite->setScaleY(visibleSize.height/320);


    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/title_bgm.mp3",true);


    int id = GameManager::sharedInstance()->getStageId();

    CCLog("Get ID :: %d",id);
/*

    CCLayerColor* frontLayer = CCLayerColor::create(ccc4(0,0,255,128));
    this->addChild(frontLayer,20);

    ccBlendFunc blend;
    blend.src = GL_SRC_ALPHA;
    blend.dst = GL_ONE;

    frontLayer->setBlendFunc(blend);*/

    dot = CCDrawNode::create();
    this->addChild(dot);
    return true;
}
bool Title::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent){
	mStartPos = this->convertToWorldSpace(
			this->convertTouchToNodeSpace(pTouch));

	this->scheduleUpdate();
	CCLog("Touch Began");

	CCTMXTiledMap* pTileMap
				= (CCTMXTiledMap*)this->getChildByTag(kTileMapTag);

	CCPoint pos = getTilePosition(mStartPos,pTileMap);

	int id = getTileNum(pos, pTileMap,"Ground");

	CCLog("Tile ID:%d",id);

	return true;
}
void Title::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent){
	CCPoint touchPos = this->convertToWorldSpace(
			this->convertTouchToNodeSpace(pTouch));

	mDelta = CCPoint(	mStartPos.x - touchPos.x,
						mStartPos.y - touchPos.y);
}

void Title::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent){
	this->unscheduleUpdate();
	CCLog("Touch Ended");

}

/*
void Title::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
	CCLog("Begin");
	CCSetIterator it;
	CCTouch* touch;
	for(it = pTouches->begin(); it != pTouches->end(); it++){
			touch = (CCTouch*)(*it);
			if(!touch){
				break;
			}

			CCLog("TouchID:%d",touch->getID());
	}
}*/
/*
void Title::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	CCLog("Move");

	CCSetIterator it;
	CCTouch* touch;
	for(it = pTouches->begin(); it != pTouches->end(); it++){
			touch = (CCTouch*)(*it);
			if(!touch){
				break;
			}
			if(touch->getID() == 0){
				dot->drawDot(touch->getLocation(),1,ccc4f(1,1,1,1));
			}
	}
}
*/
/*
void Title::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent){
	CCLog("End");

	CCSetIterator it;
	CCTouch* touch;
	for(it = pTouches->begin(); it != pTouches->end(); it++){
			touch = (CCTouch*)(*it);
			if(!touch){
				break;
			}

			CCLog("TouchID:%d",touch->getID());
			if(touch->getID() == 0){
				dot->clear();
			}
	}

	CCSetIterator it;
	CCTouch* touch;
	for(it = touches->begin(); it != touches->end(); it++){
			touch = (CCTouch*)(*it);
			if(!touch){
				break;
			}

			CCPoint location = touch->getLocationInView();
			location = CCDirector::sharedDirector()->convertToGL(location);

			CCJumpBy* jump = CCJumpBy::create(10.0f,ccp(100,100),50.0f,10);
			CCFlipX* flipx = CCFlipX::create(true);
			pSprite->runAction(CCSpawn::create(jump,flipx,NULL));

		    CCParticleSystemQuad* pParticle
		    	= CCParticleSystemQuad::create("Particle/Test.plist");
		    pParticle->setPosition(location.x,location.y);

		    this->addChild(pParticle);

			CCLog("touchEnded = {%f,%f}",location.x,location.y);
	}

}
*/

void Title::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent){
	CCLog("Cancel");
}

void Title::update(float delta){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCTMXTiledMap* pTileMap
					= (CCTMXTiledMap*)this->getChildByTag(kTileMapTag);

	CCPoint point = pTileMap->getPosition();
	CCPoint pDelta = ccp(mDelta.x*delta,mDelta.y*delta);

	point = CCPoint(point.x + pDelta.x,
					point.y + pDelta.y);

	CCSize mapSize = pTileMap->getContentSize();
	//調整

 	point.x = MAX(point.x,size.width - mapSize.width);
	point.x = MIN(point.x,0);
	point.y = MAX(point.y,size.height - mapSize.height);
	point.y = MIN(point.y,0);

	pTileMap->setPosition(point);
}

/*
 * 	タイル座標とタッチ座標の調整
 * 	point::タッチ座標
 * 	map：：マップデータ
 */
CCPoint Title::getTilePosition(CCPoint point, CCTMXTiledMap* map){


	CCPoint tilePos = ccpSub(point, map->getPosition());
	float fTileWidth = map->getTileSize().width;
	float fTileHeight = map->getTileSize().height;

	float fTileRow = map->getMapSize().height;

	tilePos.x = (int)(tilePos.x / fTileWidth);
	tilePos.y = (int)((fTileRow * fTileHeight - tilePos.y)/fTileHeight);

	return tilePos;
}
/*
 *  タイル番号の取得
 *  point::変換座標
 *  map::マップデータ
 */
int	Title::getTileNum(CCPoint point, CCTMXTiledMap* map,char* layerName){
	int num = -1;
	CCTMXLayer* pGroundLayer = map->layerNamed(layerName);
	num = pGroundLayer->tileGIDAt(point);

	return num;
}
void Title::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void Title::scenechangeCrossFadeCallback(CCObject *pSender){
	CCScene *next = Title::scene();

	CCLog("Change:CrossFade");

	CCTransitionCrossFade *change = CCTransitionCrossFade::create(0.5f,next);

	this->playSound("sound/cat.wav");

	CCDirector::sharedDirector()->replaceScene(change);
}
void Title::scenechangeSplitRowsCallback(CCObject *pSender){
	CCScene *next = Title::scene();

	CCLog("Change:RowsCallback");
	this->playSound("sound/cat.wav");
	CCTransitionSplitRows *change = CCTransitionSplitRows::create(0.5f,next);

	CCDirector::sharedDirector()->replaceScene(change);
}
void Title::scenechangeFlipAngular(CCObject *pSender){
	CCScene *next = Title::scene();

	CCLog("Change:FlipAngular");
	this->playSound("sound/cat.wav");
	CCTransitionFlipAngular *change = CCTransitionFlipAngular::create(0.5f,next);

	CCDirector::sharedDirector()->replaceScene(change);
}
void Title::scenechangeFadeCallback(CCObject *pSender){
	CCScene *next = Title::scene();

	CCLog("Change:FadeCallback");
	this->playSound("sound/cat.wav");
	CCTransitionFade *change = CCTransitionFade::create(1.5f,next);

	CCDirector::sharedDirector()->replaceScene(change);
}

void Title::scenechangeJumpZoomCallback(CCObject *pSender){
	CCScene *next = Title::scene();

	CCLog("Change:JumpZoom");
	this->playSound("sound/cat.wav");
	CCTransitionJumpZoom *change = CCTransitionJumpZoom::create(0.5f,next);

	CCDirector::sharedDirector()->replaceScene(change);
}

void Title::playSound(const char *filepath){
	CCLog("Play::%s",filepath);
	SimpleAudioEngine::sharedEngine()->playEffect(filepath);
}
