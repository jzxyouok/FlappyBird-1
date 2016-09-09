#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class WelcomeLayer : public cocos2d::Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(WelcomeLayer);
};

#endif