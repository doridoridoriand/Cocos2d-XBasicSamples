#ifndef __SmileyDog__GameLayer__
#define __SmileyDog__GameLayer__

#include "cocos2d.h"

class GameLayer : public cocos2d::Layer
{
protected:
    //タグ
    enum Tag
    {
        T_Background = 1,
        T_Enemy,
    };
    
    //Zオーダー
    enum ZOrder
    {
        Z_Background = 1,
        Z_Enemy,
    };
    
    void createBackground(); //背景の生成
    void createGround(); //地面の生成
    void createEnemy(cocos2d::Point position); //敵の生成
    
public:
    static cocos2d::Scene* createScene(); //シーン生成
    virtual bool init(); //初期化
    CREATE_FUNC(GameLayer); //create関数生成マクロ
    virtual void onEnter(); //レイヤー表示時処理
    
    //シングルタップイベント
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCanceled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif /* defined(__SmileyDog__GameLayer__) */