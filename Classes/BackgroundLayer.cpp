#include "BackgroundLayer.h"

bool BackgroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// 得到系统时间
	time_t t = time(NULL);
	tm* lt = localtime(&t);
	int hour = lt->tm_hour;

	// 根据时间渲染背景图片
	Sprite *background;
	if (hour >= 6 && hour <= 17){
		background = Sprite::createWithSpriteFrameName("bg_day.png");
	}
	else{
		background = Sprite::createWithSpriteFrameName("bg_night.png");
	}

	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	this->addChild(background);

	return true;
}