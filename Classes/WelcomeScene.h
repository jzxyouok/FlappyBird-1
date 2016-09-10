#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "GameScene.h"

USING_NS_CC;
using namespace CocosDenshion;

class WelcomeLayer : public cocos2d::Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(WelcomeLayer);
private:

	// 开始按钮回调函数
	void menuStartCallback(Ref* pSender);

	// 地板滚动函数
	void scrollLand(float dt);

	// 地板
	Sprite* land1;
	Sprite* land2;
};

#endif