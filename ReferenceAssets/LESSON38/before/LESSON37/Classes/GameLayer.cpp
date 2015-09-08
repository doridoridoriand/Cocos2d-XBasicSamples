#include "GameLayer.h"

#define WINSIZE Director::getInstance()->getWinSize()

USING_NS_CC;

//シーン生成
Scene* GameLayer::createScene()
{
    auto scene = Scene::createWithPhysics(); //シーンを生成する
    auto layer = GameLayer::create(); //GameLayerクラスのレイヤーを生成する
    scene->addChild(layer); //シーンに対してレイヤーを追加する
    
    return scene; //シーンを返す
}

//初期化
bool GameLayer::init()
{
    if (!Layer::init())
        return false;
    
    //シングルタップイベントの取得
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

//レイヤー表示時処理
void GameLayer::onEnter()
{
    Layer::onEnter();
    
    //重力
    auto v = Vect(0, -98);
    auto scene = dynamic_cast<Scene*>(this->getParent());
    scene->getPhysicsWorld()->setGravity(v);
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    //背景の生成
    createBackground();
    
    //地面の生成
    createGround();
}

//背景の生成
void GameLayer::createBackground()
{
    //背景の設定
    auto background = Sprite::create("background.png");
    background->setAnchorPoint(Point(0, 0.5));
    background->setPosition(Point(0, WINSIZE.height / 2));
    addChild(background, Z_Background, T_Background);
}

//地面の生成
void GameLayer::createGround()
{
    auto background = getChildByTag(T_Background);
    
    //物質的特徴の設定
    PhysicsMaterial material;
    material.density = 0.5;
    material.restitution = 0.5;
    material.friction = 0.8;
    
    //物理構造の設定
    auto body = PhysicsBody::createBox(Size(background->getContentSize().width, 50), material);
    body->setDynamic(false);
    
    //地面ノードの作成
    auto node = Node::create();
    node->setAnchorPoint(Point::ANCHOR_MIDDLE);
    node->setPhysicsBody(body);
    node->setPosition(Point(background->getContentSize().width / 2, 25));
    addChild(node);
}

//敵の生成
void GameLayer::createEnemy(cocos2d::Point position)
{
    //敵の生成
    auto enemy = Sprite::create("enemy1.png");
    enemy->setPosition(position);
    enemy->setTag(T_Enemy);
    
    //敵のアニメーション
    auto animation = Animation::create();
    animation->addSpriteFrameWithFile("enemy2.png");
    animation->addSpriteFrameWithFile("enemy1.png");
    animation->setDelayPerUnit(1);
    
    auto repeat = RepeatForever::create(Animate::create(animation));
    enemy->runAction(repeat);
    
    //物質的特徴の設定
    PhysicsMaterial material;
    material.density = 0.5;
    material.restitution = 0.5;
    material.friction = 0.3;
    
    //物理構造の設定
    auto body = PhysicsBody::createCircle(enemy->getContentSize().width * 0.47, material);
    body->setDynamic(true);
    enemy->setPhysicsBody(body);
    
    //敵をレイヤーに追加
    addChild(enemy, Z_Enemy);
}

bool GameLayer::onTouchBegan(Touch* touch, Event* unused_event)
{
    createEnemy(touch->getLocation());
    
    return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event)
{
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event)
{
}

void GameLayer::onTouchCanceled(Touch* touch, Event* unused_event)
{
}
