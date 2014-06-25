#ifndef _NUMBER_H__
#define _NUMBER_H__
#include "cocos2d.h"
using namespace cocos2d;

class Number : public CCNode
{
public:
	Number(){}
	virtual ~Number(void);
	static Number* create(int number,const CCPoint& pos,bool withMulty = false);
	void dead(float dt);
private:
	CCArray* mNumberSprite;
};

#endif