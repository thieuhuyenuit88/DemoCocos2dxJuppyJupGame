#include "BarrierLaser.h"
#include "CRandom.h"
#include "Constants.h"

BarrierLaser::BarrierLaser(void)
{
	collistionBoxLaser = Rect(0,0,0,0);
	typeLaser = laserDirect = speedLaser = 0;
}


BarrierLaser::~BarrierLaser(void)
{
	
}

bool BarrierLaser::Init(cocos2d::Layer *layer, Point pos, float speed, int direct){
	this->setPosition(pos);
	laserDirect = direct;
	speedLaser = speed;

	if(laserDirect == kDirectRight){
		gun = Sprite::create("LaserGunNormal.png");
		gun->setAnchorPoint(Vec2(0, 0.5f));
		gun->setPositionX(0);
		this->addChild(gun, 1);

		typeLaser = CRandom::RandomBetweenIntRemoveBias(kTypeLaserBlue, kTypeLaserYellow);

		Texture2D *texture;
		switch (typeLaser)
		{
		case kTypeLaserBlue:
			rootLaser = Sprite::create("LaserRootBlue.png");
			texture = TextureCache::sharedTextureCache()->addImage("LaserRayBlue.png");
			break;
		case kTypeLaserGreen:
			rootLaser = Sprite::create("LaserRootGreen.png");
			texture = TextureCache::sharedTextureCache()->addImage("LaserRayGreen.png");
			break;
		case kTypeLaserRed:
			rootLaser = Sprite::create("LaserRootRed.png");
			texture = TextureCache::sharedTextureCache()->addImage("LaserRayRed.png");
			break;
		case kTypeLaserYellow:
			rootLaser = Sprite::create("LaserRootYellow.png");
			texture = TextureCache::sharedTextureCache()->addImage("LaserRayYellow.png");
			break;
		}

		rootLaser->setPositionX(gun->getPositionX() + gun->getBoundingBox().size.width);
		this->addChild(rootLaser, 2);

		Texture2D::TexParams texParams = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
		texture->setTexParameters(&texParams);
		laserRay = Sprite::createWithTexture(texture, Rect(0, 0, GETVISIBLESIZE_WIDTH, 16));

		timer = ProgressTimer::create(laserRay);
		this->addChild(timer, 1);

		ReadyFightingLaser();

	}else if (laserDirect == kDirectLeft)
	{
		gun = Sprite::create("LaserGunNormal.png");
		gun->setFlippedX(true);
		gun->setAnchorPoint(Vec2(1, 0.5f));
		gun->setPositionX(GETVISIBLESIZE_WIDTH);
		this->addChild(gun, 1);

		typeLaser = CRandom::RandomBetweenIntRemoveBias(kTypeLaserBlue, kTypeLaserYellow);

		Texture2D *texture;
		switch (typeLaser)
		{
		case kTypeLaserBlue:
			rootLaser = Sprite::create("LaserRootBlue.png");
			texture = TextureCache::sharedTextureCache()->addImage("LaserRayBlue.png");
			break;
		case kTypeLaserGreen:
			rootLaser = Sprite::create("LaserRootGreen.png");
			texture = TextureCache::sharedTextureCache()->addImage("LaserRayGreen.png");
			break;
		case kTypeLaserRed:
			rootLaser = Sprite::create("LaserRootRed.png");
			texture = TextureCache::sharedTextureCache()->addImage("LaserRayRed.png");
			break;
		case kTypeLaserYellow:
			rootLaser = Sprite::create("LaserRootYellow.png");
			texture = TextureCache::sharedTextureCache()->addImage("LaserRayYellow.png");
			break;
		}

		rootLaser->setPositionX(gun->getPositionX() - gun->getBoundingBox().size.width);
		this->addChild(rootLaser, 2);

		Texture2D::TexParams texParams = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
		texture->setTexParameters(&texParams);
		laserRay = Sprite::createWithTexture(texture, Rect(0, 0, GETVISIBLESIZE_WIDTH, 16));

		timer = ProgressTimer::create(laserRay);
		this->addChild(timer, 1);

		ReadyFightingLaser();
	}

	layer->addChild(this, kZIndexLaser);

	return true;
}

