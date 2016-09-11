#ifndef __BIRD_SPRITE_H__
#define __BIRD_SPRITE_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Bird : public cocos2d::Sprite
{
public:
	static Bird* createBird();
	virtual bool init();

private:
	string birdName;
	string birdFormat;
};

#endif