#ifndef __BASE_SPRITE_H__
#define __BASE_SPRITE_H__

#include "cocos2d.h"

enum EBodyTag
{
	Char,
	Stars,
	Removed,
	Platform,
	End
};

enum EDirection
{
	Up,
	Down,
	Left,
	Right
};

class BaseSprite : public cocos2d::Node
{
public:
	int tag;

	virtual bool init();
	virtual void createPhysicBody(bool dynamic = true, bool rotationEnable = true, float restitution = 0.5f, float friction = 0.5f, float scaleX = 1.0f, float scaleY = 1.0f, float offsetX = 0, float offsetY = 0);
	virtual void updateGameObject(float deltaTime) {}

	virtual void onCollisionEnter(cocos2d::PhysicsBody* other) {}
	virtual void onCollisionExit(cocos2d::PhysicsBody* other) {}

	static cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int startIndex, int amount);

	void setAnimation(cocos2d::Vector<cocos2d::SpriteFrame*> frames, bool repeat);
protected:
	cocos2d::Sprite* _sprite;
};

#endif // __BASE_SPRITE_H__
