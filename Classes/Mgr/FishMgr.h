#ifndef __FISHMGR_H__
#define __FISHMGR_H__

#include "cocos2d.h"
#include "Obj/FishInfo.h"
#include <string>
#include <map>
using namespace cocos2d;

class Fish;
class WaterWave;
class FishMgr
{
public:
	static FishMgr* Instance()
	{
		if(0 == m_pInstance)
		{
			m_pInstance = new FishMgr();
		}
		return m_pInstance;
	}
	void Init(CCLayer* layer);
	CCSpriteBatchNode* GetSpriteBatchNode();
	FishInfo* GetFishInfo(std::string name);
	void StoneInWater(WaterWave* waterWave);
	void CatchedFish(Fish* fish);
	void Clear();
	void Load(const char* fishList,const char* fishCount);
	void ThreatenAllFish();
private:
	CCLayer*							mGameLayer;
	std::map<std::string,FishInfo>		mFishInfoMap;
	CCArray*							mFishList;
	CCSpriteBatchNode*					mSpritebatch;
	static FishMgr*						m_pInstance;
	FishMgr(){}
};
inline CCSpriteBatchNode* FishMgr::GetSpriteBatchNode()
{
	return mSpritebatch;
}
inline FishInfo* FishMgr::GetFishInfo(std::string name)
{
	std::map<std::string,FishInfo>::iterator iter = mFishInfoMap.find(name);
	if(iter != mFishInfoMap.end())
		return &(iter->second);
	return NULL;
}

#endif