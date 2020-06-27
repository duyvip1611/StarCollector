#ifndef __STAR_H__
#define __STAR_H__

#include "cocos2d.h"
#include "BaseSprite.h"

class Star : public BaseSprite
{
public:

	static Star* create();
	virtual bool init();

	virtual void onCollisionEnter(cocos2d::PhysicsBody* other) override;
};

#endif // __STAR_H__
