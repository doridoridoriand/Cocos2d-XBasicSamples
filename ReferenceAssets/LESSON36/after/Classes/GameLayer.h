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
    };
    
    //Zオーダー
    enum ZOrder
    {
        Z_Background = 1,
    };
    
    void createBackground(); //背景の生成
    void createGround(); //地面の生成
    
public:
    static cocos2d::Scene* createScene(); //シーン生成
    virtual bool init(); //初期化
    CREATE_FUNC(GameLayer); //create関数生成マクロ
    virtual void onEnter(); //レイヤー表示時処理
};

#endif /* defined(__SmileyDog__GameLayer__) */