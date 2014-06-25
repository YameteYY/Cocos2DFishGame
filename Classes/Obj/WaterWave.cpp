#include "WaterWave.h"
#include "Mgr/WaterWaveMgr.h"

WaterWave* WaterWave::create()
{
	WaterWave *waterwave = new WaterWave();
	waterwave->_createAction();
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("water_1.png");
	if(pFrame && waterwave && waterwave->initWithSpriteFrame(pFrame))
	{
		waterwave->autorelease();
		
		return waterwave;
	}
	return NULL;
}
void WaterWave::Play()
{
	this->stopAllActions();
	this->runAction(mWaveAction);
}
void WaterWave::_createAction()
{
	CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	spriteFrameCache->addSpriteFramesWithFile("waterwave/ripple.plist");

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();

	CCArray* animFrames = CCArray::createWithCapacity(11);
	char str[100] = {0};
	for(int i=1;i<= 11;i++)
	{
		sprintf(str,"water_%d.png",i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,0.1f);
	mWaveAction = CCRepeatForever::create(CCAnimate::create(animation));
	mWaveAction->retain();
}
void WaterWave::callbackMethod(float dt)
{
	mWaveAction->release();
	WaterWaveMgr::Instance()->EndWaterWave(this);
}