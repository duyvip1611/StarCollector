#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "BaseScene.h"
#include "Character.h"
#include "Maps.h"
#include "HUD.h"

class PlayScene : public BaseScene
{
public:

	//cocos2d::Layer* gameLayer;
	float myScale;
	Character* _player;
	HUD* _HUD;
	bool isFinished = false;
	int currentLevel = 1;
	int maxLevel = 5;

	cocos2d::Camera* _camera;

    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void update(float deltaTime) override;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	virtual bool onContactBegin(cocos2d::PhysicsContact& contact);
	virtual bool onContactSeparate(cocos2d::PhysicsContact& contact);
	virtual bool onContactPreSolve(cocos2d::PhysicsContact& contact);
	virtual bool onContactPostSolve(cocos2d::PhysicsContact& contact);

	void newLevel(int MapID);

    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);
};

#endif // __PLAY_SCENE_H__
