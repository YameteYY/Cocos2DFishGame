#include "LevelMgr.h"
#include "FishMgr.h"
#include "BackgroundMgr.h"
#include "SimpleAudioEngine.h"
#include "NumFactory.h"
#include "Definition.h"
#include "Mgr/UIMgr.h"
#include "Ui/MainFrame.h"

LevelMgr* LevelMgr::m_pInstance = 0;
void LevelMgr::Init(CCLayer* layer)
{
	mGameLayer = layer;
	//¶ÁfishInfo
	const char* testPlistPath = "fish/GamePart.plist";
	std::string str1 = CCFileUtils::sharedFileUtils()->fullPathForFilename(testPlistPath);
	CCDictionary* plistDic = CCDictionary::createWithContentsOfFile(str1.c_str());
	mLevelCount = plistDic->count();
	char str[64] = {0};
	for(int i=1;i<=mLevelCount;i++)
	{
		sprintf(str,"level%d",i);
		CCDictionary* levelDic = dynamic_cast<CCDictionary*>(plistDic->objectForKey(str));
		LevelInfo levelInfo;
		strcpy(levelInfo.fishList,levelDic->valueForKey("fish")->getCString());
		strcpy(levelInfo.fishCount,levelDic->valueForKey("fishCount")->getCString());
		levelInfo.time = levelDic->valueForKey("time")->intValue();
		strcpy(levelInfo.music,levelDic->valueForKey("bgMusic")->getCString());
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(levelInfo.music); 
		strcpy(levelInfo.background,levelDic->valueForKey("background")->getCString());
		mLevelInfoList.push_back(levelInfo);
	}
	mMainFrame = UIMgr::Instance()->GetMainFrame();
	// Ô¤¼ÓÔØÒôÀÖºÍÒôÐ§ 
}
void LevelMgr::Load(int level)
{
	mCurLevel = level;
	FishMgr::Instance()->Load(mLevelInfoList[mCurLevel].fishList,mLevelInfoList[mCurLevel].fishCount);
	BackGroundMgr::Instance()->Load(mCurLevel);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(mLevelInfoList[mCurLevel].music,true);
	mTime = mLevelInfoList[mCurLevel].time;
	ShowTime();
}
void LevelMgr::NextLevel()
{
	mCurLevel++;
	mCurLevel %= mLevelCount;
	FishMgr::Instance()->Load(mLevelInfoList[mCurLevel].fishList,mLevelInfoList[mCurLevel].fishCount);
	BackGroundMgr::Instance()->Load(mCurLevel);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(mLevelInfoList[mCurLevel].music,true);

	mTime = mLevelInfoList[mCurLevel].time;
	ShowTime();
}
void LevelMgr::ShowTime()
{
	mMainFrame->SetTime(mTime);
}
void LevelMgr::NextSecond(float dt)
{
	m_pInstance->mTime --;
	if(m_pInstance->mTime < 0)
	{
		m_pInstance->NextLevel();
	}
	else
	{
		m_pInstance->ShowTime();
	}
}