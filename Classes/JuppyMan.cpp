#include "JuppyMan.h"
#include "Constants.h"

JuppyMan::JuppyMan(void): MyObject()
{
	
}

JuppyMan::JuppyMan(cocos2d::Layer *layer):MyObject(){
	Init(layer);
}

JuppyMan::~JuppyMan(void)
{
}

bool JuppyMan::Init(cocos2d::Layer *layer){
	oAccel = Point(0, -1500);
	oVelloc = Point(0, 0);
	oPos = Point(GETWINSIZE_WIDTH / 2, 100);

	this->setPosition(oPos);

	spriteJuppy = Sprite::create("PlayerYellow.png");
	this->addChild(spriteJuppy);

	copters = Sprite::create("Copters.png");
	this->addChild(copters);
	copters->setPosition(Vec2(spriteJuppy->getPositionX(), spriteJuppy->getPositionY() + spriteJuppy->getBoundingBox().size.height/2 + 12)); 
	auto actionRotate3DRP = RepeatForever::create(RotateBy::create(0.5, Vec3(0, 360, 0)));
	copters->runAction(actionRotate3DRP);

	layer->addChild(this, kZIndexJuppy);

	return true;
}

void JuppyMan::HitJup(){
	oVelloc.y = 350;
}

void JuppyMan::UpdateAnimation(float deltaTime){

}

void JuppyMan::UpdateMove(float deltaTime)
{
	//form
	// s = u * t + 0.5 * a * t * t
	// v = u + a* t;

	/*float distance = 0;
	float newSpeed = 0;

	distance = oVelloc.y * deltaTime + 0.5 * oAccel.y * deltaTime * deltaTime;
	newSpeed = oVelloc.y + oAccel.y * deltaTime;

	this->setPositionY(this->getPositionY() + distance);
	
	CCLOG("PosY: %f", this->getPositionY());

	oVelloc.y = newSpeed;*/

	oPos.y = this->getPositionY();

	oVelloc.y += deltaTime * oAccel.y;
	oPos.y += deltaTime * oVelloc.y;

	this->setPositionY(oPos.y);
}

void JuppyMan::UpdateStatus(float deltaTime)
{

}

void JuppyMan::Update(float deltaTime){
	UpdateMove(deltaTime);
}

void JuppyMan::Release(){

}

Rect JuppyMan::getCollisionBox(){
	Rect convertNodeSpaceBox = BoundingBoxConvertedToNodeSpace(spriteJuppy);
	return Rect(convertNodeSpaceBox.origin.x,
		convertNodeSpaceBox.origin.y,
		convertNodeSpaceBox.size.width,
		convertNodeSpaceBox.size.height + copters->getBoundingBox().size.height);
}