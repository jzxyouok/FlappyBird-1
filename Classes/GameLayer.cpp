#include "GameLayer.h"

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 初始化状态和分数
	this->gameState = GAME_STATE_READY;
	this->score = 0;

	// 添加小鸟,小鸟物理引擎
	bird = Bird::createBird();
	PhysicsBody* body = PhysicsBody::create();
	body->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
	body->setDynamic(true);	// 设置为刚体
	body->setLinearDamping(0.0f);
	body->setGravityEnable(false); 
	body->setContactTestBitmask(0x01);// 设置接触掩码
	bird->setPhysicsBody(body);
	bird->setPosition(origin.x + visibleSize.width * 1 / 3 - 5, origin.y + visibleSize.height / 2 + 5);
	bird->ready();
	bird->setTag(BIRD_NEW);
	this->addChild(bird);

	// 地板节点
	groundNode = Node::create();
	float landHeight = Sprite::createWithSpriteFrameName("land.png")->getContentSize().height;
	auto groundBody = PhysicsBody::create();
	groundBody->addShape(PhysicsShapeBox::create(Size(visibleSize.width, landHeight)));
	groundBody->setDynamic(false);
	groundBody->setLinearDamping(0.0f);
	groundBody->setContactTestBitmask(0x01);
	groundNode->setPhysicsBody(groundBody);
	groundNode->setPosition(visibleSize.width / 2, landHeight / 2);
	groundNode->setTag(LAND_TAG);
	this->addChild(groundNode);

	// 地板
	land1 = Sprite::createWithSpriteFrameName("land.png");
	land1->setAnchorPoint(Vec2::ZERO);
	land1->setPosition(Vec2::ZERO);
	this->addChild(land1, 3);
	land2 = Sprite::createWithSpriteFrameName("land.png");
	land2->setAnchorPoint(Vec2::ZERO);
	land2->setPosition(Vec2(land1->getContentSize().width - 2.0f, 0));
	this->addChild(land2, 3);

	// 开启滚动地板定时器
	this->schedule(schedule_selector(GameLayer::scroll), 0.02f);
	
	// 捕捉游戏状态定时器
	this->schedule(schedule_selector(GameLayer::checkGameState), 0.02f);

	// 注册接触事件监听器
	EventListenerPhysicsContact * contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this](PhysicsContact& contact)
	{
		auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

		// 小鸟与管道接触
		Node* node1 = nullptr;
		if (spriteA->getTag() == BIRD_NEW && spriteB->getTag() == PIPE_NEW)
		{
			node1 = spriteB;
		}
		if (spriteA->getTag() == PIPE_NEW && spriteB->getTag() == BIRD_NEW)
		{
			node1 = spriteA;
		}
		if (node1 != nullptr)
		{
			gameOver();
			return false;
		}

		// 小鸟与地板接触
		Node* node2 = nullptr;
		if (spriteA->getTag() == BIRD_NEW && spriteB->getTag() == LAND_TAG)
		{
			node2 = spriteB;
		}
		if (spriteA->getTag() == LAND_TAG && spriteA->getTag() == BIRD_NEW)
		{
			node2 = spriteA;
		}
		if (node2 != nullptr)
		{
			gameOver();
			return false;
		}

		return false;
	};

	// 加入触摸监听
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);

	// 添加监听器
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

// 滚动
void GameLayer::scroll(float dt)
{
	// 地板滚动
	land1->setPositionX(land1->getPositionX() - MOVE_SPEED);
	land2->setPositionX(land1->getPositionX() + land1->getContentSize().width - MOVE_SPEED);
	if (land2->getPositionX() == 0)
	{
		land1->setPositionX(0);
	}

	// 管子移动
	for (auto singlePipe : this->pipes) {
		singlePipe->setPositionX(singlePipe->getPositionX() - MOVE_SPEED);
		if (singlePipe->getPositionX() < -PIPE_WIDTH) {
			singlePipe->setTag(PIPE_NEW);
			singlePipe->setPosition(Vec2(Director::getInstance()->getVisibleSize().width + PIPE_WIDTH, this->getRandomHeight()));
		}
	}
}

