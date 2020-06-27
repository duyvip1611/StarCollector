#ifndef __MYINPUTHANDLER_H__
#define __MYINPUTHANDLER_H__

#include "cocos2d.h"
enum EKeys
{
	UpArrow,
	DownArrow,
	LeftArrow,
	RightArrow
};

class MyInputHandler : public cocos2d::Node
{
public:
	static MyInputHandler* getInstance();

	void setKeyState(EKeys key, bool isPressed);
	bool getKeyState(EKeys key);

private:
	void MyInputHandle();
	static MyInputHandler* m_instance;

	bool keyStates[4];
};

#endif // __MYINPUTHANDLER_H__
