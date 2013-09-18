//
//  BgraySprite.h
//  TestProject
//
//  Created by 叶孙松 on 13-9-6.
//
//

#ifndef __TestProject__BgraySprite__
#define __TestProject__BgraySprite__

#include "cocos2d.h"

class BgraySprite : public cocos2d::CCSprite{
public:
    BgraySprite();
    virtual ~BgraySprite();
    
    static BgraySprite* createWithSpriteFrameName(const char *pszSpriteFrameName);    
    static BgraySprite* createWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame);
    
    void setGray(bool isGray);
    
    bool initWithTexture(cocos2d::CCTexture2D* pTexture, const cocos2d::CCRect& tRect);
private:
   
};

#endif /* defined(__TestProject__BgraySprite__) */
