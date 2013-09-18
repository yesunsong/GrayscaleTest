#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init(){
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )    {
        return false;
    }
    
    /////////////////////////////
    size=CCDirector::sharedDirector()->getWinSize();
    /////////////////////////////
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(pSprite, 0);
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero.plist", "hero.png");
    //
    //GraySprite支持create()，支持变回彩色
    GraySprite*  frameSprite= GraySprite::create("test.png");
    frameSprite->setGray(true);
    frameSprite->setPosition(ccp(100, 200));
    addChild(frameSprite);

//    //根据SpriteFrameName灰化,BgraySprite支持createWithSpriteFrameName（），不支持变回彩色
//    CCSprite*  frameSprite= BgraySprite::createWithSpriteFrameName("card.png");
//    frameSprite->setPosition(ccp(100, 200));
//    addChild(frameSprite);

//    //传入CCNode，支持变回彩色
//    CCSprite* testSprite=CCSprite::create("test.png");
//    CCSprite* sprite=grayWithCCNode(testSprite, true);
//    sprite->setPosition(ccp(100,200));
//    addChild(sprite);

    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
