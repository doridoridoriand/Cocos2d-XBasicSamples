#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();

  // 'layer' is an autorelease object
  auto layer = HelloWorld::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Layer::init() )
  {
    return false;
  }


  // シングルタップリスナーを用意
  auto listener = EventListenerTouchOneByOne::create();
  //listener->setSwallowTouches(_swallowsTouches);:

  // 各イベントの割り当て
  listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
  listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
  listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
  listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

  // イベントディスパッチャーにシングルタップ用リスナーを登録する
  auto _eventDispatcher = Director::getInstance()->getEventDispatcher();
  _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

  Size visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();

  /////////////////////////////
  // 2. add a menu item with "X" image, which is clicked to quit the program
  //    you may modify it.

  // add a "close" icon to exit the progress. it's an autorelease object
  auto closeItem = MenuItemImage::create(
      "CloseNormal.png",
      "CloseSelected.png",
      CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

  closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
        origin.y + closeItem->getContentSize().height/2));

  // create menu, it's an autorelease object
  auto menu = Menu::create(closeItem, NULL);
  menu->setPosition(Vec2::ZERO);
  this->addChild(menu, 1);

  /////////////////////////////
  // 3. add your codes below...

  // add a label shows "Hello World"
  // create and initialize a label

  auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

  // position the label on the center of the screen
  label->setPosition(Vec2(origin.x + visibleSize.width/2,
        origin.y + visibleSize.height - label->getContentSize().height));

  // add the label as a child to this layer
  this->addChild(label, 1);

  // add "HelloWorld" splash screen"
  auto sprite = Sprite::create("HelloWorld.png");

  // position the sprite on the center of the screen
  // コードを生成した時に自動で生成されたやつ
  //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
  // 本に書いてあったやりかた。どちらも問題なく動く(まだ違いがわかっていないけど)
  sprite->setPosition(Point(visibleSize.width/2, visibleSize.height/2));

  // 画像のスケールの変更(今は1倍になっている)
  sprite->setScale(1);

  // 画像を回転させる
  sprite->setRotation(90);

  //画像のアンカーポイントを設定する(どこを画像の座標の基準とするか決める)
  sprite->setAnchorPoint(Point(0, 0));

  // add the sprite as a child to this layer
  this->addChild(sprite, 0);

  // ラベルを表示する
  auto text = Label::createWithSystemFont("よしおアンダーソン", "HiraKakuProN-W6", 48);
  text->setPosition(Point(300, 100));
  this->addChild(text);

  //ローテーションさせたりとかは他と同じなので省略

  /*✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨ 🌙🌙🌙🌙🌙🌙🌙🌙🌙🌙🌙🌙🌙🌙*/
  /* オブジェクトを移動させたりするよ*/
  /*✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨ 🌙🌙🌙🌙🌙🌙🌙🌙🌙🌙🌙🌙🌙🌙*/
  // 2秒間に現在の位置から(x, y) = (100, 100)移動するという意味
  auto move = MoveBy::create(2, Point(100, 100));
  sprite->runAction(move);

  // 時間経過と共にスケールを変更する
  // 2秒間に現在の大きさから1.5倍にする
  auto scale = ScaleBy::create(2, 1.5);
  sprite->runAction(scale);

  // 回転させる
  auto rotate = RotateBy::create(2, 90);
  sprite->runAction(rotate);

  /***************
   * 今までのメソッドは現在の一からの相対量をしてしていた。しかし絶対量を示したい場合もある。その時は
   * Toメソッドを使用する。 ex. Moveby -> MoveTo
   */

  // 反転させる
  auto flip = FlipY::create(true);
  sprite->runAction(flip);

  // ログ出力 String型
  log("あああああああああああああああああああああああああああああああああああああああああああああああああああ");

  return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
  Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}

// スワイプの挙動の認識を確かめるために、イベントを設定。ログに吐き出す
bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event) {
  CCLOG("onTouchBegan");
  return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* unused_event) {
  CCLOG("onTouchMoved");
}

void HelloWorld::onTouchEnded(Touch* touch, Event* unused_event) {
  CCLOG("onTouchEnded");
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* unused_event) {
  CCLOG("onTouchCancelled");
}
