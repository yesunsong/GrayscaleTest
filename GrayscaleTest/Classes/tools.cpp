//
//  tools.cpp
//  TestProject
//   
//  Created by 叶孙松 on 13-9-6.
//
//

#include "tools.h"

USING_NS_CC;

/*使用方法：
 CCSprite* testSprite=CCSprite::create("test.png");
 CCSprite* sprite=grayWithCCNode(testSprite, true);
 sprite->setPosition(ccp(100,200));
 addChild(sprite);*/
//根据现有CCNode变灰,然后存为CCSprite
CCSprite* grayWithCCNode(CCNode* oldSprite,bool isGray){
    CCSprite* newSprite = CCSprite::createWithTexture(getTexture(oldSprite,isGray));
    return newSprite;
}
//传入CCNode，根据条件是否变灰，然后返回之后的纹理
CCTexture2D* getTexture(CCNode* sprite,bool isGray){
    CCPoint p = sprite->getAnchorPoint();    
    sprite->setAnchorPoint(ccp(0,0));
    CCRenderTexture *outTexture = CCRenderTexture::create((int)sprite->getContentSize().width,(int)sprite->getContentSize().height);
    outTexture->begin();
    sprite->visit();
    outTexture->end();
    sprite->setAnchorPoint(p);
    ///////////////////////////////////////////////////////////////////////
    CCImage* finalImage = outTexture->newCCImage();
    unsigned char *pData = finalImage->getData();
    ///////////////////////////////////////////////////////////////////////
    int iIndex = 0;
    if(isGray){
        for (int i = 0; i < finalImage->getHeight(); i ++){
            for (int j = 0; j < finalImage->getWidth(); j ++){
                // gray
                int iBPos = iIndex;
                unsigned int iB = pData[iIndex];
                iIndex ++;
                unsigned int iG = pData[iIndex];
                iIndex ++;
                unsigned int iR = pData[iIndex];
                iIndex ++;
                //unsigned int o = pData[iIndex];
                iIndex ++; //原来的示例缺少
                unsigned int iGray = 0.3 * iR + 0.4 * iG + 0.2 * iB;
                pData[iBPos] = pData[iBPos + 1] = pData[iBPos + 2] = (unsigned char)iGray;
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////
    CCTexture2D *texture = new CCTexture2D;
    texture->initWithImage(finalImage);
    delete finalImage;
    texture->autorelease();
    ///////////////////////////////////////////////////////////////////////
    return  texture;
}