#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    //シーンを生成する
    auto scene = Scene::create();
    
    //HelloWorldクラスのレイヤーを生成する
    auto layer = HelloWorld::create();

    //シーンに対してレイヤーを追加する
    scene->addChild(layer);

    //シーンを返す
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    return true;
}
