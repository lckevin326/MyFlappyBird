//
//  KKContactLinstener.h
//  Chapt09-Contact
//
//  Created by ibokan on 13-11-1.
//  Copyright (c) 2013年 kevin. All rights reserved.
//

#ifndef __Chapt09_Contact__KKContactLinstener__
#define __Chapt09_Contact__KKContactLinstener__

#include "cocos2d.h"
#include "Box2D.h"

class KKContactLinstener : public b2ContactListener
{
    
public:
    b2Body *_body;
    b2World *_world;
    cocos2d::CCLayer* currentLayer;
    
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};


#endif /* defined(__Chapt09_Contact__KKContactLinstener__) */
