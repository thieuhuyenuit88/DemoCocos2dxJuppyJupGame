#include "BarrierBeam.h"
#include "CRandom.h"
#include "Constants.h"

BarrierBeam::BarrierBeam(void)
{
}

BarrierBeam::~BarrierBeam(void)
{
	
}

bool BarrierBeam::Init(cocos2d::Layer *layer, Point pos, float speed, int direct){
	this->setPosition(pos);

	numBeams = CRandom::RandomBetweenInt(kNumBeamsMin, kNumBeamMax);
	listBeams = Vector<Beam*>(numBeams);

	typeBeam = CRandom::RandomBetweenInt(kTypeBeam1, kTypeBeam4);

	barrierDirect = direct;
	speedScroll = Point(speed * direct, 0);

	for (int i = 0; i < numBeams; i++)
	{
		Beam* beam = new Beam(typeBeam, speedScroll);
		listBeams.pushBack(beam);
		this->addChild(beam);
		beam->release();
	}
	
	listBeams.at(0)->setPositionX(0);

	for (int i = 1; i < numBeams; i++)
	{
		float dis = CRandom::RandomBetweenIntRemoveBias(kDistanceBeamMin, kDistanceBeamMax) * SIZECELL;

		listBeams.at(i)->setPositionX(listBeams.at(i - 1)->getPositionX() + listBeams.at(i - 1)->getCollisionBox().size.width + dis);
	}

	layer->addChild(this, kZIndexBeam);

	return true;
}

void BarrierBeam::Update(float deltaTime){
	const Vector<Beam*> copyBeams = getListBeams();
	for (auto beam: copyBeams)
	{
		beam->Update(deltaTime);

		if (barrierDirect == kDirectLeft)
		{
			if (beam->getPositionX() + beam->getCollisionBox().size.width < 0)
			{
				listBeams.eraseObject(beam);

				float dis = CRandom::RandomBetweenIntRemoveBias(kDistanceBeamMin, kDistanceBeamMax) * SIZECELL;
				beam->setPositionX(listBeams.back()->getPositionX() + listBeams.back()->getCollisionBox().size.width + dis);
				listBeams.pushBack(beam);
			}
		}else if (barrierDirect == kDirectRight)
		{
			if (beam->getPositionX() - 40 > GETWINSIZE_WIDTH)
			{
				listBeams.eraseObject(beam);

				float dis = CRandom::RandomBetweenIntRemoveBias(kDistanceBeamMin, kDistanceBeamMax) * SIZECELL;
				beam->setPositionX(listBeams.front()->getPositionX() - beam->getCollisionBox().size.width - dis);
				listBeams.insert(0, beam);
			}
		}
	}
}

void BarrierBeam::Release(){
	for (auto beam: listBeams)
	{
		beam->removeFromParent();
	}
	listBeams.clear();
	this->removeAllChildren();
	this->removeFromParent();
}

