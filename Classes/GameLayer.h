#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Bird.h"

USING_NS_CC;
using namespace CocosDenshion;

const int BIRD_RADIUS = 15;


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

	// 默认定时器
	void update(float dt);

private:

	// 游戏状态
	GameStatus gameStatus;

	// 分数
	int score;

	// 小鸟
	Bird* bird;

	// 地板节点
	Node* groundNode;
	// 地板精灵
	Sprite* land1;
	Sprite* land2;

	// 滚动地板
	void scrollLand(float dt);

	void gameOver();

	void onTouchesBegan(const vector<Touch*>& touches, Event *event);
};

#endif