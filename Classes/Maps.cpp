#include "Maps.h"
#include "SimpleAudioEngine.h"
#include "Star.h"

USING_NS_CC;

Maps *Maps::create(int ID)
{
	auto obj = new Maps();
	if (obj->init(ID) == false)
	{
		CC_SAFE_DELETE(obj);
		return nullptr;
	}

	obj->autorelease();
	return obj;
}

bool Maps::init(int ID)
{
    // super init first
    if ( !BaseSprite::init() )
    {
        return false;
    }
	// add tiledmap
	std::string str = "Map" + std::to_string(ID) + ".tmx";
	thisMap = TMXTiledMap::create(str);
	// load physic bodies
	this->loadPhysic("platformBody", EBodyTag::Platform);
	this->loadPhysic("end", EBodyTag::End);

	// load positions
	startPoint = getObjectsPositions("start")[0];

	starCount = static_cast<int>(thisMap->getObjectGroup("star")->getObjects().size());

	for (int i = 0; i < starCount; i++)
		starPositions[i] = getObjectsPositions("star")[i];

	this->addChild(thisMap, 0);

    return true;
}

void Maps::createPhysicBody(bool dynamic, bool rotationEnable)
{
	auto material = PHYSICSBODY_MATERIAL_DEFAULT;
	auto offset = -1.0f * Vec2(this->getContentSize().width / 2.0f, this->getContentSize().height / 2.0f);
	auto physicBody = PhysicsBody::createBox(this->getContentSize(), material, offset);
	physicBody->setDynamic(dynamic);
	physicBody->setRotationEnable(rotationEnable);

	//add the physic body to object
	this->addComponent(physicBody);
}

void Maps::loadPhysic(const char* layerName, int tagName)
{
	//ground physic
	auto physicNode = Node::create();
	this->addChild(physicNode);
	auto group = thisMap->getObjectGroup(layerName);
	auto& objects = group->getObjects();
	for (auto& obj : objects)
	{
		ValueMap& dict = obj.asValueMap();

		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		float width = dict["width"].asFloat();
		float height = dict["height"].asFloat();
		if (physicNode->getPhysicsBody() == nullptr)
		{
			auto body = PhysicsBody::create();
			body->setDynamic(false);
			body->setRotationEnable(false);

			physicNode->addComponent(body);
		}
		auto body = physicNode->getPhysicsBody();
		auto offset = Vec2(x + width / 2.0f, y + height / 2.0f);
		auto material = PHYSICSBODY_MATERIAL_DEFAULT;
		material.friction = 0.0f;
		auto sharp = body->addShape(PhysicsShapeBox::create(Size(width, height), material, offset));

		//allow physic world detect contact
		body->setContactTestBitmask(0xFFFFFFFF);
		body->setTag(tagName);
	}
}

cocos2d::Vec2* Maps::getObjectsPositions(char* layerName)
{
	auto objects = thisMap->getObjectGroup(layerName)->getObjects();
	cocos2d::Vec2 positions[50];
	int i = 0;
	for (auto& ob : objects)
	{
		auto obj = ob.asValueMap();
		positions[i] = Vec2(obj["x"].asFloat() + obj["width"].asFloat() / 2, obj["y"].asFloat());
		i++;
	}
	return positions;
}
