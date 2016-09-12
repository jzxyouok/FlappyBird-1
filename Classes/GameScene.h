#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "BackgroundLayer.h"
#include "GameLayer.h"

USING_NS_CC;

class GameScene : public Scene
{
public:

	virtual bool init();

	CREATE_FUNC(GameScene);
private:

};

#endif