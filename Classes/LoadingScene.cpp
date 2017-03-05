#include "LoadingScene.h"


LoadingScene::LoadingScene(void)
{
}


LoadingScene::~LoadingScene(void)
{
}

Scene* LoadingScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoadingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LoadingScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	return true;
}
void LoadingScene::onEnter(void){
	Layer::onEnter();
	//...
	MoveTo *actionBeginLoading = MoveTo::create(20, Vec2(200, 300));
	CallFunc *actionBeginLoadingDone = CallFunc::create(CC_CALLBACK_0(LoadingScene::StartLoading, this));
	this->runAction(Sequence::create(actionBeginLoading, actionBeginLoadingDone, NULL));
}

void LoadingScene::StartLoading(void){
	this->PrepareLists();
	this->StartImageLoading();
}

void LoadingScene::EndLoading(void){
	//loading done -> to gamescene?
}

void LoadingScene::PrepareLists(void){
	this->PrepareImageList();
	this->PrepareAtlasList();
}

void LoadingScene::PrepareImageList(void){
	vector<string> imageList;
	auto arr = Array::createWithContentsOfFile("ListOfImages.plist");

	Ref* obj;
	CCARRAY_FOREACH(arr, obj){
		/*imageList.push_back(dynamic_cast<CCString*>(obj)->_string);*/
		imageList.push_back(static_cast<CCString*>(obj)->_string);
	}

	this->asyncImageLoader = new AsyncImageLoader(imageList, this,
		callfuncI_selector(LoadingScene::OnImageLoaded), callfuncB_selector(LoadingScene::OnImageLoadingFinished));
}

void LoadingScene::PrepareAtlasList(void){
	vector<string> atlasList;

	auto arr = CCArray::createWithContentsOfFile("ListOfAtlases.plist");
	Ref *obj;
	CCARRAY_FOREACH(arr, obj){
		/*atlasList.push_back(dynamic_cast<CCString*>(obj)->_string);*/
		atlasList.push_back(static_cast<CCString*>(obj)->_string);
	}

	this->asyncAtlasLoader = new AsyncAtlasLoader(atlasList, this,
		callfunc_selector(LoadingScene::OnAtlasLoaded), callfunc_selector(LoadingScene::OnAtlasLoadingFinished));
}

void LoadingScene::UpdateProgress(void){

}

void LoadingScene::StartImageLoading(void){
	this->asyncImageLoader->Start();
}

void LoadingScene::OnImageLoaded(int index){
	this->UpdateProgress();
}

void LoadingScene::OnImageLoadingFinished(bool successful){
	if (!successful)
	{
		// show error
		return;
	}

	this->StartAtlasLoading();
}

void LoadingScene::StartAtlasLoading(void){
	this->asyncAtlasLoader->Start();
}

void LoadingScene::OnAtlasLoaded(void){
	this->UpdateProgress();
}

void LoadingScene::OnAtlasLoadingFinished(void){
	this->EndLoading();
}