#include "WaterWaveMgr.h"
#include "Obj/WaterWave.h"
#include "Obj/Player.h"
#include "Definition.h"
#include "FishMgr.h"
#include "SimpleAudioEngine.h"

WaterWaveMgr* WaterWaveMgr::m_pInstance = 0;

void WaterWaveMgr::Init(CCLayer* layer)
{
	mGameLayer = layer;
	std::string str1 = CCFileUtils::sharedFileUtils()->fullPathForFilename("waterwave/ripple.png");
	mSpritebatch = CCSpriteBatchNode::create(str1.c_str());
	layer->addChild(mSpritebatch,3);

	

	str1 = CCFileUtils::sharedFileUtils()->fullPathForFilename("bgm/bgm_fire.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(str1.c_str());
}
void WaterWaveMgr::PlayWaterWave(const CCPoint& pos,bool ignoreFish /* = false */)
{

	WaterWave* waterWave = WaterWave::create();
	mSpritebatch->addChild(waterWave);
	waterWave->scheduleOnce(schedule_selector(WaterWave::callbackMethod), 1.1f); 
	waterWave->Play();
	waterWave->setPosition(pos);

	std::string str1 = CCFileUtils::sharedFileUtils()->fullPathForFilename("bgm/bgm_fire.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(str1.c_str(),false);

	if(!ignoreFish)
		FishMgr::Instance()->StoneInWater(waterWave);
}
void WaterWaveMgr::EndWaterWave(WaterWave* wave)
{
	mSpritebatch->removeChild(wave,true);
}
void WaterWaveMgr::ScreenWave()
{
	for(int i=0;i<WaterCount;i++)
	{
		PlayWaterWave(ccp(((float)rand()/RAND_MAX) *SceneWidth,
			((float)rand()/RAND_MAX)*SceneWidth),true);
	}
}