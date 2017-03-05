#pragma once
#include "MyObject.h"

USING_NS_CC;

class JuppyMan: public MyObject
{
private:
	Sprite* spriteJuppy;
	Sprite* copters;

public:
	JuppyMan(void);
	JuppyMan(cocos2d::Layer *layer);
	virtual ~JuppyMan(void);

	bool Init(cocos2d::Layer *layer);

	void UpdateAnimation(float deltaTime);
	void UpdateMove(float deltaTime);
	void Update(float deltaTime);
	void UpdateStatus(float deltaTime);

	void Release();

	void HitJup();

	Rect getCollisionBox();
};

