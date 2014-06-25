#include "Player.h"
#include "Definition.h"
#include "Mgr/UIMgr.h"
#include "Mgr/FishMgr.h"
#include "Mgr/WaterWaveMgr.h"
#include "Ui/MainFrame.h"


Player* Player::m_pInstance = 0;
void Player::initPlayer(CCLayer* gameLayer)
{
	mGameLayer = gameLayer;
	mThreatenInfo.mRangeScale = 1.0f;
	mThreatenInfo.mSpeedScale = 1.0f;
	mThreatenInfo.mTimeScale = 1.0f;
	mCoinAddPoint = 0;
	mCoinDoublePoint = 0;
	mLevel = 0;
	mExperience = 0;
	mScore = 20000;
	mPointList[0] = 0;
	mPointList[1] = 0;
	mPointList[2] = 0;
	mPointList[3] = 0;
	mPointList[4] = 0;

	
	/*
	const char* testPlistPath = "player/player.plist";
	std::string str1 = CCFileUtils::sharedFileUtils()->fullPathForFilename(testPlistPath);
	CCDictionary* plistDic = CCDictionary::createWithContentsOfFile(str1.c_str());
	char str[64] = {0};
	mLevel = plistDic->valueForKey("level")->intValue();
	mExperience = plistDic->valueForKey("experience")->intValue();
	mScore = plistDic->valueForKey("coin")->intValue();
	mPointList[0] = plistDic->valueForKey("rangePoint")->intValue();
	mPointList[1] = plistDic->valueForKey("timePoint")->intValue();
	mPointList[2] = plistDic->valueForKey("speedPoint")->intValue();
	mPointList[3] = plistDic->valueForKey("addCoinPoint")->intValue();
	mPointList[4] = plistDic->valueForKey("doubleCoinPoint")->intValue();*/

	mLevel = LoadIntegerFromXML("level",mLevel);
	mExperience = LoadIntegerFromXML("experience",mExperience);
	mScore = LoadIntegerFromXML("coin",mScore);
	mPointList[0] = LoadIntegerFromXML("rangePoint",mPointList[0]);
	mPointList[1] = LoadIntegerFromXML("timePoint",mPointList[1]);
	mPointList[2] = LoadIntegerFromXML("speedPoint",mPointList[2]);
	mPointList[3] = LoadIntegerFromXML("addCoinPoint",mPointList[3]);
	mPointList[4] = LoadIntegerFromXML("doubleCoinPoint",mPointList[4]);

	mNextLevelExperience = GetTotalExperience(mLevel);
	mMainFrame = UIMgr::Instance()->GetMainFrame();
	mMainFrame->SetLevel(mLevel);
	mMainFrame->SetExperience(100*mExperience/GetTotalExperience(mLevel));
	mThreatenInfo.mRangeScale = 1.0f + 0.1*mPointList[0];
	mThreatenInfo.mTimeScale = 1.0f + 0.1*mPointList[1];
	mThreatenInfo.mSpeedScale = 1.0f + 0.1*mPointList[2];
	SetCoinAddPoint(mPointList[3]);
	SetCoinDoublePoint(mPointList[4]);
	SetScore(mScore);

	mGameLayer->schedule(schedule_selector(Player::Tick), 5.0f);
}
void Player::Tick(float dt)
{
	SaveIntegerToXML("level",m_pInstance->mLevel);
	SaveIntegerToXML("experience",m_pInstance->mExperience);
	SaveIntegerToXML("coin",m_pInstance->mScore);
	CCUserDefault::sharedUserDefault()->flush();
}
void Player::SetScore(int score)
{
	mMainFrame->SetScore(score);
	mScore = score;
}
void Player::SavePlayerData()
{
	SaveIntegerToXML("level",mLevel);
	SaveIntegerToXML("experience",mExperience);
	SaveIntegerToXML("coin",mScore);
	SaveIntegerToXML("rangePoint",mPointList[0]);
	SaveIntegerToXML("timePoint",mPointList[1]);
	SaveIntegerToXML("speedPoint",mPointList[2]);
	SaveIntegerToXML("addCoinPoint",mPointList[3]);
	SaveIntegerToXML("doubleCoinPoint",mPointList[4]);
	CCUserDefault::sharedUserDefault()->flush();
}
void Player::AddScore(int addScore)
{
	mScore += addScore;
	SetScore(mScore);
	mExperience += addScore;
	while( mExperience >= mNextLevelExperience)
	{
		mExperience -= mNextLevelExperience;
		mLevel ++;
		mNextLevelExperience = GetTotalExperience(mLevel);
		mMainFrame->SetLevel(mLevel);
	}
	mMainFrame->SetExperience(100*mExperience/GetTotalExperience(mLevel));
}
bool Player::DeleteScore(int deleteScore)
{
	if(mScore < deleteScore)
		return false;
	mScore -= deleteScore;
	SetScore(mScore);
	return true;
}