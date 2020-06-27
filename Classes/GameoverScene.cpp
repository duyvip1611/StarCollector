#include "GameoverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameoverScene::createScene(int Score)
{
    return GameoverScene::create(Score);
}

GameoverScene* GameoverScene::create(int Score)
{
	auto obj = new GameoverScene();
	if (obj->init(Score) == false)
	{
		CC_SAFE_DELETE(obj);
		return nullptr;
	}

	obj->autorelease();
	return obj;
}

bool GameoverScene::init(int Score)
{
    // super init first
    if ( !BaseScene::init() )
    {
        return false;
    }

	auto GameoverTitle = Label::createWithTTF("GAME OVER", "fonts/gomarice_no_continue.ttf", visibleSize.width/10);
	GameoverTitle->setAlignment(TextHAlignment::CENTER);
	GameoverTitle->setColor(Color3B::WHITE);
	GameoverTitle->setAnchorPoint(Vec2(0.5f, 0.5f));
	GameoverTitle->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 3);

	auto ScoreSubtitle = Label::createWithTTF(StringUtils::format("Score: %d", Score), "fonts/gomarice_no_continue.ttf", visibleSize.width / 20);
	ScoreSubtitle->setAlignment(TextHAlignment::CENTER);
	ScoreSubtitle->setColor(Color3B::WHITE);
	ScoreSubtitle->setAnchorPoint(Vec2(0.5f, 0.5f));
	ScoreSubtitle->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height/2);

	this->addChild(GameoverTitle, 1);
	this->addChild(ScoreSubtitle, 1);

	auto menuItemReturn = MenuItemFont::create("Click here to exit", CC_CALLBACK_1(GameoverScene::ReturnCallback, this));
	menuItemReturn->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height/3);
	menuItemReturn->setScale(visibleSize.width / 800);

	auto menu = Menu::create(menuItemReturn, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
    return true;
}

void GameoverScene::ReturnCallback(Ref* pSender)
{
	Director::getInstance()->end();
}
