#include "GameScene.h"

bool GameScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	// 设置重力
	this->getPhysicsWorld()->setGravity(Vect(0, -900));

	// 背景层
	auto background = BackgroundLayer::create();
	if (background)
	{
		this->addChild(background, 0);
	}

	// 状态层
	auto statusLayer = StatusLayer::create();

	// 游戏层
	auto gameLayer = GameLayer::create();
	if (gameLayer)
	{
		gameLayer->setDelegator(statusLayer);
		this->addChild(gameLayer);
	}

	if (statusLayer) {
		this->addChild(statusLayer);
	}

	return true;
}