#include "BarrierGaps.h"
#include "Constants.h"

BarrierGaps::BarrierGaps(void)
{
}


BarrierGaps::~BarrierGaps(void)
{
	
}

bool BarrierGaps::Init(cocos2d::Layer *layer, Point pos, float _timeMove, float _timeDelay){
	this->setPosition(pos);

	timeMove = _timeMove;
	timeDelay = _timeDelay;

	listGaps = Vector<Sprite*>(2);

	gapLeft = Sprite::create("Gaps.png");
	gapLeft->setAnchorPoint(Vec2(1, 0.5f));
	gapLeft->setPosition(GETVISIBLESIZE_WIDTH/2, 0);
	this->addChild(gapLeft);
	listGaps.pushBack(gapLeft);

	gapRight = Sprite::create("Gaps.png");
	gapRight->setFlippedX(true);
	gapRight->setAnchorPoint(Vec2(0, 0.5f));
	gapRight->setPosition(GETVISIBLESIZE_WIDTH/2, 0);
	this->addChild(gapRight);
	listGaps.pushBack(gapRight);

	auto move = MoveBy::create(timeMove, Vec2(-(GETVISIBLESIZE_WIDTH/2 - 200), 0));
	auto moveBack = move->reverse();

	auto moveEase1 = EaseBackIn::create(move->clone());
	auto moveEaseBack1 = moveEase1->reverse();

	auto moveEase2 = EaseBackIn::create(moveBack->clone());
	auto moveEaseBack2 = moveEase2->reverse();

	auto delay = DelayTime::create(timeDelay);

	auto seq1 = Sequence::create(move, delay, moveEase2, delay->clone(), nullptr);
	auto seq2 = Sequence::create(moveBack, delay->clone(), moveEase1, delay->clone(), nullptr);

	gapLeft->runAction(RepeatForever::create(seq1));
	gapRight->runAction(RepeatForever::create(seq2));

	layer->addChild(this, kZIndexGap);

	return true;
}

void BarrierGaps::Update(float deltaTime){

}

void BarrierGaps::Release(){
	listGaps.clear();
	this->removeAllChildren();
	this->removeFromParent();
}