// 捕捉游戏状态
void GameLayer::checkGameState(float dt)
{
	if (this->gameState == GAME_STATE_START) 
	{
		this->rotateBird();
		this->checkHit();
	}
}

// 根据重力设置小鸟的角度
void GameLayer::rotateBird()
{
	float verticalSpeed = bird->getPhysicsBody()->getVelocity().y;
	bird->setRotation(min(max(-90, (verticalSpeed*0.2 + 60)), 30));
}

// 判断碰撞，改变分数
void GameLayer::checkHit()
{
	for (auto pipe : pipes) {
		if (pipe->getTag() == PIPE_NEW) {
			if (pipe->getPositionX() < bird->getPositionX()) {
				SimpleAudioEngine::getInstance()->playEffect("sounds/swooshing.wav");
				
				this->score++;
				
				pipe->setTag(PIPE_PASS);
			}
		}
	}
}

// 触摸事件
void GameLayer::onTouchesBegan(const vector<Touch*>& touches, Event *event)
{
	if (gameState == GAME_STATE_OVER) 
	{
		return;
	}

	SimpleAudioEngine::getInstance()->playEffect("sounds/fly.wav");

	if (gameState == GAME_STATE_READY) 
	{		
		this->delegator->onGameStart();
		bird->fly();
		gameState = GAME_STATE_START;
		this->createPipes();
	}
	else if (gameState == GAME_STATE_START) 
	{
		bird->getPhysicsBody()->setVelocity(Vect(0, BIRD_VELOCITY));
	}
}

// 创建管子
void GameLayer::createPipes() 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// 屏幕中有两组管道
	for (int i = 0; i < 2; i++) 
	{
		
		Sprite* pipeUp = Sprite::createWithSpriteFrameName("pipe_up.png");
		Sprite* pipeDown = Sprite::createWithSpriteFrameName("pipe_down.png");
		Node* pipe = Node::create();

		pipeDown->setPosition(0, PIPE_HEIGHT + PIPE_DISTANCE);
		pipe->addChild(pipeDown, 0, DOWN_PIPE);
		pipe->addChild(pipeUp, 0, UP_PIPE);
		pipe->setPosition(visibleSize.width + i*PIPE_INTERVAL + WAIT_DISTANCE, this->getRandomHeight());

		// 添加物理引擎
		auto body = PhysicsBody::create();
		body->addShape(PhysicsShapeBox::create(pipeDown->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT, Vec2(0, PIPE_HEIGHT + PIPE_DISTANCE)));
		body->addShape(PhysicsShapeBox::create(pipeUp->getContentSize()));
		body->setDynamic(false);
		body->setContactTestBitmask(0x01);
		pipe->setPhysicsBody(body);
		pipe->setTag(PIPE_NEW);

		this->addChild(pipe);
		pipes.push_back(pipe);
	}
}

// 得到随机的管道长度
int GameLayer::getRandomHeight() 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	return rand() % (int)(2 * PIPE_HEIGHT + PIPE_DISTANCE - visibleSize.height);
}

// 游戏结束
void GameLayer::gameOver()
{
	if (gameState == GAME_STATE_OVER)
	{
		return;
	}

	SimpleAudioEngine::getInstance()->playEffect("sounds/hit.wav");

	// 停止滚动
	this->unschedule(schedule_selector(GameLayer::scroll));

	// 执行死亡动作
	bird->die();
	birdFadeOut();
	gameState = GAME_STATE_OVER;
}

void GameLayer::birdFadeOut()
{
	FadeOut* animation = FadeOut::create(1.5);
	CallFunc* animationDone = CallFunc::create(bind(&GameLayer::birdRemove, this));
	Sequence* sequence = Sequence::createWithTwoActions(animation, animationDone);
	bird->runAction(sequence);
}

void GameLayer::birdRemove()
{
	bird->setRotation(0);
	this->removeChild(bird);
}