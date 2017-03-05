#include "CManagerBackgroud.h"
#include "Constants.h"

CManagerBackgroud::CManagerBackgroud(void)
{
}


CManagerBackgroud::~CManagerBackgroud(void)
{
	listWallLeft.clear();
	listWallRight.clear();
}

void CManagerBackgroud::Init(Layer* layer){
	auto wallLeft1 = Sprite::create("Wall.png");
	auto wallLeft2 = Sprite::create("Wall.png");
	auto wallLeft3 = Sprite::create("Wall.png");

	auto wallRight1 = Sprite::create("Wall.png");
	auto wallRight2= Sprite::create("Wall.png");
	auto wallRight3 = Sprite::create("Wall.png");

	wallLeft1->setFlippedX(true);
	wallLeft1->setAnchorPoint(Vec2(0,0));
	wallLeft1->setPosition(Vec2(0, 0));
	layer->addChild(wallLeft1, kZIndexWall); //retain
	listWallLeft.pushBack(wallLeft1); //retain

	wallLeft2->setFlippedX(true);
	wallLeft2->setAnchorPoint(Vec2(0,0));
	wallLeft2->setPosition(Vec2(0, wallLeft2->getBoundingBox().size.height));
	layer->addChild(wallLeft2, kZIndexWall);
	listWallLeft.pushBack(wallLeft2);

	wallLeft3->setFlippedX(true);
	wallLeft3->setAnchorPoint(Vec2(0,0));
	wallLeft3->setPosition(Vec2(0, wallLeft3->getBoundingBox().size.height * 2));
	layer->addChild(wallLeft3, kZIndexWall);
	listWallLeft.pushBack(wallLeft3);

	wallRight1->setAnchorPoint(Vec2(1,0));
	wallRight1->setPosition(Vec2(GETWINSIZE_WIDTH, 0));
	layer->addChild(wallRight1, kZIndexWall);
	listWallRight.pushBack(wallRight1);

	wallRight2->setAnchorPoint(Vec2(1,0));
	wallRight2->setPosition(Vec2(GETWINSIZE_WIDTH, wallRight2->getBoundingBox().size.height));
	layer->addChild(wallRight2, kZIndexWall);
	listWallRight.pushBack(wallRight2);

	wallRight3->setAnchorPoint(Vec2(1,0));
	wallRight3->setPosition(Vec2(GETWINSIZE_WIDTH, wallRight3->getBoundingBox().size.height * 2));
	layer->addChild(wallRight3, kZIndexWall);
	listWallRight.pushBack(wallRight3);
}

void CManagerBackgroud::Update(CustomFollow* cusFollow){
	const Vector<Sprite*> copyWallsLeft = getCopyListWallLeft();
	for (auto wallLeft: copyWallsLeft)
	{
		if (wallLeft->getPositionY() +  wallLeft->getBoundingBox().size.height <= 
			cusFollow->GetCurRectView().origin.y)
		{
			listWallLeft.eraseObject(wallLeft);

			//wall still alive
			wallLeft->setPositionY(listWallLeft.back()->getPositionY() + 
				listWallLeft.back()->getBoundingBox().size.height);
			listWallLeft.pushBack(wallLeft);
		}
	}

	const Vector<Sprite*> copyWallsRight = getCopyListWallRight();
	for (auto wallRight: copyWallsRight)
	{
		if (wallRight->getPositionY() + wallRight->getBoundingBox().size.height <= 
			cusFollow->GetCurRectView().origin.y)
		{
			listWallRight.eraseObject(wallRight);

			//wall still alive
			wallRight->setPositionY(listWallRight.back()->getPositionY() + 
				listWallRight.back()->getBoundingBox().size.height);
			listWallRight.pushBack(wallRight);
		}
	}
}
