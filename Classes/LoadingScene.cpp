#include "LoadingScene.h"

Scene* LoadingLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = LoadingLayer::create();

	scene->addChild(layer);

	return scene;
}

bool LoadingLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 等待标签
	auto loading = Label::createWithSystemFont("Loading...", "Arial", 36);
	loading->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(loading);

	// 加载纹理图集
	Director::getInstance()->getTextureCache()->addImageAsync("res.png", CC_CALLBACK_1(LoadingLayer::loadingCallBack, this));
}

// 异步加载精灵帧缓存
void LoadingLayer::loadingCallBack(Texture2D* texture)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res.plist", texture);

	auto call = CallFunc::create([](){
		auto scene = WelcomeLayer::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
	});

	// 延时进入
	this->runAction(Sequence::create(DelayTime::create(0.5), call, nullptr));
}