//
//  BgSprite.h
//  MyFlappyBird
//
//  Created by LiuChao on 14-3-9.
//
//

#ifndef __MyFlappyBird__BgSprite__
#define __MyFlappyBird__BgSprite__

#include "cocos2d.h"

class BgSprite : public cocos2d::CCLayer
{
private:
    cocos2d::CCSprite* ground_spA;
    cocos2d::CCSprite* ground_spB;
    
public:
    static BgSprite* create(const char* fileName);
    void init(const char* fileName);
    void update(float);
    
    virtual void onExit();
};

#endif /* defined(__MyFlappyBird__BgSprite__) */