void BarrierLaser::ReadyFightingLaser(){
	
	timer->setOpacity(255);
	timer->setScaleY(1.0f);
	if (laserDirect == kDirectRight)
	{
		//init timer ray laser
		timer->setAnchorPoint(Vec2(0, 0.5f));
		timer->setType(ProgressTimer::Type::BAR);
		timer->setBarChangeRate(Vec2(1, 0));
		timer->setMidpoint(Vec2(0, 0.5));
		timer->setPercentage(0);
		timer->setPosition(Vec2(gun->getPositionX() + gun->getBoundingBox().size.width, 0));
		timer->setVisible(true);
	}else if (laserDirect == kDirectLeft){
		//init timer ray laser
		timer->setAnchorPoint(Vec2(1, 0.5f));
		timer->setType(ProgressTimer::Type::BAR);
		timer->setBarChangeRate(Vec2(1, 0));
		timer->setMidpoint(Vec2(1, 0.5));
		timer->setPercentage(0);
		timer->setPosition(Vec2(gun->getPositionX() - gun->getBoundingBox().size.width, 0));
		timer->setVisible(true);
	}

	//root laser action ready
	rootLaser->setVisible(true);
	rootLaser->setOpacity(255);
	rootLaser->setScale(0.0f);
	auto scaleRoot = ScaleTo::create(2.0f, 1.0f);
	auto rotateRoot = RotateBy::create(2.0f, 360);
	auto actionRootSpawn = Spawn::create(scaleRoot, rotateRoot, nullptr);
	CallFunc* actionDone = CallFunc::create(CC_CALLBACK_0(BarrierLaser::StartFightingLaser, this));
	
	auto delay = DelayTime::create(kTimeDelayLaserBeam);

	auto actionRootSequence = Sequence::create(delay, actionRootSpawn, actionDone, nullptr);
	rootLaser->runAction(actionRootSequence);
}

void BarrierLaser::StartFightingLaser(){
	ProgressTo* to1 = ProgressTo::create(speedLaser, 100);
	CallFunc* fightingDone = CallFunc::create(CC_CALLBACK_0(BarrierLaser::FightingLaserDone, this));
	auto seqActionTimer = Sequence::create(to1, fightingDone, nullptr);
	timer->runAction(seqActionTimer);

	auto rotateRoot = RepeatForever::create(RotateBy::create(2.0f, 360));
	rootLaser->runAction(rotateRoot);
}

void BarrierLaser::FightingLaserDone(){
	auto delayTime = DelayTime::create(1.0f);

	auto scaleTimer = ScaleTo::create(1.0f, 1.0f, 0.1f);
	auto fadeOut = FadeOut::create(1.0f);
	auto spawnTimer = Spawn::create(scaleTimer, fadeOut, nullptr);
	CallFunc* actionDone = CallFunc::create(CC_CALLBACK_0(BarrierLaser::EndFightingAndLoop, this));
	auto actionSeqTimer = Sequence::create(delayTime, spawnTimer, actionDone, nullptr);
	timer->runAction(actionSeqTimer);

	auto scaleRoot = ScaleTo::create(1.0f, 0.1f);
	auto rotateRoot = RotateBy::create(1.0f, 360);
	auto actionRootSpawn = Spawn::create(scaleRoot, rotateRoot, fadeOut->clone(), nullptr);
	auto actionSeqRoot = Sequence::create(delayTime->clone(), actionRootSpawn, nullptr);
	rootLaser->runAction(actionSeqRoot);
}

void BarrierLaser::EndFightingAndLoop(){
	rootLaser->stopAllActions();
	rootLaser->setVisible(false);

	timer->stopAllActions();
	timer->setVisible(false);

	ReadyFightingLaser();
}

void BarrierLaser::Update(float deltaTime){
	Point worldSpacePosTimer = timer->getParent()->convertToWorldSpace(timer->getPosition());
	if (laserDirect == kDirectRight)
	{
		float x = worldSpacePosTimer.x;
		float y = worldSpacePosTimer.y - timer->getBoundingBox().size.height/2 * timer->getScaleY();
		float width = timer->getBoundingBox().size.width * (timer->getPercentage() / 100);
		float height = timer->getBoundingBox().size.height * timer->getScaleY();
		collistionBoxLaser.setRect(x, y, width, height);
	}else if (laserDirect = kDirectLeft)
	{
		float x = worldSpacePosTimer.x - timer->getBoundingBox().size.width * (timer->getPercentage() / 100);
		float y = worldSpacePosTimer.y - timer->getBoundingBox().size.height/2 * timer->getScaleY();
		float width = timer->getBoundingBox().size.width * (timer->getPercentage() / 100);
		float height = timer->getBoundingBox().size.height * timer->getScaleY();
		collistionBoxLaser.setRect(x, y, width, height);
	}
	/*CCLOG("Bouding Box Timer X: %f, Y: %f, Width: %f, Height: %f", 
		collistionBoxLaser.origin.x, collistionBoxLaser.origin.y, collistionBoxLaser.size.width, collistionBoxLaser.size.height);*/
}

void BarrierLaser::Release(){
	this->removeAllChildren();
	this->removeFromParent();
}

Rect BarrierLaser::getCollisionBoxLaser(){
	return collistionBoxLaser;
}