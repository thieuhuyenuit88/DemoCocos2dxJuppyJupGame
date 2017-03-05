#pragma once
#include "cocos2d.h"
#include "Beam.h"

USING_NS_CC;

class BarrierBeam: public MyObject
{
private:
	Point speedScroll;
	Vector<Beam*> listBeams;

	int barrierDirect;
	int numBeams;
	int typeBeam;
public:
	BarrierBeam(void);
	virtual ~BarrierBeam(void);

	void SetSpeed(Point speed){
		speedScroll = speed;
	}

	Point GetSpeed(){return speedScroll;}

	const Vector<Beam*> & getListBeams(){return listBeams;}

	bool Init(cocos2d::Layer *layer, Point pos, float speed, int direct);

	void Update(float deltaTime);

	void Release();
};

