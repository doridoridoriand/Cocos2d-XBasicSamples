#include "GameLayer.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

#define WINSIZE Director::getInstance()->getWinSize() //画面サイズ
#define INIT_BLOCK_TIME 3.0 //ブロックが最初に出現する時間[s]
#define INTERVAL_BLOCK_TIME 1.5 //ブロックが出現するタイミング[s]
#define MOVING_TIME 3 //ブロックが消えるまでの時間

//背景のJSON
#define BACKGROUND_JSON "JumpingPenguinUI/Background.ExportJson"

//ポップアップのJSON
#define POPUP_JSON "JumpingPenguinUI/Popup.ExportJson"

//ブロックのJSON
#define BLOCK_JSON "JumpingPenguinUI/Block.ExportJson"

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

    //タップイベントの取得
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // Backgroundレイヤーの取得
    auto widget = GUIReader::getInstance()->widgetFromJsonFile(BACKGROUND_JSON);
    auto layout = dynamic_cast<Layout*>(widget);
    layout->setPosition(Point((WINSIZE - layout->getContentSize()) / 2));
    addChild(layout, Z_BG, T_BG);
    return true;
}

//レイヤー表示時処理
void GameLayer::onEnter()
{
    Layer::onEnter();
    
    //Popupレイヤーの表示
    auto widget = GUIReader::getInstance()->widgetFromJsonFile(POPUP_JSON);
    auto popup = dynamic_cast<Layout*>(widget);
    popup->setPosition(Point((WINSIZE - popup->getContentSize()) / 2));
    addChild(popup, Z_GameStartLayer);
    
    //スタート画面フレームイン
    ActionManagerEx::getInstance()->playActionByName("Popup.ExportJson", "GameStart_In");
    _state = State::GameStart;
}

//update関数（毎フレーム処理）
void GameLayer::update(float dt)
{
    //ゲーム時間の積算
    _totalTime += dt;
    
    //次のブロックの表示
    if (_totalTime > _nextBlockTime)
    {
        //Blockレイヤーの取得
        auto widget = GUIReader::getInstance()->widgetFromJsonFile(BLOCK_JSON);
        auto blockLayout = dynamic_cast<Layout*>(widget);
        blockLayout->setAnchorPoint(Point(0, 0.5));
        blockLayout->setPosition(Point(WINSIZE.width, WINSIZE.height * 0.5));
        addChild(blockLayout, Z_Block, T_Block);
        
        //ブロックを移動させる
        auto move = MoveBy::create(MOVING_TIME, Point((blockLayout->getContentSize().width + WINSIZE.width) * -1, 0));
        auto remove = RemoveSelf::create();
        auto seq = Sequence::create(move, remove, nullptr);
        blockLayout->runAction(seq);
        
        //次のブロックの時間を設定
        _nextBlockTime += INTERVAL_BLOCK_TIME;
    }
}

void GameLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
    if (_state == State::GameStart)
    {
        // スタート画面フレームアウト
        ActionManagerEx::getInstance()->playActionByName("Popup.ExportJson", "GameStart_Out");
        _state = State::Gaming;
        //時間の初期化
        _totalTime = 0;
        _nextBlockTime = INIT_BLOCK_TIME;
        
        //update関数を毎フレーム呼び出す
        scheduleUpdate();
    }
}
