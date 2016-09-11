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
		Animation* animation = Animation::create();
		for (int i = 0; i < 3; i++)
		{
			__String* frameName = __String::createWithFormat(birdFormat.c_str(), i);
			SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}
		animation->setDelayPerUnit(0.1f);

		Animate* animate = Animate::create(animation);

		this->runAction(RepeatForever::create(animate));

		return true;
	}
	else
	{
		return false;
	}
}