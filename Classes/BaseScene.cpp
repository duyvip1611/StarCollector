#include "BaseScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* BaseScene::createScene()
{
    return BaseScene::create();
}

bool BaseScene::init()
{
    // super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    return true;
}
