#ifndef __BACKGROUNDMGR_H__
#define __BACKGROUNDMGR_H__

#include "cocos2d.h"
using namespace cocos2d;
class BackGroundMgr
{
public:
	static BackGroundMgr* Instance()
	{
		if(0 == m_pInstance)
		{
			m_pInstance = new BackGroundMgr();
		}
		return m_pInstance;
	}
	CCSprite* GetBackGround();
	void Init(CCLayer* layer);
	void Load(int level);
	void ScreenWave();
private:
	CCLayer*  mGameLayer;
	static BackGroundMgr* m_pInstance;
	CCSprite* mSprite;
	BackGroundMgr(){}
};

inline CCSprite* BackGroundMgr::GetBackGround()
{
	return mSprite;
}


#endif