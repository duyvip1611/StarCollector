
#ifndef  __HUD_h__
#define  __HUD_h__

#include "cocos2d.h"

class HUD : public cocos2d::LayerColor
{
public:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	int score;
	cocos2d::Label* _score;
	float time;
	const float START_TIME = 60.0f;
	cocos2d::Label* _time;

	static HUD* create(float scale);
	virtual bool init(float scale);

	void IncreaseScore(int ammount);

	void UpdateTime(float deltaTime);
};

#endif // __HUD_h__