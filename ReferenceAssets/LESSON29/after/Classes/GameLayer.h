#ifndef __JumpingPenguin__GameLayer__
#define __JumpingPenguin__GameLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

class GameLayer : public cocos2d::Layer
{
protected:
    //タグ
    enum Tag
    {
        T_BG = 1,
    };
    
    //Zオーダー
    enum ZOrder
    {
        Z_BG = 1,
    };

public:
    static cocos2d::Scene* createScene(); //シーン生成
    virtual bool init(); //初期化
    CREATE_FUNC(GameLayer); //create関数生成マクロ
};

#endif /* defined(__JumpingPenguin__GameLayer__) */
