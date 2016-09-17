#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Bird.h"

USING_NS_CC;
using namespace CocosDenshion;

#define min(X,Y) ((X) < (Y) ? (X) : (Y)) 
#define max(X,Y) ((X) > (Y) ? (X) : (Y)) 

const int DOWN_PIPE = 12;		// 标记
const int UP_PIPE = 21;
const int PIPE_PASS = 30;
const int PIPE_NEW = 31;
const int BIRD_NEW = 32;
const int LAND_TAG = 33;

const int BIRD_RADIUS = 23;		// 小鸟半径
const int BIRD_VELOCITY = 260;	// 小鸟重力
const int PIPE_WIDTH = 52;		// 管道宽度
const int PIPE_HEIGHT = 320;	// 管道长度
const int PIPE_DISTANCE = 100;  // 上下管道间隔
const int PIPE_INTERVAL = 180;  // 每组管道间隔

const int WAIT_DISTANCE = 100;  // 创建管道等待距离
const float MOVE_SPEED = 2.0f;  // 滚动速度

typedef enum {
	GAME_STATE_READY = 1,
	GAME_STATE_START,
	GAME_STATE_OVER
} GameState;

// 委托的基类
class StatusDelegate {
public:
	virtual void onGameStart(void) = 0;

};

class GameLayer : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(GameLayer);

	CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);
private:
	int score;				// 分数
	GameState gameState;	// 游戏状态
	Bird* bird;				// 小鸟
	Node* groundNode;		// 地板节点
	Sprite* land1;			// 地板
	Sprite* land2;
	vector<Node *> pipes;	// 管道组

	void onTouchesBegan(const vector<Touch*>& touches, Event* event);

	// 滚动
	void scroll(float dt);
	// 捕捉游戏状态
	void checkGameState(float dt);
	// 游戏结束
	void gameOver();

	void rotateBird();
	void checkHit();
	void createPipes();		// 创建管道
	int getRandomHeight();	// 得到随机长度
	void birdFadeOut();
	void birdRemove();
};

#endif