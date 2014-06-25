#ifndef __LEVELMGR_H__
#define __LEVELMGR_H__
#include "cocos2d.h"
#include <vector>
using namespace cocos2d;

struct LevelInfo
{
	int level;
	char fishList[128];					//Ãû×Ö
	char fishCount[64];					//ÊýÁ¿
	int time;
	char music[64];
	char background[64];
};
class MainFrame;
class LevelMgr
{
public:
	static LevelMgr* Instance()
	{
		if(0 == m_pInstance)
		{
			m_pInstance = new LevelMgr();
		}
		return m_pInstance;
	}
	void Init(CCLayer* layer);
	void Load(int level);
	void NextLevel();
	void NextSecond(float dt);
	void ShowTime();
private:
	MainFrame*	 mMainFrame;
	CCLayer*     mGameLayer;
	int mCurLevel;
	std::vector<LevelInfo> mLevelInfoList;
	LevelMgr(){}
	static LevelMgr* m_pInstance;
	int mTime;
	int mLevelCount;
};
#endif