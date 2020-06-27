#include "Star.h"
#include "SimpleAudioEngine.h"
#include "MyInputHandler.h"

USING_NS_CC;

Star* Star::create()
{
	auto obj = new Star();
	if (obj->init() == false)
	{
		CC_SAFE_DELETE(obj);
		return nullptr;
	}

	obj->autorelease();
	return obj;
}

bool Star::init()
{
    // super init first
    if ( !BaseSprite::init() )
    {
        return false;
    }

	// set tag
	tag = EBodyTag::Stars;

	// add sprite
	auto idleFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("star.png");
	_sprite = Sprite::createWithSpriteFrame(idleFrame);

	// create physic body
	createPhysicBody(false, false, 0, 0, 0.8f, 0.9f);

	this->addChild(_sprite);
	
    return true;
}

void Star::onCollisionEnter(cocos2d::PhysicsBody* other)
{
	if (other->getTag() == EBodyTag::Char)
	{
		this->setVisible(false);
		this->getPhysicsBody()->setTag(EBodyTag::Removed);
	}
}

