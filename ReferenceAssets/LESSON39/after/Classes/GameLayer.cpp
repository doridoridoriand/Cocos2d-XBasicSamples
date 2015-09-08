#include "GameLayer.h"

#define WINSIZE Director::getInstance()->getWinSize()

#define BALL_INIT_POS Point(100, 150)
#define BALL_STRETCH_LENGTH 50

#define LAUNCHER_POS1 Point( 80, 135)
#define LAUNCHER_POS2 Point(125, 140)

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

    //ボールの生成
    createBall();
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
    bool ret = false;
    
    auto ball = getChildByTag(T_Ball);
    if (ball && ball->getBoundingBox().containsPoint(touch->getLocation()))
    {
        //ボールの位置を算出
        ball->setPosition(calculatedPosition(touch->getLocation()));
        ret = true;
    }
    
    return ret;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event)
{
    auto ball = getChildByTag(T_Ball);
    if (ball)
    {
        //ボールの位置を算出
        ball->setPosition(calculatedPosition(touch->getLocation()));
        
        //ゴムを伸ばすポイント
        auto angle = ((BALL_INIT_POS - ball->getPosition()).getAngle());
        auto pos = ball->getPosition() + Point(-25, 0).rotate(Point::forAngle(angle));
        
        //ゴムの表示
        auto gum1 = getChildByTag(T_Gum1);
        if (!gum1)
        {
            gum1 = Sprite::create("brown.png");
            addChild(gum1, Z_Gum1, T_Gum1);
        }
        
        gum1->setPosition(LAUNCHER_POS1 - (LAUNCHER_POS1 - pos) / 2);
        gum1->setRotation(CC_RADIANS_TO_DEGREES((LAUNCHER_POS1 - pos).getAngle() * -1));
        gum1->setScaleX(LAUNCHER_POS1.getDistance(pos));
        gum1->setScaleY(10);
        
        auto gum2 = getChildByTag((int)T_Gum2);
        if (!gum2)
        {
            gum2 = Sprite::create("brown.png");
            addChild(gum2, Z_Gum2, T_Gum2);
        }
        
        gum2->setPosition(LAUNCHER_POS2 - (LAUNCHER_POS2 - pos) / 2);
        gum2->setRotation(CC_RADIANS_TO_DEGREES((LAUNCHER_POS2 - pos).getAngle() * -1));
        gum2->setScaleX(LAUNCHER_POS2.getDistance(pos));
        gum2->setScaleY(10);
    }
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event)
{
    auto ball = getChildByTag(T_Ball);
    if (ball)
    {
        //ゴムを削除
        removeChildByTag(T_Gum1);
        removeChildByTag(T_Gum2);
        
        //ボールの位置を算出
        ball->setPosition(calculatedPosition(touch->getLocation()));
        
        //ボールに飛ばす力を追加する
        applyingForceToBall(ball);
    }
}

void GameLayer::onTouchCanceled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}

//ボールの生成
void GameLayer::createBall()
{
    //ボールの生成
    auto ball = Sprite::create("ball.png");
    ball->setPosition(BALL_INIT_POS);
    ball->setTag(T_Ball);
    ball->setZOrder(Z_Ball);
    
    //物質的特徴の設定
    PhysicsMaterial material;
    material.density = 0.5;
    material.restitution = 0.5;
    material.friction = 0.3;
    
    //物理構造の設定
    auto body = PhysicsBody::createCircle(ball->getContentSize().width * 0.47, material);
    body->setDynamic(false);
    ball->setPhysicsBody(body);
    
    //ボールをレイヤーに追加
    addChild(ball);
    
    //発射台を追加
    auto launcher1 = Sprite::create("launcher1.png");
    launcher1->setScale(0.5);
    launcher1->setPosition(Point(100, 100));
    addChild(launcher1, Z_Launcher1);
    
    auto launcher2 = Sprite::create("launcher2.png");
    launcher2->setScale(0.5);
    launcher2->setPosition(launcher1->getPosition());
    addChild(launcher2, Z_Launcher2);
}

//ボールの位置を算出
Point GameLayer::calculatedPosition(Point touchPosition)
{
    //ボールの初期位置とタップ位置の距離
    int distance = touchPosition.getDistance(BALL_INIT_POS);
    
    if (distance > BALL_STRETCH_LENGTH)
        //距離がBALL_STRETCH_LENGTHとなる位置を返す
        return BALL_INIT_POS + (touchPosition - BALL_INIT_POS) * BALL_STRETCH_LENGTH / distance;
    else
        //タップ位置を返す
        return touchPosition;
}

//ボールに飛ぶ力を加える
void GameLayer::applyingForceToBall(Node* ball)
{
    //ボールを自由に動けるようする
    ball->getPhysicsBody()->setDynamic(true);
    
    //ボールに力を加える
    Vect force = (ball->getPosition() - BALL_INIT_POS) * -10000;
    ball->getPhysicsBody()->resetForces();
    ball->getPhysicsBody()->applyImpulse(force);
}
