//
//  GameStartScene.h
//  MyFlappyBird
//
//  Created by LiuChao on 14-3-9.
//
//

#ifndef __MyFlappyBird__GameStartScene__
#define __MyFlappyBird__GameStartScene__

#include "cocos2d.h"
#include "Box2D.h"
#include "B2Sprite.h"
#include "GLES-Render.h"
#include "KKContactLinstener.h"

#define PTM_RATIO 32.0f

class GameStartScene : public cocos2d::CCLayer
{
private:
    void addBird();
    
    CCArray* downBars;
    CCArray* upBars;
    
public:
    b2World* m_world;
    B2Sprite* m_bird;
    GLESDebugDraw* m_debugDraw;
    KKContactLinstener* m_contactLinstener;
    
    void startGame();
    void addBar(float dt);
    virtual bool init();
    virtual void update(float dt);
    void initWorld();
    void draw();
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    ~GameStartScene();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameStartScene);
};

#endif /* defined(__MyFlappyBird__GameStartScene__) */
