#pragma once
#include "cocos2d.h"
#include "AsyncAtlasLoader.h"
#include "AsyncImageLoader.h"

USING_NS_CC;

class LoadingScene: public Layer
{
protected:
	AsyncAtlasLoader *asyncAtlasLoader;
	AsyncImageLoader *asyncImageLoader;

public:
	LoadingScene(void);
	virtual ~LoadingScene(void);

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(LoadingScene);

	void onEnter(void);

protected:
	void StartLoading(void);
	void EndLoading(void);
	void PrepareLists(void);
	void PrepareImageList(void);
	void PrepareAtlasList(void);
	void UpdateProgress(void);
	void StartImageLoading(void);
	void OnImageLoaded(int index);
	void OnImageLoadingFinished(bool successful);
	void StartAtlasLoading(void);
	void OnAtlasLoaded(void);
	void OnAtlasLoadingFinished(void);
};

