#include "SimpleAudioEngine.h"
#include "MyInputHandler.h"

USING_NS_CC;
MyInputHandler* MyInputHandler::m_instance = NULL;

MyInputHandler* MyInputHandler::getInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new MyInputHandler();
	}

	return m_instance;
}

void MyInputHandler::setKeyState(EKeys key, bool isPressed)
{
	keyStates[key] = isPressed;
}

bool MyInputHandler::getKeyState(EKeys key)
{
	return keyStates[key];
}

void MyInputHandler::MyInputHandle()
{
	for (int i = 0; i < 4; i++)
		keyStates[i] = false;
}
