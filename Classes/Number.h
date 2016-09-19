#ifndef __NUMBER_H__
#define __NUMBER_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

// 显示方式
typedef enum
{
	GRAVITY_CENTER = 1,
	GRAVITY_LEFT,
	GRAVITY_RIGHT
}Gravity;

class NumberSeries : public Object{
public:
	virtual bool init();

	CREATE_FUNC(NumberSeries);

	void loadNumber(const char *fmt, int base = 0);

	SpriteFrame* at(int index);
private:
	Vector<SpriteFrame*> numberSeries;
};

class Number
{
public:
	virtual bool init();

	virtual bool loadNumber(const char* name, const char* fmt, int base = 0);

	Node* convert(const char* name, int number, Gravity gravity = Gravity::GRAVITY_CENTER);

	static Number* getInstance();

	static void destroyInstance();
private:
	Map<string, NumberSeries*> numberContainer;

	static Number* sharedNumber;
};

#endif