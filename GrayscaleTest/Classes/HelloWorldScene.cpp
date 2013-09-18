#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "GraySprite.h"
#include "BgraySprite.h"
#include "tools.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene(){
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init(){ 
    if ( !CCLayer::init()){
        return false;
    }    
    /////////////////////////////
    size=CCDirector::sharedDirector()->getWinSize();
    /////////////////////////////    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero.plist", "hero.png");
    //
    //GraySprite支持create()，支持变回彩色
//    testSprite= GraySprite::create("test.png");
//    testSprite->setAnchorPoint(ccp(0, 1));
//    testSprite->setGray(true);
//    testSprite->setPosition(ccp(0, 600));
//    addChild(testSprite);

   //根据SpriteFrameName灰化,BgraySprite支持createWithSpriteFrameName（），不支持变回彩色
//    CCSprite*  frameSprite= BgraySprite::createWithSpriteFrameName("card.png");
//    frameSprite->setAnchorPoint(ccp(0, 1));
//    frameSprite->setPosition(ccp(testSprite->getPositionX()+testSprite->getContentSize().width, 600));
//    addChild(frameSprite);

    //传入CCNode，支持变回彩色
//    CCSprite* colorSprite=CCSprite::create("test.png");
//    CCSprite* sprite=grayWithCCNode(colorSprite, true);
//    sprite->setAnchorPoint(ccp(0, 1));
//    sprite->setPosition(ccp(frameSprite->getPositionX()+frameSprite->getContentSize().width,600));
//    addChild(sprite);

//    this->schedule(schedule_selector(HelloWorld::updateThis), 2.0f);
//    //
    CCSprite* test1=CCSprite::createWithSpriteFrameName("card.png");
    CCSprite* test2=CCSprite::create("test.png");
    test1->setPosition(ccp(100, 100));
    test2->setPosition(ccp(200, 100));
    CCLayer* layer=CCLayer::create();
    layer->addChild(test1);
    layer->addChild(test2);
    layer->setPosition(ccp(100,200));
    addChild(layer);  
    layer->setContentSize(CCSizeMake(400, 500));
    
    CCSprite* sp= grayWithCCNode(layer, true);
    sp->setAnchorPoint(ccp(0,0));
    sp->setPosition(ccp(0,0));
    sp->setColor(ccc3(255, 0, 0));
    CCLog("%f %f",sp->getAnchorPoint().x,sp->getAnchorPoint().y);
    CCLog("%f %f",sp->getContentSize().width,sp->getContentSize().height);
    addChild(sp);
    //
    return true;
}

void HelloWorld::updateThis(CCObject *pSender){
    testSprite->setGray(false);
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
