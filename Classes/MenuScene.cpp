#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "PlayScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

bool MenuScene::init()
{
    // super init first
    if ( !BaseScene::init() )
    {
        return false;
    }

	auto MenuTitle = Label::createWithTTF("GAME START", "fonts/gomarice_no_continue.ttf", visibleSize.width / 10);
	MenuTitle->setAlignment(TextHAlignment::CENTER);
	MenuTitle->setColor(Color3B::WHITE);
	MenuTitle->setAnchorPoint(Vec2(0.5f, 0.5f));
	MenuTitle->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 3);

	auto menuItemPlay = MenuItemFont::create("Click here to play", CC_CALLBACK_1(MenuScene::menuPlayCallback, this));
	menuItemPlay->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3);
	menuItemPlay->setScale(visibleSize.width / 800);

	auto menu = Menu::create(menuItemPlay, nullptr);
	menu->setPosition(Vec2::ZERO);

	this->addChild(MenuTitle);
	this->addChild(menu, 1);

    return true;
}

void MenuScene::menuPlayCallback(Ref* pSender)
{
	Director::getInstance()->pushScene(TransitionFade::create(1.0f, PlayScene::createScene()));
}
