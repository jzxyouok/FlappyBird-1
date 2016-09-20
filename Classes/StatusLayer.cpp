#include "StatusLayer.h"

bool StatusLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	// 初始化分数
	currentScore = 0;
	m_bestScore = 0;
	isNewRecord = false;

	// 加载数字资源
	Number::getInstance()->loadNumber(NUMBER_FONT.c_str(), "font_0%02d.png", 48);
	Number::getInstance()->loadNumber(NUMBER_SCORE.c_str(), "number_score_%02d.png");

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
	this->addChild(scoreSprite);
}

// 游戏结束,传入当前分和最高分
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

// 全屏闪烁
void StatusLayer::blinkFullScreen()
{
	auto blinkAction = Sequence::create(FadeIn::create(0.1f), FadeOut::create(0.1f), NULL);
	CallFunc* actionDone = CallFunc::create(bind(&StatusLayer::fadeInGameOver, this));
	whiteSprite->stopAllActions();
	whiteSprite->runAction(Sequence::createWithTwoActions(blinkAction, actionDone));
}

// 游戏结束标签淡入
void StatusLayer::fadeInGameOver()
{
	Sprite* gameoverSprite = Sprite::createWithSpriteFrameName("text_game_over.png");
	gameoverSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 3));
	this->addChild(gameoverSprite);

	// 跳到得分板
	CallFunc* actionDone = CallFunc::create(bind(&StatusLayer::jumpToScorePanel, this));
	gameoverSprite->stopAllActions();
	gameoverSprite->runAction(Sequence::createWithTwoActions(FadeIn::create(0.5f), actionDone));
}

// 跳到得分面板
void StatusLayer::jumpToScorePanel()
{
	// 分数面板
	Sprite* scorepanelSprite = Sprite::createWithSpriteFrameName("score_panel.png");
	scorepanelSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y - scorepanelSprite->getContentSize().height));
	this->addChild(scorepanelSprite);

	// 得分
	auto curScoreSprite = (Sprite*)Number::getInstance()->convert(NUMBER_SCORE.c_str(), this->currentScore, Gravity::GRAVITY_RIGHT);
	curScoreSprite->setAnchorPoint(Vec2(1, 0));
	curScoreSprite->setPosition(Vec2(origin.x + visibleSize.width * 3 / 4 + 20.0f, origin.y + visibleSize.height * 1 / 2));
	this->addChild(curScoreSprite);

	// 最高分
	auto bestScoreSprite = (Sprite*)Number::getInstance()->convert(NUMBER_SCORE.c_str(), this->m_bestScore, Gravity::GRAVITY_RIGHT);
	bestScoreSprite->setAnchorPoint(Vec2(1, 1));
	bestScoreSprite->setPosition(scorepanelSprite->getContentSize().width - 28, 50);
	scorepanelSprite->addChild(bestScoreSprite);

	// 奖牌
	string medalsName = this->getMedalsName(currentScore);
	if (medalsName != "")
	{
		Sprite* medalsSprite = Sprite::createWithSpriteFrameName(medalsName);
		medalsSprite->addChild(this->blink);
		medalsSprite->setPosition(54, 58);
		scorepanelSprite->addChild(medalsSprite);
	}

	// 新纪录
	if (this->isNewRecord)
	{
		Sprite* newTagSprite = Sprite::createWithSpriteFrameName("new.png");
		newTagSprite->setPosition(-16, 12);
		bestScoreSprite->addChild(newTagSprite);
	}

	auto scorePanelMoveTo = MoveTo::create(0.8f, Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 10.0f));
	EaseExponentialOut* sineIn = EaseExponentialOut::create(scorePanelMoveTo);
	CallFunc* actionDone = CallFunc::create(bind(&StatusLayer::fadeInRestartBtn, this));
	scorepanelSprite->stopAllActions();
	scorepanelSprite->runAction(Sequence::createWithTwoActions(sineIn, actionDone));
}

// 根据得分得到奖牌名
string StatusLayer::getMedalsName(int score)
{
	// 闪烁效果
	this->setBlinkSprite();

	string medalsName = "";
	if (this->currentScore >= 10 && this->currentScore < 20)
	{
		medalsName = "medals_0.png";
	}
	else if (this->currentScore >= 20 && currentScore < 30)
	{

		medalsName = "medals_1.png";
	}
	else if (currentScore >= 30 && currentScore < 50)
	{
		medalsName = "medals_2.png";
	}
	else if (currentScore >= 50)
	{
		medalsName = "medals_3.png";
	}

	return medalsName;
}

// 闪烁精灵
void StatusLayer::setBlinkSprite()
{
	blink = Sprite::createWithSpriteFrameName("blink_00.png");

	// 添加帧动画
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	for (int i = 0; i < 3; i++)
	{
		const char *filename = String::createWithFormat("blink_%02d.png", i)->getCString();
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	for (int i = 2; i >= 0; i--)
	{
		const char *filename = String::createWithFormat("blink_%02d.png", i)->getCString();
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	auto animate = Animate::create(animation);
	auto actionDone = CallFunc::create(bind(&StatusLayer::blinkAction, this));
	blink->runAction(RepeatForever::create(Sequence::createWithTwoActions(animate, actionDone)));
}

// 闪烁精灵随机设置位置
void StatusLayer::blinkAction()
{
	if (blink && blink->getParent())
	{
		Size activeSize = blink->getParent()->getContentSize();
		blink->setPosition(rand() % ((int)(activeSize.width)), rand() % ((int)(activeSize.height)));
	}
}

// 按钮淡入
void StatusLayer::fadeInRestartBtn()
{
	// 继续按钮
	Sprite* restartBtn = Sprite::createWithSpriteFrameName("button_play.png");
	Sprite* restartBtnActive = Sprite::createWithSpriteFrameName("button_play.png");
	restartBtnActive->setPositionY(-4);
	auto  menuItem = MenuItemSprite::create(restartBtn, restartBtnActive, NULL, CC_CALLBACK_1(StatusLayer::menuRestartCallback, this));
	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(Vec2(origin.x + visibleSize.width / 2 - restartBtn->getContentSize().width / 2, origin.y + visibleSize.height * 2 / 7 - 10.0f));
	this->addChild(menu);

	// 排行榜
	Sprite* rateBtn = Sprite::createWithSpriteFrameName("button_score.png");
	rateBtn->setPosition(Vec2(origin.x + visibleSize.width / 2 + rateBtn->getContentSize().width / 2, origin.y + visibleSize.height * 2 / 7 - 10.0f));
	this->addChild(rateBtn);

}

// 重新开始游戏
void StatusLayer::menuRestartCallback(Ref* pSender)
{
	auto scene = GameScene::create();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}