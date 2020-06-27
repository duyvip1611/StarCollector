#include "PlayScene.h"
#include "SimpleAudioEngine.h"
#include "MyInputHandler.h"
#include "Star.h"
#include "GameoverScene.h"

USING_NS_CC;

Scene* PlayScene::createScene()
{
	return PlayScene ::create();
}

bool PlayScene::init()
{
    // super init first
    if ( !BaseScene::init() )
    {
        return false;
    }

	if (!initWithPhysics())
	{
		return false;
	}

	// set scene ID
	this->SceneID = ESceneID::PlayScene;

	// myScale is the scale to fit map to scene size
	auto map = Maps::create(1);
	myScale = MAX(visibleSize.width,visibleSize.height) / map->thisMap->getContentSize().width;

	// set gravity
	this->getPhysicsWorld()->setGravity(Vec2(0, -3.0f * myScale));

	// physic world speed
	this->getPhysicsWorld()->setSpeed(20);

	// enable debug draw
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// init gameplay
	newLevel(currentLevel);

	// add HUD
	_HUD = HUD::create(myScale);
	this->addChild(_HUD, 10);

	// input handler
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = CC_CALLBACK_2(PlayScene::onKeyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(PlayScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	// add event listener for collision
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactPreSolve = CC_CALLBACK_1(PlayScene::onContactPreSolve, this);
	contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(PlayScene::onContactSeparate, this);
	contactListener->onContactPostSolve = CC_CALLBACK_1(PlayScene::onContactPostSolve, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	// tell cocos to call update
	this->scheduleUpdate();

	return true;
}

void PlayScene::update(float deltaTime)
{
	// get character to handle
	auto layer = (Layer*)this->getChildByTag(99);
	_player = (Character*)layer->getChildByTag(EBodyTag::Char);

	// update character
	_player->updateGameObject(deltaTime);

	// update HUD timer
	_HUD->UpdateTime(deltaTime);

	// move camera to follow player
	_camera = Camera::getDefaultCamera();
	auto CamPos = _camera->getPosition();
	if (visibleSize.width >= visibleSize.height)
		CamPos.smooth(Vec2(CamPos.x, MIN(MAX(_player->getPosition().y, visibleSize.height/2), visibleSize.width - visibleSize.height / 2)), 1.0f, 10.0f);
	else
		CamPos.smooth(Vec2(MIN(MAX(_player->getPosition().x, visibleSize.width/2), visibleSize.height - visibleSize.width/2), CamPos.y), 1.0f, 10.0f);

	_camera->setPosition(CamPos);

	// move HUD to follow camera
	_HUD->setPosition(CamPos - visibleSize/2);

	// change level
	if (isFinished)
	{
		if (currentLevel < maxLevel)
			currentLevel++;
		else
			currentLevel = 1;
		newLevel(currentLevel);
		isFinished = false;
	}

	// gameover
	if(_HUD->time == 0)
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameoverScene::createScene(_HUD->score)));
};

void PlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		MyInputHandler::getInstance()->setKeyState(EKeys::UpArrow, true);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		MyInputHandler::getInstance()->setKeyState(EKeys::DownArrow, true);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		MyInputHandler::getInstance()->setKeyState(EKeys::LeftArrow, true);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		MyInputHandler::getInstance()->setKeyState(EKeys::RightArrow, true);
		break;
	default:
		break;
	}
}

void PlayScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		MyInputHandler::getInstance()->setKeyState(EKeys::UpArrow, false);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		MyInputHandler::getInstance()->setKeyState(EKeys::DownArrow, false);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		MyInputHandler::getInstance()->setKeyState(EKeys::LeftArrow, false);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		MyInputHandler::getInstance()->setKeyState(EKeys::RightArrow, false);
		break;
	default:
		break;
	}
}

bool PlayScene::onContactBegin(cocos2d::PhysicsContact & contact)
{
	auto objectA = contact.getShapeA()->getBody();
	auto objectB = contact.getShapeB()->getBody();

	if (objectA->getTag() == EBodyTag::Char && objectB->getTag() == EBodyTag::Stars || objectA->getTag() == EBodyTag::Stars && objectB->getTag() == EBodyTag::Char)
		_HUD->IncreaseScore(10);

	if (objectA->getTag() <= EBodyTag::Stars)
		((BaseSprite*)objectA->getNode())->onCollisionEnter(objectB);

	if (objectB->getTag() <= EBodyTag::Stars)
		((BaseSprite*)objectB->getNode())->onCollisionEnter(objectA);

	if (objectA->getTag() == EBodyTag::Char && objectB->getTag() == EBodyTag::End || objectA->getTag() == EBodyTag::End && objectB->getTag() == EBodyTag::Char)
		isFinished = true;

	return true;
}

bool PlayScene::onContactSeparate(cocos2d::PhysicsContact & contact)
{
	return true;
}

bool PlayScene::onContactPreSolve(cocos2d::PhysicsContact & contact)
{
	auto objectA = contact.getShapeA()->getBody();
	auto objectB = contact.getShapeB()->getBody();

	if (objectA->getTag() == EBodyTag::Removed || objectB->getTag() == EBodyTag::Removed)
		return false;

	return true;
}

bool PlayScene::onContactPostSolve(cocos2d::PhysicsContact & contact)
{

	return true;
}

void PlayScene::newLevel(int MapID)
{
	this->removeChildByTag(99);

	auto gameLayer = Layer::create();
	gameLayer->setTag(99);
	this->addChild(gameLayer);

	// set background
	auto background = Sprite::createWithSpriteFrameName("sky.png");
	background->setPosition(origin.x + MAX(visibleSize.width, visibleSize.height) /2, origin.y + MAX(visibleSize.width, visibleSize.height) / 2);

	// add map
	auto map = Maps::create(MapID);
	map->setPosition(origin);

	// set map scale
	map->setScale(myScale);

	// set background scale to fit map
	background->setScale(MAX(visibleSize.width, visibleSize.height) / background->getContentSize().height);
	// add character
	Character* player = Character::create(myScale);
	player->setPosition(map->startPoint*myScale);
	player->setScale(myScale);
	player->setTag(EBodyTag::Char);

	//add stars
	for (int i = 0; i < map->starCount; i++)
	{
		auto newStar = Star::create();
		newStar->setPosition(map->starPositions[i] * myScale);
		newStar->setScale(myScale);
		gameLayer->addChild(newStar, 4);
	}

	// add child
	gameLayer->addChild(background, 0);
	gameLayer->addChild(map, 1);
	gameLayer->addChild(player, 2);
}
