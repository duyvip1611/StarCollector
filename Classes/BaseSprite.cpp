#include "BaseSprite.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool BaseSprite::init()
{
    // super init first
    if ( !Node::init() )
    {
        return false;
    }

    return true;
}

void BaseSprite::createPhysicBody(bool dynamic, bool rotationEnable, float restitution, float friction, float scaleX, float scaleY, float offsetX, float offsetY)
{
	// create material
	auto material = PHYSICSBODY_MATERIAL_DEFAULT;
	material.restitution = 0.0f;
	material.friction = 0.0f;

	// set physic body size

	auto physicBodySize = Size(_sprite->getContentSize().width * scaleX, _sprite->getContentSize().height * scaleY);

	// set offset to get the physic body at the center of sprite
	auto offset = Vec2(offsetX, physicBodySize.height/2 + offsetY);

	// create physic body
	auto physicBody = PhysicsBody::createBox(physicBodySize, material, offset);

	physicBody->setDynamic(dynamic);
	physicBody->setRotationEnable(rotationEnable);
	physicBody->setMass(100.0f);
	physicBody->setTag(tag);

	// add the physic body to object
	this->addComponent(physicBody);


	// set bitmask to collide with everything
	this->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
}

cocos2d::Vector<cocos2d::SpriteFrame*> BaseSprite::getAnimation(const char * format, int startIndex, int amount)
{
	auto spritecache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames;

	char str[50];
	for (int i = startIndex; i < startIndex + amount; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	return animFrames;

	return cocos2d::Vector<cocos2d::SpriteFrame*>();
}

void BaseSprite::setAnimation(cocos2d::Vector<cocos2d::SpriteFrame*> frames, bool repeat)
{
	_sprite->stopAllActions();

	if (repeat)
		_sprite->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frames, 1.0f/8))));
	else
		_sprite->runAction(Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 8)));
}
