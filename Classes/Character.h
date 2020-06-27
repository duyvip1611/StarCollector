#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "BaseSprite.h"

class Character : public BaseSprite
{
public:
	float speed = 150.0f;
	float jumpHeight = 7000.0f;
	float gameScale;
	int Movement = 0;
	bool isJumping = false;
	bool isRunningLeft = false;
	bool isRunningRight = false;
	float jumpDelay = 0.1f;

	cocos2d::Vector<cocos2d::SpriteFrame*> runLeft;
	cocos2d::Vector<cocos2d::SpriteFrame*> runRight;
	cocos2d::SpriteFrame* idleFrame;

	static Character* create(float scale);
	virtual bool init(float scale);

	virtual void updateGameObject(float deltaTime) override;
	virtual void onCollisionEnter(cocos2d::PhysicsBody* other) override;
};

#endif // __CHARACTER_H__
