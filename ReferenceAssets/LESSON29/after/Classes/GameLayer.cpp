#include "GameLayer.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

#define WINSIZE Director::getInstance()->getWinSize() //画面サイズ

//背景のJSON
#define BACKGROUND_JSON "JumpingPenguinUI/Background.ExportJson"

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
    
    // Backgroundレイヤーの取得
    auto widget = GUIReader::getInstance()->widgetFromJsonFile(BACKGROUND_JSON);
    auto layout = dynamic_cast<Layout*>(widget);
    layout->setPosition(Point((WINSIZE - layout->getContentSize()) / 2));
    addChild(layout, Z_BG, T_BG);
    return true;
}
