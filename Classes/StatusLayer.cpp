#include "StatusLayer.h"

bool StatusLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	currentScore = 0;


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 准备文字
	textReady = Sprite::createWithSpriteFrameName("text_ready.png");
	textReady->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 3));
	this->addChild(textReady);

	// 准备图片
	tutorial = Sprite::createWithSpriteFrameName("tutorial.png");
	tutorial->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 1 / 2));
	this->addChild(tutorial);

	whiteSprite = Sprite::createWithSpriteFrameName("white.png");
	whiteSprite->setScale(100);
	whiteSprite->setOpacity(0);
	this->addChild(whiteSprite, 10000);

	return true;
}


void StatusLayer::onGameStart()
{
	textReady->runAction(FadeOut::create(0.4f));
	tutorial->runAction(FadeOut::create(0.4f));
}