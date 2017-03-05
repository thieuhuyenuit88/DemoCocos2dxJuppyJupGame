#pragma once
#include "Singleton.h"
#include "cocos2d.h"
#include "MyObject.h"

USING_NS_CC;
class CustomFollow;

class CManagerBarrier: public Singleton<CManagerBarrier>
{
private:
	Vector<MyObject*> listBarrier;
	Layer* containerLayer;

	const Vector<MyObject*> & getCopyListBarrier(){
		return listBarrier;
	};

	void AddBarrier();

	float oldPosY;
	bool isFirst;
public:
	CManagerBarrier(void);
	virtual ~CManagerBarrier(void);

	Vector<MyObject*> GetListBarrier(){
		return listBarrier;
	}

	void InitListBarrier(Layer *layer);
	
	void UpdateBarrier(CustomFollow * CFollow);
};

