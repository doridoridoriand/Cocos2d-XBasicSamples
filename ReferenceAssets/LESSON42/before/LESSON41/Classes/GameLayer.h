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
        T_Ball,
        T_Gum1,
        T_Gum2,
        T_Block,
    };
    
    //Zオーダー
    enum ZOrder
    {
        Z_Background = 1,
        Z_Enemy,
        Z_Launcher2,
        Z_Gum2,
        Z_Ball,
        Z_Gum1,
        Z_Launcher1,
        Z_Block,
        Z_Fog,
        Z_Star,
    };

    //種類
    enum class BlockType
    {
        Block1,
        Block2,
        Roof,
        Stone
    };
    
    void createBackground(); //背景の生成
    void createGround(); //地面の生成
    void createEnemy(cocos2d::Point position); //敵の生成
    void createBall(); //ボールの生成
    cocos2d::Point calculatedPosition(cocos2d::Point touchPosition); //ボールの位置を算出
    void applyingForceToBall(cocos2d::Node* ball); //ボールに飛ぶ力を加える
    void createBlockAndEnemy(); //敵とブロックの生成
    void createBlock(BlockType type, cocos2d::Point position, float angle); //ブロックの生成
    void contactedBall(); //ボールの衝突
    void removingEnemy(cocos2d::Node* enemy); //敵の消滅
    
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

    //衝突イベント
    bool onContactBegin(cocos2d::PhysicsContact& contact);
};

#endif /* defined(__SmileyDog__GameLayer__) */