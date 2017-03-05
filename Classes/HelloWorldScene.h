#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Wall.h"
#include "JuppyMan.h"
#include "Beam.h"
#include "BarrierBeam.h"
#include "BarrierGaps.h"
#include "BarrierLaser.h"
#include "CustomFollow.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:
	Wall* wallScroll;

	Size winSize;

	JuppyMan* juppy;

	Beam* beam;

	BarrierBeam* barrierBeam;

	BarrierGaps* barrierGaps;

	BarrierLaser* barrierLaser;

	ProgressTimer* timer;

	CustomFollow* follow;

	bool isHolding;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);

	void OnHitJump(float dt);
	void update(float dt);
};

#endif // __HELLOWORLD_SCENE_H__
