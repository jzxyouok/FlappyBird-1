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

	// 游戏层
	auto gameLayer = GameLayer::create();
	if (gameLayer)
	{
		this->addChild(gameLayer, 1);
	}

	return true;
}