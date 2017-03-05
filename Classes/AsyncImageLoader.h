#pragma once
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

typedef void (Ref::*SEL_CallFuncI)(int);
typedef void (Ref::*SEL_CallFuncB)(bool);

#define  callfuncI_selector(_func_) SEL_CallFuncI(&_func_)
#define  callfuncB_selector(_func_) SEL_CallFuncB(&_func_)

class AsyncImageLoader: public Ref
{
protected:
	std::vector<string> imageList;
	int imageIndex;

	bool running;

	Ref *callbackTarget;
	SEL_CallFuncI onImageLoaded;
	SEL_CallFuncB onImageLoadingFinished;
public:
	AsyncImageLoader(void);
	AsyncImageLoader(const std::vector<string> &imageList, Ref* callbackTarget, SEL_CallFuncI onImageLoaded,
		SEL_CallFuncB onImageLoadingFinished);
	virtual ~AsyncImageLoader(void);

	//at the compile time
	inline const vector<string> & getImageList(void) const
	{
		return this->imageList;
	}

	inline int getImageIndex(void) const
	{
		return this->imageIndex;
	}

	void Start(void);
	void Stop(void);
private:
	void addImageAsyncCallback(void *textureObject);
};

