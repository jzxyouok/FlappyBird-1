#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "WelcomeScene.h"

USING_NS_CC;
using namespace CocosDenshion;

class LoadingLayer: public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LoadingLayer);

	void loadingCallBack(Texture2D* texture);
};

#endif