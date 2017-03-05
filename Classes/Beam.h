#pragma once
#include "MyObject.h"

USING_NS_CC;

class Beam: public MyObject
{
private:
	Vector<Sprite*> listSpriteBeam;
	int numMemBeam;
	int typeBeam;

	float speedBeam;

	void InitWithType(int type);
public:
	Beam(void);
	Beam(int type, Point velloc);
	virtual ~Beam(void);

	bool Init(cocos2d::Layer *layer);

	void UpdateAnimation(float deltaTime);
	void UpdateMove(float deltaTime);
	void Update(float deltaTime);
	void UpdateStatus(float deltaTime);

	void Release();	

	Rect getCollisionBox();
};

