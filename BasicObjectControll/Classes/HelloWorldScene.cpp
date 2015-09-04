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

  //ログ出力 String型
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
