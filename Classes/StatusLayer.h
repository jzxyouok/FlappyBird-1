#ifndef __STATE_LAYER_H__
#define __STATE_LAYER_H__

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class StatusLayer : public Layer ,public StatusDelegate
{
public:
	virtual bool init();

	void onGameStart();

	CREATE_FUNC(StatusLayer);
private:

	int currentScore;

	Sprite* textReady;
	Sprite* tutorial;
	Sprite* whiteSprite;
};

#endif