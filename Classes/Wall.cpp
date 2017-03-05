#include "Wall.h"
#include "Constants.h"

Wall::Wall(void)
{
	speedScroll = 4.0f;
	InitWall();
}


Wall::~Wall(void)
{
}

void Wall::InitWall(){
	wall1 = Sprite::create("Wall.png");
	wall2 = Sprite::create("Wall.png");
	wall3 = Sprite::create("Wall.png");
	wall4 = Sprite::create("Wall.png");
	wall5 = Sprite::create("Wall.png");
	wall6 = Sprite::create("Wall.png");

	wall1->setFlippedX(true);
	wall1->setAnchorPoint(Vec2(0, 0));
	wall1->setPosition(Vec2(0, wall1->getBoundingBox().size.height));
	this->addChild(wall1, kZIndexWall);

	wall2->setAnchorPoint(Vec2(0, 0));
	wall2->setFlippedX(true);
	wall2->setPosition(Vec2(0, 0));
	this->addChild(wall2, kZIndexWall);

	wall5->setAnchorPoint(Vec2(0, 0));
	wall5->setFlippedX(true);
	wall5->setPosition(Vec2(0, wall5->getBoundingBox().size.height * 2));
	this->addChild(wall5, kZIndexWall);

	wall3->setAnchorPoint(Vec2(1, 0));
	wall3->setPosition(Vec2(GETWINSIZE_WIDTH, wall3->getBoundingBox().size.height));
	this->addChild(wall3, kZIndexWall);

	wall4->setAnchorPoint(Vec2(1, 0));
	wall4->setPosition(Vec2(GETWINSIZE_WIDTH, 0));
	this->addChild(wall4, kZIndexWall);

	wall6->setAnchorPoint(Vec2(1, 0));
	wall6->setPosition(Vec2(GETWINSIZE_WIDTH, wall6->getBoundingBox().size.height * 2));
	this->addChild(wall6, kZIndexWall);
}

void Wall::StartScrollWall1(){
	wall1->stopAllActions();

	MoveBy* actionMoveBy = MoveBy::create(speedScroll, Vec2(0, -wall1->getBoundingBox().size.height));
	CallFunc* actionMoveDone = CallFunc::create(CC_CALLBACK_0(Wall::ReachedDestinationWall1, this));
	wall1->runAction(Sequence::create(actionMoveBy, actionMoveDone, NULL));
}

void Wall::StartScrollWall2(){
	wall2->stopAllActions();

	MoveBy* actionMoveBy = MoveBy::create(speedScroll, Vec2(0, -wall2->getBoundingBox().size.height));
	CallFunc* actionMoveDone = CallFunc::create(CC_CALLBACK_0(Wall::ReachedDestinationWall2, this));
	wall2->runAction(Sequence::create(actionMoveBy, actionMoveDone, NULL));
}

void Wall::StartScrollWall5(){
	wall5->stopAllActions();

	MoveBy* actionMoveBy = MoveBy::create(speedScroll, Vec2(0, -wall5->getBoundingBox().size.height));
	CallFunc* actionMoveDone = CallFunc::create(CC_CALLBACK_0(Wall::ReachedDestinationWall5, this));
	wall5->runAction(Sequence::create(actionMoveBy, actionMoveDone, NULL));
}

void Wall::StartScrollWall3(){
	wall3->stopAllActions();

	MoveBy* actionMoveBy = MoveBy::create(speedScroll, Vec2(0, -wall3->getBoundingBox().size.height));
	CallFunc* actionMoveDone = CallFunc::create(CC_CALLBACK_0(Wall::ReachedDestinationWall3, this));
	wall3->runAction(Sequence::create(actionMoveBy, actionMoveDone, NULL));
}

void Wall::StartScrollWall4(){
	wall4->stopAllActions();

	MoveBy* actionMoveBy = MoveBy::create(speedScroll, Vec2(0, -wall4->getBoundingBox().size.height));
	CallFunc* actionMoveDone = CallFunc::create(CC_CALLBACK_0(Wall::ReachedDestinationWall4, this));
	wall4->runAction(Sequence::create(actionMoveBy, actionMoveDone, NULL));
}

void Wall::StartScrollWall6(){
	wall6->stopAllActions();

	MoveBy* actionMoveBy = MoveBy::create(speedScroll, Vec2(0, -wall6->getBoundingBox().size.height));
	CallFunc* actionMoveDone = CallFunc::create(CC_CALLBACK_0(Wall::ReachedDestinationWall6, this));
	wall6->runAction(Sequence::create(actionMoveBy, actionMoveDone, NULL));
}

void Wall::ReachedDestinationWall1(){
	wall1->setPosition(Vec2(0, wall1->getBoundingBox().size.height));
	StartScrollWall1();
}

void Wall::ReachedDestinationWall2(){
	wall2->setPosition(Vec2(0, 0));
	StartScrollWall2();
}

void Wall::ReachedDestinationWall5(){
	wall5->setPosition(Vec2(0, wall5->getBoundingBox().size.height * 2));
	StartScrollWall5();
}

void Wall::ReachedDestinationWall3(){
	wall3->setPosition(Vec2(GETWINSIZE_WIDTH, wall3->getBoundingBox().size.height));
	StartScrollWall3();
}

void Wall::ReachedDestinationWall4(){
	wall4->setPosition(Vec2(GETWINSIZE_WIDTH, 0));
	StartScrollWall4();
}

void Wall::ReachedDestinationWall6(){
	wall6->setPosition(Vec2(GETWINSIZE_WIDTH, wall6->getBoundingBox().size.height * 2));
	StartScrollWall6();
}

void Wall::StopScroll(){
	wall1->stopAllActions();
	wall2->stopAllActions();
	wall3->stopAllActions();
	wall4->stopAllActions();
	wall5->stopAllActions();
	wall6->stopAllActions();
}

void Wall::StartScroll(){
	StartScrollWall1();
	StartScrollWall2();
	StartScrollWall3();
	StartScrollWall4();
	StartScrollWall5();
	StartScrollWall6();
}