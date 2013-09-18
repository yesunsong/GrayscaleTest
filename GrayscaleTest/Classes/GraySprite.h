//
//  GraySprite.h
//  TestProject
//
//  Created by 叶孙松 on 13-9-4.
//
//

#ifndef __TestProject__GraySprite__
#define __TestProject__GraySprite__

#include "cocos2d.h"

class GraySprite : public cocos2d::CCSprite{
public:
    GraySprite();
    virtual ~GraySprite();
    static  GraySprite* create(const char* pszFileName);
//    static CCSprite* createWithSprite(cocos2d::CCSprite *sprite);
//    static GraySprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    
//    static GraySprite* createWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame);
     void setGray(bool isGray);
    void draw();
private:  
    const char *  m_pszFilename;   
    bool initWithFile(const char *pszFilename);
};

#endif /* defined(__TestProject__GraySprite__) */
