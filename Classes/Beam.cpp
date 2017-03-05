#include "Beam.h"
#include "Constants.h"
#include "CRandom.h"

Beam::Beam(void): MyObject()
{

}

Beam::Beam(int type, Point velloc): MyObject()
{
	oVelloc.set(velloc.x, velloc.y);

	typeBeam = type;
	InitWithType(type);
}

Beam::~Beam(void)
{
	
}

bool Beam::Init(cocos2d::Layer *layer){
	return true;
}

void Beam::InitWithType(int type){
	numMemBeam = CRandom::RandomBetweenIntRemoveBias(kNumMemBeamMin, kNumMemBeamMax);
	listSpriteBeam = Vector<Sprite*>(numMemBeam);

	switch (type)
	{
	case kTypeBeam1:
		for (int i = 0; i < numMemBeam; i++)
		{
			auto beam = Sprite::create("Beam1.png");
			beam->setPositionX(i * beam->getBoundingBox().size.width);
			this->addChild(beam);
			listSpriteBeam.pushBack(beam);
		}
		break;
	case kTypeBeam2:
		for (int i = 0; i < numMemBeam; i++)
		{
			auto beam = Sprite::create("Beam2.png");
			beam->setPositionX(i * beam->getBoundingBox().size.width);
			this->addChild(beam);
			listSpriteBeam.pushBack(beam);
		}
		break;
	case kTypeBeam3:
		for (int i = 0; i < numMemBeam; i++)
		{
			auto beam = Sprite::create("Beam3.png");
			beam->setPositionX(i * beam->getBoundingBox().size.width);
			this->addChild(beam);
			listSpriteBeam.pushBack(beam);
		}
		break;
	case kTypeBeam4:
		for (int i = 0; i < numMemBeam; i++)
		{
			auto beam = Sprite::create("Beam4.png");
			beam->setPositionX(i * beam->getBoundingBox().size.width);
			this->addChild(beam);
			listSpriteBeam.pushBack(beam);
		}
		break;
	default:
		break;
	}
}

void Beam::UpdateAnimation(float deltaTime){

}

void Beam::UpdateMove(float deltaTime){
	oPos.x = this->getPositionX();

	oPos.x += oVelloc.x * deltaTime;

	this->setPositionX(oPos.x);
}

void Beam::Update(float deltaTime){
	UpdateMove(deltaTime);
}

void Beam::UpdateStatus(float deltaTime){

}

void Beam::Release(){
	listSpriteBeam.clear();
	this->removeFromParent();
}

Rect Beam::getCollisionBox(){
	Rect convertToNodeSpace = BoundingBoxConvertedToNodeSpace(listSpriteBeam.front());
	float minX = convertToNodeSpace.origin.x;
	float minY = convertToNodeSpace.origin.y;
	float width = numMemBeam * convertToNodeSpace.size.width;
	float height = convertToNodeSpace.size.height;
	return Rect(minX, minY, width, height);
}