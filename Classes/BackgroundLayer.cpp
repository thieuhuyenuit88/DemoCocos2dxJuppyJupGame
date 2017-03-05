#include "BackgroundLayer.h"
#include "Constants.h"

BackgroundLayer::BackgroundLayer(void)
{
}


BackgroundLayer::~BackgroundLayer(void)
{
}

bool BackgroundLayer::init(){
	Color4B colorBG = Color4B(0, 114, 188, 255);
	
	if(!LayerColor::initWithColor(colorBG)){
		return false;
	}

	cloud1 = Sprite::create("Cloud1.png");
	cloud1->setPosition(Vec2(200, 200));
	this->addChild(cloud1, kZIndexCloud);

	cloud2 = Sprite::create("Cloud2.png");
	cloud2->setPosition(Vec2(540, 500));
	this->addChild(cloud2, kZIndexCloud);

	cloud3 = Sprite::create("Cloud3.png");
	cloud3->setPosition(Vec2(250, 800));
	this->addChild(cloud3, kZIndexCloud);

	cloud4 = Sprite::create("Cloud1.png");
	cloud4->setPosition(Vec2(500, 1000));
	this->addChild(cloud4, kZIndexCloud);

	auto cloud5 = Sprite::create("Cloud2.png");
	cloud5->setPosition(Vec2(434, 0));
	this->addChild(cloud5, kZIndexCloud);

	auto cloud6 = Sprite::create("Cloud1.png");
	cloud6->setPosition(Vec2(230, 1200));
	this->addChild(cloud6, kZIndexCloud);

	return true;
}

void BackgroundLayer::onEnter(){
	LayerColor::onEnter();
}

void BackgroundLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags){
	LayerColor::draw(renderer, transform, flags);
}

void BackgroundLayer::SetColorBG(Color4B color){
	Color3B color3B = Color3B(color.r, color.g, color.b);
	this->setColor(color3B);
}
