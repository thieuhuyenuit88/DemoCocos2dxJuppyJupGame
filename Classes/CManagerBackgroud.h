#pragma once
#include "Singleton.h"
#include "cocos2d.h"
#include "CustomFollow.h"

USING_NS_CC;

class CManagerBackgroud: public Singleton<CManagerBackgroud>
{
private:
	Vector<Sprite*> listWallLeft;
	Vector<Sprite*> listWallRight;

	const Vector<Sprite*>& getCopyListWallLeft(){
		return listWallLeft;
	}

	const Vector<Sprite*>& getCopyListWallRight(){
		return listWallRight;
	}
public:
	CManagerBackgroud(void);
	virtual ~CManagerBackgroud(void);

	void Init(Layer* layer);
	void Update(CustomFollow* cusFollow);
};

