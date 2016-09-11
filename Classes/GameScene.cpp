#include "GameScene.h"

Scene* GameLayer::createScene()
{
	auto scene = Scene::createWithPhysics();

	PhysicsWorld * phyWorld = scene->getPhysicsWorld();

	// 设置重力，不受影响
	phyWorld->setGravity(Vect(0, 0));

	auto layer = GameLayer::create();

	scene->addChild(layer);

	return scene;
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}




	return true;
}