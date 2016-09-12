#ifndef __BIRD_SPRITE_H__
#define __BIRD_SPRITE_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

typedef enum{
	ACTION_STATE_READY,
	ACTION_STATE_FLY,
	ACTION_STATE_DIE
}BirdState;

class Bird : public cocos2d::Sprite
{
public:
	static Bird* createBird();
	virtual bool init();

	void ready();
	void fly();
	void die();
private:
	string birdName;	// 小鸟名字
	string birdFormat;	// 小鸟帧动画名字

	BirdState m_state;	// 小鸟状态

	Action* flyAcion;	// 飞行动作
	Action* swingAction;// 浮动动作

	bool changeState(BirdState state); // 改变状态
};

#endif