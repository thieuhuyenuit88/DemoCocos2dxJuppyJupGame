#include "AsyncImageLoader.h"


AsyncImageLoader::AsyncImageLoader(const std::vector<string> &imageList, Ref* callbackTarget, SEL_CallFuncI onImageLoaded,
								   SEL_CallFuncB onImageLoadingFinished): running(false),
	callbackTarget(callbackTarget), onImageLoaded(onImageLoaded), onImageLoadingFinished(onImageLoadingFinished)
{
	this->imageList = imageList;
	this->imageIndex = -1;
}

AsyncImageLoader::AsyncImageLoader(void)
{
}

AsyncImageLoader::~AsyncImageLoader(void)
{
}

void AsyncImageLoader::Start(void){
	if (!this->running)
	{
		this->running = true;
		this->addImageAsyncCallback(this); // truyền this làm cờ hiệu
	}
}

void AsyncImageLoader::Stop(void){
	this->running = false;
}

// được gọi mỗi khi nạp xong một hình
void AsyncImageLoader::addImageAsyncCallback(void *textureObject){
	auto This = reinterpret_cast<AsyncImageLoader *>(textureObject);

	if (!textureObject)
	{
		// nạp không được, kết thúc
		(this->callbackTarget->*this->onImageLoadingFinished)(false);
	}else{
		// đã nạp được hình
		if (this != textureObject)
		{
			(this->callbackTarget->*this->onImageLoaded)(this->imageIndex);
		}

		// nếu bị gọi dừng giữa chừng
		if (!this->running)
			return;

		// xong hết danh sách chưa?
		if (++this->imageIndex == this->imageList.size())
			(this->callbackTarget->*this->onImageLoadingFinished)(true);
		else
			CCTextureCache::sharedTextureCache()->addImageAsync(this->imageList[this->imageIndex].c_str(),
			CC_CALLBACK_1(AsyncImageLoader::addImageAsyncCallback, this));
	}
}