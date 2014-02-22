//#define BATCH_NODE

#include "TitleScene.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "GameManager.h"
#include "spine/Json.h"

#include "cocos-ext.h"

#include "../CocosDenshion/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;

USING_NS_CC_EXT;

USING_NS_CC;

CCScene* Game::scene()
{
	CCLog("NORMAL");
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Game *layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{

    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);

    mTouchStartPos = ccp(100,100);
    mTouchMovePos = ccp(100,100);
    mPlayerDefPos = ccp(100,100);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/ImagePack.plist");

    pPlayer = (Player*)Player::create("Image/radish.png");
    pPlayer->setPositionX(100);
    pPlayer->setPositionY(100);
    pPlayer->setAnchorPoint(CCPointMake(0.5,0.5));
//    pPlayer->load("Image/radish.png");

    pEnemy = (Enemy*)Enemy::create("Image/mushroom.png");
    pEnemy->setPositionX(250);
    pEnemy->setPositionY(250);
    pEnemy->setAnchorPoint(ccp(0.5,0.5));
    pEnemy->setSpeed(1);

//    pBullet = CCArray::create();
//    pBullet->initWithCapacity(MAX_BULLET);

    testBullet = (Shot*)Shot::create("Image/canser.png");
    this->addChild(testBullet);

    this->scheduleUpdate();

    pFont = CCLabelBMFont::create("Hello World","fonts/font.fnt",24);

    pFont->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pFont->getContentSize().height));
    count = 0;

    const int WIDTH = 30;
    const int HEIGHT = 20;

    CCArray* item = CCArray::createWithContentsOfFile("Image/ImagePack.plist");

    batchNode = CCSpriteBatchNode::create("Image/ImagePack.png");
    this->addChild(batchNode);

#ifdef BATCH_NODE
    batchNode = CCSpriteBatchNode::create("Image/ImagePack.png");
    this->addChild(batchNode);
    CCLog("BATCH_NODE");
#else
    CCLog("NORMAL");
#endif


    Json* json = Json_create("{\"abc\":true,\"def\":false,\"ghi\":1,\"jkl\":\"miya\"}");


//3    CCLog("Json::%d",Json_getBool(NULL,"def",true));

    this->addChild(pFont);
    this->addChild(pPlayer);
    this->addChild(pEnemy);
    return true;
}
bool Game::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent){
	mTouchStartPos = this->convertToWorldSpace(
			this->convertTouchToNodeSpace(pTouch));

	mPlayerDefPos = pPlayer->getPosition();

/*	CCSprite* add = this->getPackageSprite("AttackEffect.png");
	add->setPosition(mTouchStartPos);

#ifdef BATCH_NODE
	batchNode->addChild(add);
#else
	this->addChild(add);
#endif
	count++;
	CCString* str = CCString::createWithFormat("%d",count);
	pFont->setString(str->getCString());
*/

	return true;
}
void Game::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent){
	CCPoint touchPos = this->convertToWorldSpace(
			this->convertTouchToNodeSpace(pTouch));

	mTouchMovePos = touchPos;

	mDelta = CCPoint(	mTouchStartPos.x - touchPos.x,
						mTouchStartPos.y - touchPos.y);
}

void Game::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent){

	mPlayerDefPos = pPlayer->getPosition();
	mDelta = ccp(0,0);
}

void Game::update(float delta){
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	if(pEnemy->getAttackTiming()){
//		CCLog("ENEMY -> [ATTACK]");

//		CreateBullet(ccp(0,5));
	}

	MovePlayer(delta);
	MoveEnemy(delta);
	MoveBullet(delta);

	Collision();
}

/*
 *	プレイヤー動作
 */
void Game::MovePlayer(float delta){
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCPoint pos = mPlayerDefPos;
	CCPoint vec = mDelta;

	pos.x -= vec.x;
	pos.y -= vec.y;
	if(pos.x < 0){pos.x = 0;}
	if(pos.x > size.width){pos.x = size.width;}

	if(pos.y < 0){pos.y = 0;}
	if(pos.y > size.height){pos.y = size.height;}

	pPlayer->setPosition(pos);
}

void Game::MoveEnemy(float delta){
	CCPoint now = pEnemy->getPosition();
	CCPoint add = ccp(	pPlayer->getPosition().x - pEnemy->getPosition().x,
						pPlayer->getPosition().y - pEnemy->getPosition().y);
/*
	add = add.normalize();

	add.x *= 5;
	add.y *= 5;

	pEnemy->setVector(add);
*/
//	pEnemy->setPosition(now + add);
	pEnemy->update(delta);
}

void Game::CreateBullet(CCPoint in_vecter){
	Shot* bullet = (Shot*)Shot::create("Image/canser.png");

//	pBullet->addObject(bullet);
//	pBullet->addObject(new Shot());

}
void Game::MoveBullet(float delta){
	CCPoint now,add;

	CCObject* obj = NULL;
	CCARRAY_FOREACH_REVERSE(pBullet,obj){
		Shot* bullet = (Shot*)obj;
		now = bullet->getPosition();
		bullet->setPosition(now + bullet->getVector());
	}
}
/*
 *	あたり判定
 */
void Game::Collision(){
	if(pEnemy->CollisionSprite(pPlayer,false)){
		 if(!pEnemy->getHit()){
			pEnemy->setHit(true);

			AddHitEffect(pPlayer->getPosition(),1.0f);
			AddExprosion(pPlayer->getPosition());
		 }
	}
	else{
		pEnemy->setHit(false);
	}
}

/*
 *	ヒットエフェクト生成
 */
void Game::AddHitEffect(CCPoint in_pos,float time){
	CCSprite* add = this->getPackageSprite("AttackEffect.png");
	add->setPosition(in_pos);
	CCFiniteTimeAction* fade = CCFadeTo::create( time, 0);
	add->runAction(fade);
//			this->addChild(add);
	batchNode->addChild(add);
}
/*
 *	爆発エフェクト生成
 */
void Game::AddExprosion(CCPoint in_pos){
	CCParticleExplosion* pParticle
		= CCParticleExplosion::create();
	pParticle->setPosition(in_pos);
	this->addChild(pParticle);
}

void Game::menuCloseCallback(CCObject* pSender)
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

CCSprite* Game::getPackageSprite(const char* fileName){
    CCSpriteFrameCache* sfc = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCSpriteFrame* frame = sfc->spriteFrameByName(fileName);
	CCSprite* sp = new CCSprite();
	sp->autorelease();

	if( frame != NULL){
    	sp->initWithSpriteFrame(frame);
    }
    else{
    	CCLog("Load Error : %s",fileName);
    }
	return sp;
}
void Game::playSound(const char *filepath){
	CCLog("Play::%s",filepath);
	SimpleAudioEngine::sharedEngine()->playEffect(filepath);
}
