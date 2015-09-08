#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    //HelloWorldクラスのシーンを作成する
    static cocos2d::Scene* createScene();

    //初期化処理を行う
    virtual bool init();  
    
    //create関数作成マクロ
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
