#include "AppDelegate.h"
#include "Scene/HelloWorldScene.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"
#include "../CocosDenshion/include/SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate() {
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->setDepthTest(true);
	pDirector->setProjection(kCCDirectorProjection2D);
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    //CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    // turn on display FPS
    pDirector->setDisplayStats(true);

    CCEGLView* pEGLView = CCDirector::sharedDirector()->getOpenGLView();
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(320,480,kResolutionExactFit);

    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
    SimpleAudioEngine::sharedEngine()->preloadEffect("sound/cat.wav");
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/title_bgm.mp3");
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object

    //CCScene *pScene = HelloWorld::scene();
    //CCScene *pScene = Title::scene();
    CCScene *pScene = Game::scene();
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
