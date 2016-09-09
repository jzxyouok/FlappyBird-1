#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

#include "WelcomeScene.h"

USING_NS_CC;

class LoadingLayer: public cocos2d::Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LoadingLayer);

	void loadingCallBack(Texture2D* texture);
};

#endif