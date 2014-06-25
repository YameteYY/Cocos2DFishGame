#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__
#include "cocos2d.h"
using namespace cocos2d;

class BackGround : public CCSprite
{
public:
	BackGround(){}
	static BackGround* create(const char* name);

};


#endif