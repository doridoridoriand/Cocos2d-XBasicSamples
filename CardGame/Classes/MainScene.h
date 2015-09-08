#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

// カードの種類を定義
enum CardType {
    Clubs = 0,
    Diamonds,
    Hearts,
    Spades
};

// カード
struct Card {
    int number;
    CardType type;
};

// カードを表示する位置
struct PosIndex {
    int x;
    int y;
};

class Main : public cocos2d::Layer
{
protected:
    std::vector<Card> _cards; // カード情報
    void initCards(); // カード初期化
    Card getCard(); // カードを取得

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Main);
};

#endif // __HELLOWORLD_SCENE_H__
