#ifndef _WATERWAVEMGR_H__
#define _WATERWAVEMGR_H__
#include "cocos2d.h"
using namespace cocos2d;
class WaterWave;
class WaterWaveMgr
{
public:
	static WaterWaveMgr* Instance()
	{
		if(0 == m_pInstance)
		{
			m_pInstance = new WaterWaveMgr();
		}
		return m_pInstance;
	}
	void Init(CCLayer* layer);
	CCAction* GetWaveAction();
	void PlayWaterWave(const CCPoint& pos,bool ignoreFish = false);
	void EndWaterWave(WaterWave* wave);
	void ScreenWave();
private:
	CCLayer*  mGameLayer;
	static WaterWaveMgr* m_pInstance;
	WaterWaveMgr(){}
	CCSpriteBatchNode* mSpritebatch;
};


#endif