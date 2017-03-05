#pragma once
#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer: public LayerColor
{
private:
	Sprite* cloud1;
	Sprite* cloud2;
	Sprite* cloud3;
	Sprite* cloud4;
public:
	BackgroundLayer(void);
	virtual ~BackgroundLayer(void);

	virtual bool init();  

	CREATE_FUNC(BackgroundLayer);

	virtual void onEnter();
	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);

	void SetColorBG(Color4B color);
};

