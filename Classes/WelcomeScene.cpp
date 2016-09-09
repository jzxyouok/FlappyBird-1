#include "WelcomeScene.h"

Scene* WelcomeLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = WelcomeLayer::create();

	scene->addChild(layer);

	return scene;
}

bool WelcomeLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 得到系统时间
	time_t t = time(NULL);
	tm* lt = localtime(&t);
	int hour = lt->tm_hour;

	// 根据时间渲染不同的背景图片
	Sprite* bg;
	if (hour >= 6 && hour <= 17)
	{
		bg = Sprite::createWithSpriteFrameName("bg_day.png");
	}
	else
	{
		bg = Sprite::createWithSpriteFrameName("bg_night.png");
	}
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg, 0);

	return true;
}