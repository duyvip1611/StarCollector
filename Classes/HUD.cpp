#include "HUD.h"

USING_NS_CC;

HUD* HUD::create(float scale)
{
	auto chr = new HUD();
	if (chr->init(scale) == false)
	{
		CC_SAFE_DELETE(chr);
		return nullptr;
	}

	chr->autorelease();
	return chr;
}

bool HUD::init(float scale)
{
	if (!LayerColor::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	// score
	score = 0;

	_score = Label::createWithTTF("Score: 0", "fonts/gomarice_no_continue.ttf", 24 * scale);
	_score->setAlignment(TextHAlignment::LEFT);
	_score->setColor(Color3B::BLACK);
	_score->setAnchorPoint(Vec2(0, 1));

	// time
	time = START_TIME;

	_time = Label::createWithTTF("Time: " + std::to_string(START_TIME), "fonts/gomarice_no_continue.ttf", 24 * scale);
	_time->setAlignment(TextHAlignment::LEFT);
	_time->setColor(Color3B::WHITE);
	_time->setAnchorPoint(Vec2(0, 1));
	_time->setPositionY(-20 * scale);

	auto Group = Node::create();
	Group->addChild(_score, 0);
	Group->addChild(_time, 0);

	Group->setPosition(Vec2(origin.x + 10 * scale, origin.y + visibleSize.height - 5 * scale));

	this->addChild(Group, 0);

	return true;
}

void HUD::IncreaseScore(int ammount)
{
	score += ammount;
	_score->setString(StringUtils::format("Score: %d", score));
}

void HUD::UpdateTime(float deltaTime)
{
	time -= deltaTime;
	if (time < 0)
		time = 0;
	_time->setString(StringUtils::format("Time: %d", (int)floor(time)));
}
