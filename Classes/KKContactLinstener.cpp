//
//  KKContactLinstener.cpp
//  Chapt09-Contact
//
//  Created by ibokan on 13-11-1.
//  Copyright (c) 2013年 kevin. All rights reserved.
//

#include "KKContactLinstener.h"
#include "cocos2d.h"
#include "B2Sprite.h"
#include "BgSprite.h"
#include "GameStartScene.h"

void KKContactLinstener::BeginContact(b2Contact *contact)
{
    b2Body *bodyA = contact -> GetFixtureA() -> GetBody();
    b2Body *bodyB = contact -> GetFixtureB() -> GetBody();
    
    B2Sprite *spriteB = (B2Sprite *)bodyB->GetUserData();
    B2Sprite *spriteA = (B2Sprite *)bodyA->GetUserData();
    
    if (spriteA != NULL && spriteB != NULL)
    {
        CCLOG("A-Name = %s",spriteA->getSpriteName());
        CCLOG("B-Name = %s",spriteB->getSpriteName());
        
        const char* A_name = spriteA->getSpriteName();
        const char* B_name = spriteB->getSpriteName();
        const char* bird = "小鸟";
        const char* bar = "柱子";
        const char* ground = "地面";

        
        if ((strcmp(A_name, bird)==0 && strcmp(B_name, bar)==0) || (strcmp(A_name, ground)==0 && strcmp(B_name, bird)==0))
        {
            CCLOG("++++++++++++++++++++++++++++++++++++++");
            CCLOG("碰撞了！！！");
            CCLOG("++++++++++++++++++++++++++++++++++++++");
            
            // 停止地面运动
            BgSprite* bgSprite = (BgSprite *)currentLayer->getChildByTag(2);
            bgSprite->unscheduleUpdate();
            
            // 停止出现柱子
            currentLayer->unschedule(schedule_selector(GameStartScene::addBar));
            
//            CCDirector::sharedDirector()->stopAnimation();
//            CCSize size = CCDirector::sharedDirector()->getWinSize();
//            CCSprite* gameOver = CCSprite::createWithSpriteFrameName("gameover.png");
//            gameOver->setPosition(ccp(size.width/2, size.height/2));
//            currentLayer->addChild(gameOver,10);
        }
        
    }
    
}

void KKContactLinstener::EndContact(b2Contact *contact)
{
    
}




