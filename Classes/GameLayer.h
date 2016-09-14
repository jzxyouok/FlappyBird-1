#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Bird.h"

USING_NS_CC;
using namespace CocosDenshion;

#define min(X,Y) ((X) < (Y) ? (X) : (Y)) 
#define max(X,Y) ((X) > (Y) ? (X) : (Y)) 

const int PIPE_PASS = 30;
const int PIPE_NEW = 31;
const int BIRD_NEW = 32;
const int LAND_TAG = 33;

const int PIPE_WIDTH = 52;
const int PIPE_INTERVAL = 180;

const int WAIT_DISTANCE = 100;
const float MOVE_SPEED = 2.0f;

const int BIRD_VELOCITY = 260;

const int DOWN_PIPE = 12;
const int UP_PIPE = 21;
const int PIPE_HEIGHT = 320;
const int PIPE_DISTANCE = 100;

const int BIRD_RADIUS = 23;

typedef enum {
	GAME_STATE_READY = 1,
	GAME_STATE_START,
	GAME_STATE_OVER
} GameState;

class GameLayer : public Layer
{
public:
	virtual bool init();

	void setPhyWorld(PhysicsWorld* world){ this->world = world; }

	CREATE_FUNC(GameLayer);
private:

	PhysicsWorld *world;

	int score;// 分数
	GameState gameState;// 游戏状态
	Bird* bird;// 小鸟
	Node* groundNode;// 地板节点
	// 地板精灵
	Sprite* land1;
	Sprite* land2;
	vector<Node *> pipes;// 管道

	// 滚动
	void scroll(float dt);

	void checkGameState(float dt);

	void gameOver();

	void onTouchesBegan(const vector<Touch*>& touches, Event* event);

	void rotateBird();

	int getRandomHeight();

	void createPipes();

	void checkHit();

	void birdFadeOut();
	void birdRemove();
};

#endif