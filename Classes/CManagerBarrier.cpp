#include "CManagerBarrier.h"
#include "Constants.h"
#include "CRandom.h"
#include "BarrierBeam.h"
#include "BarrierGaps.h"
#include "BarrierLaser.h"
#include "CustomFollow.h"

CManagerBarrier::CManagerBarrier(void):Singleton<CManagerBarrier>()
{

}


CManagerBarrier::~CManagerBarrier(void)
{
}

void CManagerBarrier::InitListBarrier(Layer *layer){
	oldPosY = 0;
	isFirst = true;

	int direct = 0;
	int typeBarrier = 0;
	containerLayer = layer;
	listBarrier = Vector<MyObject*>(7);

	for (int i = 0; i < 7; i++)
	{
		typeBarrier = CRandom::RandomBetweenIntRemoveBias(kTagBarrierBeam, kTagBarrierLaser);

		switch (typeBarrier)
		{
		case kTagBarrierBeam:
			BarrierBeam* barrierBeam;
			barrierBeam = new BarrierBeam;
			direct = CRandom::RandomBetweenInt(0, 1) ? kDirectLeft : kDirectRight;
			barrierBeam->Init(layer, Vec2(0, kInitStartPosBarrier), kSpeedBarrierBeam, direct);
			barrierBeam->setTag(kTagBarrierBeam);
			listBarrier.pushBack(barrierBeam);
			barrierBeam->release();
			break;
		case kTagBarrierGaps:
			{
				BarrierGaps* barrierGaps = new BarrierGaps;
				barrierGaps->Init(layer, Vec2(0, kInitStartPosBarrier), kTimeMoveGaps, kTimeDelayGaps);
				barrierGaps->setTag(kTagBarrierGaps);
				listBarrier.pushBack(barrierGaps);
				barrierGaps->release();
				break;
			}
		case kTagBarrierLaser:
			{
				BarrierLaser* barrierLaser = new BarrierLaser;
				direct = CRandom::RandomBetweenInt(0, 1) ? kDirectLeft : kDirectRight;
				barrierLaser->Init(layer, Vec2(0, kInitStartPosBarrier), kSpeedLaser, direct);
				barrierLaser->setTag(kTagBarrierLaser);
				listBarrier.pushBack(barrierLaser);
				barrierLaser->release();
				break;
			}
		}
	}
	
	for (int i = 1; i < 7; i++)
	{
		float dis = CRandom::RandomBetweenIntRemoveBias(kDistanceBarrierMin, kDistanceBarrierMax);

		listBarrier.at(i)->setPositionY(listBarrier.at(i - 1)->getPositionY() + listBarrier.at(i - 1)->getFullBoundingBox().size.height/2 + dis);
	}
}

void CManagerBarrier::AddBarrier(){
	int direct = 0;
	int typeBarrier = 0;
	float posY = 0;

	typeBarrier = CRandom::RandomBetweenIntRemoveBias(kTagBarrierBeam, kTagBarrierLaser);

	float dis = CRandom::RandomBetweenIntRemoveBias(kDistanceBarrierMin, kDistanceBarrierMax);

	posY = listBarrier.back()->getPositionY() + listBarrier.back()->getFullBoundingBox().size.height + dis;

	switch (typeBarrier)
	{
	case kTagBarrierBeam:
		BarrierBeam* barrierBeam;
		barrierBeam = new BarrierBeam;
		direct = CRandom::RandomBetweenInt(0, 1) ? kDirectLeft : kDirectRight;
		barrierBeam->Init(containerLayer, Vec2(0, posY), kSpeedBarrierBeam, direct);
		barrierBeam->setTag(kTagBarrierBeam);
		listBarrier.pushBack(barrierBeam);
		barrierBeam->release();
		break;
	case kTagBarrierGaps:
		{
			BarrierGaps* barrierGaps = new BarrierGaps;
			barrierGaps->Init(containerLayer, Vec2(0, posY), kTimeMoveGaps, kTimeDelayGaps);
			barrierGaps->setTag(kTagBarrierGaps);
			listBarrier.pushBack(barrierGaps);
			barrierGaps->release();
			break;
		}
	case kTagBarrierLaser:
		{
			BarrierLaser* barrierLaser = new BarrierLaser;
			direct = CRandom::RandomBetweenInt(0, 1) ? kDirectLeft : kDirectRight;
			barrierLaser->Init(containerLayer, Vec2(0, posY), kSpeedLaser, direct);
			barrierLaser->setTag(kTagBarrierLaser);
			listBarrier.pushBack(barrierLaser);
			barrierLaser->release();
			break;
		}
	}
}

void CManagerBarrier::UpdateBarrier(CustomFollow* CFollow){
	const Vector<MyObject*> copyBarriers = getCopyListBarrier();
	for (auto barrier: copyBarriers)
	{
		if (barrier->getPositionY() + barrier->getFullBoundingBox().size.height <= CFollow->GetCurRectView().origin.y)
		{
			listBarrier.eraseObject(barrier);
			barrier->Release();
			AddBarrier();
			break;
		}
	}
}