#include "Character.h"
#include "SimpleAudioEngine.h"
#include "MyInputHandler.h"

USING_NS_CC;

Character* Character::create(float scale)
{
	auto obj = new Character();
	if (obj->init(scale) == false)
	{
		CC_SAFE_DELETE(obj);
		return nullptr;
	}

	obj->autorelease();
	return obj;
}

bool Character::init(float scale)
{
    // super init first
    if ( !BaseSprite::init() )
    {
        return false;
    }

	// scale run and jump speed to match screen size
	gameScale = scale;
	speed *= gameScale;
	jumpHeight *= gameScale;

	// set tag
	tag = EBodyTag::Char;

	// get animations
	runLeft = getAnimation("dude/dude-%d.png", 0, 4);
	runRight = getAnimation("dude/dude-%d.png", 5, 4);

	// add sprite
	idleFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dude/dude-4.png");
	_sprite = Sprite::createWithSpriteFrame(idleFrame);
	// create physic body
	createPhysicBody(true, false, 0, 0, 0.4f, 0.8f);
	this->addChild(_sprite);
	
    return true;
}

void Character::updateGameObject(float deltaTime)
{

	// change character's movement following input
	auto inputHandler = MyInputHandler::getInstance();

	if (inputHandler->getKeyState(EKeys::UpArrow))
	{
		if (!isJumping)
		{
			this->getPhysicsBody()->applyForce(Vec2(0, 1) * jumpHeight);
			isJumping = true;
			jumpDelay = 0.1f;
		}
	}
	if (inputHandler->getKeyState(EKeys::LeftArrow)&&!inputHandler->getKeyState(EKeys::RightArrow))
	{
		this->setPositionX(this->getPositionX() - speed * deltaTime);
		if (!isRunningLeft)
		{
			setAnimation(runLeft, true);
			isRunningLeft = true;
			isRunningRight = false;
		}
	}
	if (inputHandler->getKeyState(EKeys::RightArrow) && !inputHandler->getKeyState(EKeys::LeftArrow))
	{
		this->setPositionX(this->getPositionX() + speed * deltaTime);
		if (!isRunningRight)
		{
			setAnimation(runRight, true);
			isRunningRight = true;
			isRunningLeft = false;
		}
	}
	if (inputHandler->getKeyState(EKeys::LeftArrow) && inputHandler->getKeyState(EKeys::RightArrow)|| !inputHandler->getKeyState(EKeys::LeftArrow) && !inputHandler->getKeyState(EKeys::RightArrow))
	{
		_sprite->stopAllActions();
		_sprite->setSpriteFrame(idleFrame);
		isRunningLeft = false;
		isRunningRight = false;
	}
	jumpDelay -= deltaTime;

	if (this->getPhysicsBody()->getVelocity().y == 0 && jumpDelay < 0)
		isJumping = false;
}

void Character::onCollisionEnter(cocos2d::PhysicsBody* other)
{
	//int otherTag = other->getTag();
	//if (otherTag == EBodyTag::Platform)
	//	isJumping = false;
}
