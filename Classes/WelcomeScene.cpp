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

	// 标题
	Sprite* title = Sprite::createWithSpriteFrameName("title.png");
	title->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height * 5 / 7));
	this->addChild(title, 1);

	// 版权信息
	Sprite* copyright = Sprite::createWithSpriteFrameName("brand_copyright.png");
	copyright->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 6));
	this->addChild(copyright, 2);

	// 开始按钮
	Sprite* startButtonNormal = Sprite::createWithSpriteFrameName("button_play.png");
	Sprite* startButtonSelected = Sprite::createWithSpriteFrameName("button_play.png");
	startButtonSelected->setPositionY(5);

	auto menuItem = MenuItemSprite::create(startButtonNormal, startButtonSelected, CC_CALLBACK_1(WelcomeLayer::menuStartCallback, this));
	menuItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 5));

	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(Vec2(origin.x, origin.y));
	this->addChild(menu, 1);

	// 地板
	land1 = Sprite::createWithSpriteFrameName("land.png");
	land1->setAnchorPoint(Vec2::ZERO);
	land1->setPosition(Vec2::ZERO);
	this->addChild(land1, 1);

	land2 = Sprite::createWithSpriteFrameName("land.png");
	land2->setAnchorPoint(Vec2::ZERO);
	land2->setPosition(Vec2(land1->getContentSize().width - 2.0f, 0));
	this->addChild(land2, 1);

	// 开启定时器，滚动地板
	this->schedule(schedule_selector(WelcomeLayer::scrollLand), 0.01f);

	return true;
}

// 开始按钮回调函数
void WelcomeLayer::menuStartCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("sounds/start.ogg");

	//auto scene = GameLayer::createScene();

	//Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}

// 地板滚动
void WelcomeLayer::scrollLand(float dt)
{
	land1->setPositionX(land1->getPositionX() - 2.0f);
	land2->setPositionX(land1->getPositionX() + land1->getContentSize().width - 2.0f);

	if (land2->getPositionX() == 0)
	{
		land1->setPositionX(0);
	}
}