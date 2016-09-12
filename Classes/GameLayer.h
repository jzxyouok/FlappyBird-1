#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Bird.h"

USING_NS_CC;
using namespace CocosDenshion;

#define min(X,Y) ((X) < (Y) ? (X) : (Y)) 
#define max(X,Y) ((X) > (Y) ? (X) : (Y)) 

const int BIRD_RADIUS = 15;

const int UP_PIPE = 21;
const int DOWN_PIPE = 12;
const int PIPE_PASS = 30;
const int PIPE_NEW = 31;

const int PIPE_HEIGHT = 320;
const int PIPE_WIDTH = 52;
const int PIPE_DISTANCE = 100;

const int PIPE_INTERVAL = 180;

const int WAIT_DISTANCE = 100;

typedef enum {
	GAME_STATUS_READY = 1,
	GAME_STATUS_START,
	GAME_STATUS_OVER
} GameStatus;

class GameLayer : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(GameLayer);
private:
	int score;// 分数
	GameStatus gameStatus;// 游戏状态
	Bird* bird;// 小鸟
	Node* groundNode;// 地板节点
	// 地板精灵
	Sprite* land1;
	Sprite* land2;
	vector<Node *> pipes;// 管道

	// 滚动
	void scroll(float dt);

	void checkBird(float dt);

	void gameOver();

	void onTouchesBegan(const vector<Touch*>& touches, Event *event);


	void rotateBird();

	int getRandomHeight();

	void createPipes();
};

#endif