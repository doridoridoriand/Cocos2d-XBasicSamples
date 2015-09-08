#ifndef __SmileyDog__GameLayer__
#define __SmileyDog__GameLayer__

#include "cocos2d.h"

class GameLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(); //シーン生成
    virtual bool init(); //初期化
    CREATE_FUNC(GameLayer); //create関数生成マクロ
};

#endif /* defined(__SmileyDog__GameLayer__) */