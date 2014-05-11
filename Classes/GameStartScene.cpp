//
//  GameStartScene.cpp
//  MyFlappyBird
//
//  Created by LiuChao on 14-3-9.
//
//

#include "GameStartScene.h"
#include "BgSprite.h"

#define MENU_TAG 1
#define BG_SPRITE_TAG 2

using namespace cocos2d;

CCScene* GameStartScene::scene()
{
    CCScene* scene = CCScene::create();
    GameStartScene* layer = GameStartScene::create();
    scene->addChild(layer);
    return scene;
}

GameStartScene::~GameStartScene()
{
    delete m_world;
    m_world = NULL;
    
    delete m_debugDraw;
    m_debugDraw = NULL;
    
    delete m_bird;
    m_bird = NULL;
    
    delete m_contactLinstener;
    m_contactLinstener = NULL;
}

bool GameStartScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("flappy_packer.plist");
    
    CCSprite* startSprite = CCSprite::createWithSpriteFrameName("getready.png");
    CCMenuItemSprite* item = CCMenuItemSprite::create((CCNode*)startSprite, (CCNode*)startSprite, this, menu_selector(GameStartScene::startGame));
    CCMenu* menu = CCMenu::create(item,NULL);
    addChild(menu, 10, MENU_TAG);

    setTouchEnabled(true);
    
    BgSprite* bgSprite = BgSprite::create("ground.png");
    this->addChild(bgSprite,0, BG_SPRITE_TAG);
    
    initWorld();
    
    
    return true;
}

void GameStartScene::startGame()
{
    CCMenu* menu = (CCMenu *)this->getChildByTag(1);
    menu->removeFromParent();
    
//    scheduleOnce(schedule_selector(GameStartScene::addBird), 1.0f);
    addBird();
    scheduleUpdate();
    schedule(schedule_selector(GameStartScene::addBar), 2.5f);
}

void GameStartScene::initWorld()
{
    b2Vec2 gravity(0, -60);
    m_world = new b2World(gravity);
    
    m_debugDraw = new GLESDebugDraw(PTM_RATIO);
    m_world->SetDebugDraw(m_debugDraw);
    
    m_contactLinstener = new KKContactLinstener();
    m_contactLinstener->currentLayer = this;
    m_world->SetContactListener(m_contactLinstener);
    
    
    uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	m_debugDraw->SetFlags(flags);
    
    B2Sprite* ground = B2Sprite::create("ground.png");
    CCSize g_Size = ground->getContentSize();
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = b2Vec2(g_Size.width/2/PTM_RATIO, g_Size.height/2/PTM_RATIO);
    b2Body* groundBody = m_world->CreateBody(&bodyDef);
    
    b2PolygonShape shape;
    shape.SetAsBox(g_Size.width/2/PTM_RATIO, g_Size.height/2/PTM_RATIO);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    groundBody->CreateFixture(&fixtureDef);
    
    ground->setB2Body(groundBody);
    ground->setPTMRatio(PTM_RATIO);
    ground->setName("地面");
    addChild(ground,-1);
    
}

void GameStartScene::draw()
{
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	
	kmGLPushMatrix();
	
	m_world->DrawDebugData();
	
	kmGLPopMatrix();
}

void GameStartScene::update(float dt)
{
    m_world->Step(dt, 8, 1);
    
    CCArray* barSprites = this->getChildren();
    for (int i = 0; i < barSprites->count(); i++)
    {
        B2Sprite* sprite = (B2Sprite *)barSprites->objectAtIndex(i);
        if (sprite->getPositionX() < -sprite->getContentSize().width)
        {
            sprite->removeFromParent();
        }
    }
}

void GameStartScene::addBird()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    m_bird = B2Sprite::createWithSpriteFrameName("bird1.png");
    CCSize birdSize = m_bird->getContentSize();
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(size.width/2.5/PTM_RATIO, size.height/2/PTM_RATIO);
    
    b2PolygonShape shape;
    shape.SetAsBox(birdSize.width/2/PTM_RATIO, birdSize.height/2/PTM_RATIO);
    
    b2Body* body = m_world->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 5.0f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);
    
    b2MassData* MassData = new b2MassData;
    MassData->mass = 0.1f;
    MassData->I = 0.0f;
    b2Vec2 center;
    center.Set(0.9f, 0.5f);
    MassData->center = center;
    body->SetMassData(MassData);
    
    m_bird->setPTMRatio(PTM_RATIO);
    m_bird->setB2Body(body);
    m_bird->setName("小鸟");
    addChild(m_bird,1);
    
}

void GameStartScene::addBar(float dt)
{
    float offset = -rand()%10;
    
    // 下面柱子
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    B2Sprite* downBar = B2Sprite::createWithSpriteFrameName("holdback1.png");
    CCSize downBar_size = downBar->getContentSize();
    
    b2BodyDef down_bar_bodyDef;
    down_bar_bodyDef.type = b2_kinematicBody;
    down_bar_bodyDef.position = b2Vec2(size.width/PTM_RATIO+4, downBar_size.height/PTM_RATIO/2 + offset);
    down_bar_bodyDef.linearVelocity = b2Vec2(-5, 0);
    b2Body* down_bar = m_world->CreateBody(&down_bar_bodyDef);
    
    b2PolygonShape down_bar_shape;
    down_bar_shape.SetAsBox(downBar_size.width/2/PTM_RATIO, downBar_size.height/2/PTM_RATIO);
    b2FixtureDef down_bar_fixtureDef;
    down_bar_fixtureDef.shape = &down_bar_shape;
    down_bar->CreateFixture(&down_bar_fixtureDef);
    
    downBar->setB2Body(down_bar);
    downBar->setPTMRatio(PTM_RATIO);
    downBar->setName("柱子");
    addChild(downBar);
    
    float downY = downBar->getPositionY();
    CCLog("downY = %f",downY);
    
    // 上面柱子
    B2Sprite* upBarSprite = B2Sprite::createWithSpriteFrameName("holdback2.png");
    CCSize upBar_size = upBarSprite->getContentSize();
    
    b2BodyDef up_bar_bodyDef;
    up_bar_bodyDef.type = b2_kinematicBody;
    up_bar_bodyDef.position = b2Vec2(size.width/PTM_RATIO+4, downY/PTM_RATIO+downBar_size.height/2/PTM_RATIO+8+upBar_size.height/2/PTM_RATIO);
    up_bar_bodyDef.linearVelocity = b2Vec2(-5, 0);
    b2Body* up_bar = m_world->CreateBody(&up_bar_bodyDef);
    
    b2PolygonShape up_bar_shape;
    up_bar_shape.SetAsBox(upBar_size.width/2/PTM_RATIO, upBar_size.height/2/PTM_RATIO);
    b2FixtureDef up_bar_fixtureDef;
    up_bar_fixtureDef.shape = &up_bar_shape;
    up_bar->CreateFixture(&up_bar_fixtureDef);
    
    upBarSprite->setB2Body(up_bar);
    upBarSprite->setPTMRatio(PTM_RATIO);
    upBarSprite->setName("柱子");
    addChild(upBarSprite);
}

void GameStartScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if (m_bird)
    {
        m_bird->getB2Body()->SetLinearVelocity(b2Vec2(0, 23));
    }
    
}






