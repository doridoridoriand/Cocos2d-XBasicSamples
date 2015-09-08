#include "GameLayer.h"

USING_NS_CC;

//シーン生成
Scene* GameLayer::createScene()
{
    auto scene = Scene::create(); //シーンを生成する
    auto layer = GameLayer::create(); //GameLayerクラスのレイヤーを生成する
    scene->addChild(layer); //シーンに対してレイヤーを追加する
    
    return scene; //シーンを返す
}

//初期化
bool GameLayer::init()
{
    if (!Layer::init())
        return false;
    
    return true;
}
