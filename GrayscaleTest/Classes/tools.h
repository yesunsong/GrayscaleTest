//
//  tools.h
//  TestProject
//
//  Created by 叶孙松 on 13-9-6.
//
//

#ifndef __TestProject__tools__
#define __TestProject__tools__

#include "cocos2d.h"

USING_NS_CC;

cocos2d::CCTexture2D* getTexture(cocos2d::CCNode* sprite,bool isGray);
//根据现有CCNode变灰
cocos2d::CCSprite* grayWithCCNode(cocos2d::CCNode* oldSprite,bool isGray);
#endif /* defined(__TestProject__tools__) */
