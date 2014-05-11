//
//  BgSprite.cpp
//  MyFlappyBird
//
//  Created by LiuChao on 14-3-9.
//
//

#include "BgSprite.h"
using namespace cocos2d;

BgSprite* BgSprite::create(const char *fileName)
{
    BgSprite* bgSprite = new BgSprite();
    if (bgSprite && bgSprite -> CCLayer::create())
    {
        bgSprite -> init(fileName);
        bgSprite -> autorelease();
        return bgSprite;
    }
    else
    {
        CC_SAFE_DELETE(bgSprite);
        return NULL;
    }
}

void BgSprite::init(const char *fileName)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bgSprite = CCSprite::create("bg.png");
    bgSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bgSprite, -10, 1);
    
    ground_spA = CCSprite::create("ground.png");
    ground_spA->setPosition(ccp(size.width/2, ground_spA->getContentSize().height/2));
    this->addChild(ground_spA);
    
    ground_spB = CCSprite::create("ground.png");
    ground_spB->setPosition(ccp(size.width/2+ground_spA->getContentSize().width-5, ground_spB->getContentSize().height/2));
    this->addChild(ground_spB);
    
    this->scheduleUpdate();
}

void BgSprite::update(float delt)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    if (ground_spA->getPositionX() < -ground_spA->getContentSize().width/2)
    {
        ground_spA->setPosition(ccp(size.width/2 + ground_spA->getContentSize().width-5, ground_spA->getContentSize().height/2));
    }
    else
        ground_spA->setPosition(ccpSub(ground_spA->getPosition(), ccp(3, 0)));
    
    if (ground_spB->getPositionX() < -ground_spB->getContentSize().width/2)
    {
        ground_spB->setPosition(ccp(size.width/2+ground_spA->getContentSize().width-5, ground_spB->getContentSize().height/2));
    }
    else
        ground_spB->setPosition(ccpSub(ground_spB->getPosition(), ccp(3, 0)));
    
    
}

void BgSprite::onExit()
{
    
}
