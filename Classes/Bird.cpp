#include "Bird.h"

Bird* Bird::createBird()
{
	Bird* bird = new Bird();

	if (bird && bird->init())
	{
		bird->autorelease();

		return bird;
	}
	else
	{
		CC_SAFE_DELETE(bird);

		return nullptr;
	}
}

bool Bird::init()
{
	Sprite::init();
	
	srand((unsigned)time(NULL));
	int type = ((int)rand()) % 3;

	switch (type)
	{
	case 0:
		this->birdName = "bird0_0.png";
		this->birdFormat = "bird0_%d.png";
		break;
	case 1:
		this->birdName = "bird1_0.png";
		this->birdFormat = "bird1_%d.png";
		break;
	case 2:
		this->birdName = "bird2_0.png";
		this->birdFormat = "bird2_%d.png";
		break;
	default:
		this->birdName = "bird2_0.png";
		this->birdFormat = "bird2_%d.png";
		break;
	}

	if (this->initWithSpriteFrameName(birdName))
	{
		// 设置小鸟飞行动作
		Animation* animation = Animation::create();
		for (int i = 0; i < 3; i++)
		{
			__String* frameName = __String::createWithFormat(birdFormat.c_str(), i);
			SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}
		animation->setDelayPerUnit(0.1f);
		Animate* animate = Animate::create(animation);
		this->flyAcion = RepeatForever::create(animate);
		
		// 设置小鸟浮动动作
		ActionInterval *up = CCMoveBy::create(0.4f, Point(0, 8));
		ActionInterval *upBack = up->reverse();
		this->swingAction = RepeatForever::create(Sequence::create(up, upBack, NULL));

		return true;
	}
	else
	{
		return false;
	}
}

// 小鸟准备时状态
void Bird::ready()
{
	if (changeState(ACTION_STATE_READY))
	{
		this->runAction(flyAcion);
		this->runAction(swingAction);
	}
}

// 小鸟飞行时状态
void Bird::fly()
{
	if (changeState(ACTION_STATE_FLY))
	{
		this->stopAction(swingAction);
		this->getPhysicsBody()->setGravityEnable(true);
	}
}

// 小鸟死亡状态
void Bird::die()
{
	if (changeState(ACTION_STATE_DIE))
	{
		this->setRotation(-90);
		this->stopAllActions();
	}
}

// 改变小鸟状态
bool Bird::changeState(BirdState state)
{
	m_state = state;
	return true;
}