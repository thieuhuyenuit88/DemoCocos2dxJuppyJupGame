#pragma once
#include "cocos2d.h"
#include "MyObject.h"

USING_NS_CC;

class BarrierLaser: public MyObject
{
private:
	Sprite* gun;
	Sprite* rootLaser;
	Sprite* laserRay;
	ProgressTimer* timer;

	Rect collistionBoxLaser;
	int laserDirect;
	int typeLaser;
	float speedLaser;
public:
	BarrierLaser(void);
	virtual ~BarrierLaser(void);

	bool Init(cocos2d::Layer *layer, Point pos, float speed, int direct);

	void Update(float deltaTime);

	void Release();

	Rect getCollisionBoxLaser();

	void ReadyFightingLaser();
	void StartFightingLaser();
	void FightingLaserDone();
	void EndFightingAndLoop();
};

