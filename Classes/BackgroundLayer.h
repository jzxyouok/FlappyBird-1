#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(BackgroundLayer);
};

#endif