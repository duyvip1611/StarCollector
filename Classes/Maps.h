#ifndef __MAPS_H__
#define __MAPS_H__

#include "cocos2d.h"
#include "BaseSprite.h"

class Maps : public BaseSprite
{
public:
	static Maps* create(int ID);
	virtual bool init(int ID);
	virtual void createPhysicBody(bool dynamic = true, bool rotationEnable = true);
	virtual void updateGameObject(float deltaTime, int direction = 0) {}

	cocos2d::TMXTiledMap* thisMap;
	cocos2d::Vec2 startPoint;
	cocos2d::Vec2 starPositions[50];
	int starCount;

	virtual void loadPhysic(const char* layerName, int tagName);
	cocos2d::Vec2* getObjectsPositions(char* layerName);

	virtual void onCollisionEnter(Maps* other) {}
	virtual void onCollisionExit(Maps* other) {}

};

#endif // __MAPS_H__
