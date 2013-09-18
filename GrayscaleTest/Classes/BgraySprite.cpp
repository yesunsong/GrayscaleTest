//
//  BgraySprite.cpp
//  TestProject
//  利用Shader设置 重写了createWithSpriteFrameName()
//  Created by 叶孙松 on 13-9-6.
//
//

#include "BgraySprite.h"

USING_NS_CC;

BgraySprite::BgraySprite(){
}

BgraySprite::~BgraySprite(){
}

BgraySprite* BgraySprite::createWithSpriteFrameName(const char *pszSpriteFrameName){
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
#endif
    
    return createWithSpriteFrame(pFrame);
}

BgraySprite* BgraySprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame){
    BgraySprite *pobSprite = new BgraySprite();
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame)){
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

bool BgraySprite::initWithTexture(CCTexture2D* pTexture, const CCRect& tRect ){
    do{
        CC_BREAK_IF(!CCSprite::initWithTexture(pTexture, tRect));
        
        GLchar* pszFragSource =
        "#ifdef GL_ES \n \
        precision mediump float; \n \
        #endif \n \
        uniform sampler2D u_texture; \n \
        varying vec2 v_texCoord; \n \
        varying vec4 v_fragmentColor; \n \
        void main(void) \n \
        { \n \
        // Convert to greyscale using NTSC weightings \n \
        // float grey = dot(texture2D(u_texture, v_texCoord).rgb, vec3(0.299, 0.587, 0.114)); \n \
        //gl_FragColor = vec4(grey, grey, grey, 1.0); \n \
        vec4 col = texture2D(u_texture, v_texCoord); \n \
        float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114)); \n \
        gl_FragColor = vec4(grey, grey, grey, col.a); \n \
    }";
        
        CCGLProgram* pProgram = new CCGLProgram();
        pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
        this->setShaderProgram(pProgram);
        pProgram->release();
        CHECK_GL_ERROR_DEBUG();
        
        this->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        this->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
        this->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        CHECK_GL_ERROR_DEBUG();
        
        this->getShaderProgram()->link();
        CHECK_GL_ERROR_DEBUG();
        
        this->getShaderProgram()->updateUniforms();
        CHECK_GL_ERROR_DEBUG();
        
        return true;
    } while (0);       
    
    return false;
}