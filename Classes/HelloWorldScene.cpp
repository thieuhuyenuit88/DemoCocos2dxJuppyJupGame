#include "HelloWorldScene.h"
#include "Constants.h"
#include "CManagerBarrier.h"
#include "CManagerBackgroud.h"
#include "CRandom.h"
#include "BackgroundLayer.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

	// layer bg
	auto layerBG = BackgroundLayer::create();
	scene->addChild(layerBG);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	//glClearColor(0.815f, 0.957f, 0.968f, 1.0f);

    Size visibleSize = Director::getInstance()->getVisibleSize();
	winSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*wallScroll = new Wall;
	this->addChild(wallScroll);
	wallScroll->StartScroll();*/
	
	juppy = new JuppyMan(this);

	//beam = new Beam(kTypeBeam1, Vec2(40, 540), Vec2(20, 0));
	//this->addChild(beam, kZIndexBeam);
	
	CManagerBarrier::GetInstance()->InitListBarrier(this);
	CManagerBackgroud::GetInstance()->Init(this);

	follow = CustomFollow::create(juppy);
	this->runAction(follow);

	/*Size designResolution = Director::sharedDirector()->getOpenGLView()->getDesignResolutionSize();
	Size frameSize = Director::sharedDirector()->getOpenGLView()->getFrameSize();
	CCLOG("Visible size: %4.1f x %4.1f", visibleSize.width, visibleSize.height);
	CCLOG("Win size: %4.1f x %4.1f", winSize.width, winSize.height);
	CCLOG("DesignResolution size: %4.1f x %4.1f", designResolution.width, designResolution.height);
	CCLOG("Frame size: %4.1f x %4.1f", frameSize.width, frameSize.height);*/

	/*CCLOG("BoudingBox beam X: %f, Y: %f, Width: %f, Height: %f", 
	beam->getFullBoundingBox().origin.x, beam->getFullBoundingBox().origin.y,
	beam->getFullBoundingBox().size.width, beam->getFullBoundingBox().size.height);*/

	/*Texture2D *texture = TextureCache::sharedTextureCache()->addImage("LaserRayRed.png");
	Texture2D::TexParams texParams = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
	texture->setTexParameters(&texParams);

	auto laserSp = Sprite::createWithTexture(texture, Rect(0,0, GETVISIBLESIZE_WIDTH, 16));*/
	/*laserSp->setAnchorPoint(Vec2(0, 0.5));
	laserSp->setPosition(0, 200);
	laserSp->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
	this->addChild(laserSp);*/

	/*timer = ProgressTimer::create(laserSp);
	timer->setAnchorPoint(Vec2(1, 0.5f));
	timer->setType(ProgressTimer::Type::BAR);
	timer->setBarChangeRate(Vec2(1, 0));
	timer->setMidpoint(Vec2(1, 0.5));
	timer->setPercentage(0);
	timer->setTag(1);
	timer->setPosition(Vec2(768, 500));
	this->addChild(timer, 100);

	ProgressTo* to1 = ProgressTo::create(2.0f, 100);
	timer->runAction(to1);*/

	/*auto tintColor = Sprite::create("TintColor.png");
	tintColor->setPosition(Vec2(384, 512));
	tintColor->setColor(Color3B(255, 0, 0));
	tintColor->setScale(2.0f);
	this->addChild(tintColor);
	*/
	//listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::OnHitJump));
	isHolding = false;

    return true;
}

void HelloWorld::OnHitJump(float dt){
	if (isHolding)
	{
		juppy->HitJup();
	}
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event){
	isHolding = true;
	return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event){
	isHolding = false;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event){

}

void HelloWorld::update(float dt){
	juppy->Update(dt);
	for (auto barrier: CManagerBarrier::GetInstance()->GetListBarrier())
	{
		barrier->Update(dt);
	}
	CManagerBarrier::GetInstance()->UpdateBarrier(follow);
	CManagerBackgroud::GetInstance()->Update(follow);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
