#include "StatusLayer.h"

bool StatusLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// 初始化分数
	currentScore = 0;
	m_bestScore = 0;
	isNewRecord = false;

	// 加载数字资源
	Number::getInstance()->loadNumber(NUMBER_FONT.c_str(), "font_0%02d.png", 48);
	Number::getInstance()->loadNumber(NUMBER_SCORE.c_str(), "number_score_%02d.png");

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	// 初始分数
	scoreSprite = (Sprite *)Number::getInstance()->convert(NUMBER_FONT.c_str(), 0);
	scoreSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 5 / 6));
	this->addChild(scoreSprite);

	// 准备文字
	textReady = Sprite::createWithSpriteFrameName("text_ready.png");
	textReady->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 3));
	this->addChild(textReady);

	// 准备图片
	tutorial = Sprite::createWithSpriteFrameName("tutorial.png");
	tutorial->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 1 / 2));
	this->addChild(tutorial);

	// 纯白图片，闪烁效果用
	whiteSprite = Sprite::createWithSpriteFrameName("white.png");
	whiteSprite->setScale(100);
	whiteSprite->setOpacity(0);
	this->addChild(whiteSprite, 10000);

	return true;
}

// 游戏开始，准备标签淡出
void StatusLayer::onGameStart()
{
	textReady->runAction(FadeOut::create(0.4f));
	tutorial->runAction(FadeOut::create(0.4f));
}

// 更新分数
void StatusLayer::onGamePlaying(int score)
{
	this->removeChild(scoreSprite);
	scoreSprite = (Sprite*)Number::getInstance()->convert(NUMBER_FONT.c_str(), score);
	scoreSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 5 / 6));
	this->addChild(scoreSprite, 10);
}

void StatusLayer::onGameEnd(int curScore, int bestScore)
{
	currentScore = curScore;
	m_bestScore = bestScore;

	if (currentScore > m_bestScore)
	{
		m_bestScore = curScore;
		isNewRecord = true;
	}
	else
	{
		isNewRecord = false;
	}
	this->removeChild(scoreSprite);
	this->blinkFullScreen();
}

void StatusLayer::blinkFullScreen()
{
	auto fadeOut = FadeOut::create(0.1f);
	auto fadeIn = FadeIn::create(0.1f);
	auto blinkAction = Sequence::create(fadeIn, fadeOut, NULL);
	CallFunc* actionDone = CallFunc::create(bind(&StatusLayer::fadeInGameOver, this));
	auto sequence = Sequence::createWithTwoActions(blinkAction, actionDone);
	whiteSprite->stopAllActions();
	whiteSprite->runAction(sequence);
}

void StatusLayer::fadeInGameOver()
{
	Sprite* gameoverSprite = Sprite::createWithSpriteFrameName("text_game_over.png");
	gameoverSprite->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 3));
	this->addChild(gameoverSprite,10);
}