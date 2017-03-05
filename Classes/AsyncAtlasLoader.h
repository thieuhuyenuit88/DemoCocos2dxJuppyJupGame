#pragma once
#include "cocos2d.h"
#include <thread>
#include <mutex>

USING_NS_CC;

class AsyncAtlasLoader: public Ref
{
protected:
	std::vector<std::string> atlasList;
	int atlasIndex;

	std::thread *thd;
	std::mutex mtx;

	bool running;
	bool recentAtlasLoaded;
	bool atlasLoadingEnded;

	Ref *callbackTarget;
	SEL_CallFunc onAtlasLoaded;
	SEL_CallFunc onAtlasLoadingFinished;
public:
	AsyncAtlasLoader(void);
	AsyncAtlasLoader(const std::vector<std::string> &atlasList, Ref *callbackTarget, SEL_CallFunc onAtlasLoaded, SEL_CallFunc onAtlasLoadingFinished);
	virtual ~AsyncAtlasLoader(void);

	//at compile time
	inline const std::vector<std::string> & getAtlasList(void) const
	{
		return this->atlasList;
	}

	inline int getAtlasIndex(void) const
	{
		return this->atlasIndex;
	}

	void Start(void);
	void Stop(void);

	void update(float dt);
private:
	static void * Run(void *arg);
};

