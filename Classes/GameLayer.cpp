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
	this->gameStatus = GAME_STATUS_READY;
	this->score = 0;

	// 添加小鸟
	bird = Bird::createBird();
	PhysicsBody *body = PhysicsBody::create();
	body->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setGravityEnable(false);
	bird->setPhysicsBody(body);
	bird->setPosition(origin.x + visibleSize.width * 1 / 3 - 5, origin.y + visibleSize.height / 2 + 5);
	this->addChild(bird, 1);

	// 地板节点
	this->groundNode = Node::create();
	float landHeight = Sprite::createWithSpriteFrameName("land.png")->getContentSize().height;
	auto groundBody = PhysicsBody::create();
	groundBody->addShape(PhysicsShapeBox::create(Size(288, landHeight)));
	groundBody->setDynamic(false);
	groundBody->setLinearDamping(0.0f);
	this->groundNode->setPhysicsBody(groundBody);
	this->groundNode->setPosition(144, landHeight / 2);
	this->addChild(this->groundNode);

	// 地板
	land1 = Sprite::createWithSpriteFrameName("land.png");
	land1->setAnchorPoint(Vec2::ZERO);
	land1->setPosition(Vec2::ZERO);
	this->addChild(land1, 1);

	land2 = Sprite::createWithSpriteFrameName("land.png");
	land2->setAnchorPoint(Vec2::ZERO);
	land2->setPosition(Vec2(land1->getContentSize().width - 2.0f, 0));
	this->addChild(land2, 1);

	// 开启定时器，滚动地板
	this->schedule(schedule_selector(GameLayer::scrollLand), 0.01f);


	// 注册接触事件监听器
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this](PhysicsContact& contact)
	{
		this->gameOver();

		return true;
	};

	// 加入触摸监听
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);

	// 添加监听器
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

// 地板滚动
void GameLayer::scrollLand(float dt)
{
	land1->setPositionX(land1->getPositionX() - 2.0f);
	land2->setPositionX(land1->getPositionX() + land1->getContentSize().width - 2.0f);

	if (land2->getPositionX() == 0)
	{
		land1->setPositionX(0);
	}
}

// 默认定时器
void GameLayer::update(float delta) {
	if (this->gameStatus == GAME_STATUS_START) {
	
	}
}

// 触摸事件
void GameLayer::onTouchesBegan(const vector<Touch*>& touches, Event *event)
{
	if (this->gameStatus == GAME_STATUS_OVER) {
		return;
	}

	SimpleAudioEngine::getInstance()->playEffect("sounds/fly.wav");

	if (this->gameStatus == GAME_STATUS_READY) {
		

		this->gameStatus = GAME_STATUS_START;
	}
	else if (this->gameStatus == GAME_STATUS_START) {
		this->bird->getPhysicsBody()->setVelocity(Vect(0, 260));
	}
}

// 游戏结束
void GameLayer::gameOver()
{
	log("gameover");
}