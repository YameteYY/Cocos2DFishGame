#ifndef _WATERWAVW_H__
#define _WATERWAVW_H__
#include "cocos2d.h"
using namespace cocos2d;


class WaterWave : public CCSprite
{
public:
	WaterWave(){}
	static WaterWave* create();
	void Play();
	void callbackMethod(float dt);
	
private:
	void _createAction();
	CCAction* mWaveAction;
};

#endif