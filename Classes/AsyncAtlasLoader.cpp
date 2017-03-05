#include "AsyncAtlasLoader.h"


AsyncAtlasLoader::AsyncAtlasLoader(void)
{
}

AsyncAtlasLoader::AsyncAtlasLoader(const std::vector<std::string> &atlasList, Ref *callbackTarget, SEL_CallFunc onAtlasLoaded, SEL_CallFunc onAtlasLoadingFinished)
	: thd(nullptr), running(false), recentAtlasLoaded(false), atlasLoadingEnded(false),
	callbackTarget(callbackTarget),
	onAtlasLoaded(onAtlasLoaded), onAtlasLoadingFinished(onAtlasLoadingFinished)
{
	this->atlasList = atlasList;
	this->atlasIndex = -1;
}

AsyncAtlasLoader::~AsyncAtlasLoader(void)
{
}

void AsyncAtlasLoader::Start(void){
	if (!this->running)
	{
		Director::getInstance()->getScheduler()->scheduleUpdateForTarget(this, 0, false);

		this->running = true;
		this->thd = new std::thread(AsyncAtlasLoader::Run, this);
	}
}

void AsyncAtlasLoader::Stop(void){
	if (this->running)
	{
		this->mtx.lock();
		this->running = false;
		this->mtx.unlock();

		this->thd->join();
		delete this->thd;
		this->thd = nullptr;

		Director::getInstance()->getScheduler()->unscheduleUpdateForTarget(this);
	}
}

//schedule update - call callback in main thread
void AsyncAtlasLoader::update(float dt){
	(void)dt;

	// có atlas vừa được nạp
	if (this->recentAtlasLoaded)
	{
		this->mtx.lock();

		this->recentAtlasLoaded = false;
		(this->callbackTarget->*this->onAtlasLoaded)();

		this->mtx.unlock();
	}

	// đã nạp tất cả atlas
	if (this->atlasLoadingEnded)
	{
		this->mtx.lock();

		this->atlasLoadingEnded = false;
		(this->callbackTarget->*this->onAtlasLoadingFinished)();

		this->running = false;
		this->mtx.unlock();
	}
}

void * AsyncAtlasLoader::Run(void *arg){
	auto This = reinterpret_cast<AsyncAtlasLoader *>(arg);

	while (true)
	{
		This->mtx.lock();
		if (This->running == false)
		{
			This->mtx.unlock();
			break;
		}
		This->mtx.unlock();

		if (++This->atlasIndex >= This->atlasList.size())
		{
			This->atlasLoadingEnded = true;
		}
		else
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(This->atlasList[This->atlasIndex]);
			This->recentAtlasLoaded = true;
		}
	}

	return nullptr;
}