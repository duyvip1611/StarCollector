#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "BaseScene.h"

class GameoverScene : public BaseScene
{
public:
    static cocos2d::Scene* createScene(int Score);
	static GameoverScene* create(int Score);
    virtual bool init(int Score);

	// a selector callback
	void ReturnCallback(cocos2d::Ref* pSender);
};

#endif // __GAMEOVER_SCENE_H__
