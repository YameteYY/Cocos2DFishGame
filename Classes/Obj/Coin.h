#ifndef __COIN_H__
#define __COIN_H__
#include "cocos2d.h"
using namespace cocos2d;
class Coin : public CCSprite
{
public:
	static Coin* create();
	Coin(){}
	void initCoin(int score,const CCPoint& pos);
private:
	void dead();
	CCParticleSystem* mStar;
};

#endif