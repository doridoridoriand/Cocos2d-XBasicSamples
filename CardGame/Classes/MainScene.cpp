#include "MainScene.h"

#define CARD_NUM 13 // 1種類あたりのカードの枚数
#define CARD_TYPE_NUM 4 // カードの種類の総数
#define CARD_1_POS_X 200 // 1番目のカードの位置(x)
#define CARD_1_POS_Y 320 // 1番目のカードの位置(y)
#define CARD_DISTANCE_X 140 // カード間の距離(x)
#define CARD_DISTANCE_Y 200 // カード間の距離(y)
#define Z_ORDER_SHOW_CARD 1 // 表示しているカードのZオーダー

USING_NS_CC;
using namespace std;

Scene* Main::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();

  // 'layer' is an autorelease object
  auto layer = Main::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

// on "init" you need to initialize your instance
bool Main::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Layer::init() )
  {
    return false;
  }
  return true;
}

void Main::initCards() {
  // 配列を用意
  _cards.clear();

  // カードを52枚用意する
  for (int type = 0; type < CARD_TYPE_NUM; type++) {
    for (int number = 1; number <= CARD_NUM; number++) {
      // Card構造体を参照 => enumの中身を確認
      Card card;
      card.number = number;
      card.type = (CardType)type;

      _cards.push_back(card);
    }
  }
}

Card Main::getCard() {
  random_device rd;
  // メルセンヌツイスターを使用して乱数を発生させる
  mt19937 rand = mt19937(rd());

  // インデックスをランダムに取得する
  int index = uniform_int_distribution<int>(0, (int)_cards.size() - 1)(rand);

  auto card = _cards[index];

  // _cardsはあくまで中間生成物なので、必要なくなったらメモリ節約のために削除
  _cards.erase(_cards.begin() + index);

  return card;
}
