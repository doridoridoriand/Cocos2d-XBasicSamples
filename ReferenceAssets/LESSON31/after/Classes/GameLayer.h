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
        T_Block,
    };
    
    //Zオーダー
    enum ZOrder
    {
        Z_BG = 1,
        Z_Block,
        Z_GameStartLayer,
        Z_GameOverLayer,
    };

    //ゲームの状態
    enum class State
    {
        GameStart,
        Gaming,
        GameOver,
    };
    
    State _state; //ゲームの状態
    float _totalTime; //ゲーム時間
    float _nextBlockTime; //次のブロックが出るまでの時間
    
public:
    static cocos2d::Scene* createScene(); //シーン生成
    virtual bool init(); //初期化
    CREATE_FUNC(GameLayer); //create関数生成マクロ
    virtual void onEnter(); //レイヤー表示時処理
    virtual void update(float dt); //update関数（毎フレーム処理）

    //マルチタップイベント
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
};

#endif /* defined(__JumpingPenguin__GameLayer__) */
