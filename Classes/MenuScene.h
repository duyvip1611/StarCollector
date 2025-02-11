#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "BaseScene.h"

class MenuScene : public BaseScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

	// a selector callback
	void menuPlayCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif // __MENU_SCENE_H__
