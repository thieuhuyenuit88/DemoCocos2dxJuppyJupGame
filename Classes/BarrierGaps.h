#pragma once
#include "cocos2d.h"
#include "MyObject.h"

USING_NS_CC;

class BarrierGaps: public MyObject
{
private:
	float timeMove;
	float timeDelay;

	Sprite* gapLeft;
	Sprite* gapRight;
	Vector<Sprite*> listGaps;
public:
	BarrierGaps(void);
	virtual ~BarrierGaps(void);

	float getTimeMove(){return timeMove;}
	float getTimeDelay(){return timeDelay;}

	void setTimeMove(float _timeMove){
		timeMove = _timeMove;
	}

	void setTimeDelay(float _timeDelay){
		timeDelay = _timeDelay;
	}

	const Vector<Sprite*> & getListGaps(){return listGaps;}

	bool Init(cocos2d::Layer *layer, Point pos, float _timeMove, float _timeDelay);

	void Update(float deltaTime);

	void Release();
};

