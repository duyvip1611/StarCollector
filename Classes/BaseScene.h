#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "cocos2d.h"

enum ESceneID
{
	PlayScene
};

class BaseScene : public cocos2d::Scene
{
public:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	int SceneID;

    static cocos2d::Scene* createScene();
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(BaseScene);
};

#endif // __BASE_SCENE_H__
