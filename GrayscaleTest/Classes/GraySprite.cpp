//
//  GraySprite.cpp
//  TestProject
//  支持.png
//  Created by 叶孙松 on 13-9-4.
//
//

#include "GraySprite.h"

USING_NS_CC;

GraySprite::GraySprite(){
}

GraySprite::~GraySprite(){
}
//create
GraySprite* GraySprite::create(const char* pszFileName){
    GraySprite *pobSprite = new GraySprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName)) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

////createWithSpriteFrameName
//GraySprite* GraySprite::createWithSpriteFrameName(const char *pszSpriteFrameName){
//    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
//    
//#if COCOS2D_DEBUG > 0
//    char msg[256] = {0};
//    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
//    CCAssert(pFrame != NULL, msg);
//#endif
//    
//    return createWithSpriteFrame(pFrame);
//}
//
////createWithSpriteFrame
//GraySprite* GraySprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame){
//     GraySprite *pobSprite = new GraySprite();
//    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame)){
//        pobSprite->autorelease();
//        return pobSprite;
//    }
//    CC_SAFE_DELETE(pobSprite);
//    return NULL;
//}

//initWithFile
bool GraySprite::initWithFile(const char *pszFilename){
  m_pszFilename=pszFilename;
    return CCSprite::initWithFile(pszFilename);
}

void GraySprite::setGray(bool isGray){
    CCImage* finalImage=new CCImage();
    finalImage->initWithImageFile(m_pszFilename);
    
//    CCPoint p = this->getAnchorPoint();
//    this->setAnchorPoint(ccp(0,0));
//    CCRenderTexture *outTexture = CCRenderTexture::create((int)this->getContentSize().width,(int)this->getContentSize().height);
//    outTexture->begin();
//    this->visit();
//    outTexture->end();
//    this->setAnchorPoint(p);
//    
//    CCImage* finalImage = outTexture->newCCImage();

    unsigned char *pData = finalImage->getData();
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
              
                iIndex ++; //原来的示例缺少
                unsigned int iGray = 0.3 * iR + 0.4 * iG + 0.2 * iB;
                pData[iBPos] = pData[iBPos + 1] = pData[iBPos + 2] = (unsigned char)iGray;
            }
        }
    }

    CCTexture2D *pTexture = new CCTexture2D;
    pTexture->initWithImage(finalImage);

    setTexture(pTexture);
    
    delete finalImage;
    pTexture->release();
}

void GraySprite::draw(){
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
    
    this->getShaderProgram()->use();
    //    this->getShaderProgram()->setUniformForModelViewProjectionMatrix();//原来的
    this->getShaderProgram()->setUniformsForBuiltins();//我自己添加的
    
    ccGLBindTexture2D( this->getTexture()->getName());
    
#define kQuadSize sizeof(m_sQuad.bl)
    long offset = (long)&m_sQuad;
    
    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    CC_INCREMENT_GL_DRAWS(1);
}