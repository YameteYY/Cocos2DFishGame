#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"
#include "Mgr/UIMgr.h"
using namespace cocos2d;

struct  ThreatenInfo
{
	float mTimeScale;
	float mSpeedScale;
	float mRangeScale;
};
class MainFrame;
class Player : public CCSprite
{
public:
	static Player* Instance()
	{
		if(0 == m_pInstance)
		{
			m_pInstance = new Player();
		}
		return m_pInstance;
	}
	void initPlayer(CCLayer* gameLayer);
	void SetScore(int score);
	void AddScore(int addScore);
	bool DeleteScore(int deleteScore);
	ThreatenInfo* GetThreatenInfo();
	void SetThreatenInfo(ThreatenInfo waterWaveInfo);
	void SetCoinAddPoint(int point);
	int GetCoinAddPoint();
	void SetCoinDoublePoint(int point);
	int GetCoinDoublePoint();
	int GetScore();
	int* GetPointList();
	void SavePlayerData();
	void Tick(float dt);
private:
	int mPointList[5];
	int mLevel;
	int mExperience;
	int mNextLevelExperience;
	ThreatenInfo mThreatenInfo;
	Player(){}
	static Player* m_pInstance;
	CCLayer* mGameLayer;
	int mScore;
	int mCoinAddPoint;
	int mCoinDoublePoint;
	MainFrame* mMainFrame;
};
inline int* Player::GetPointList()
{
	return mPointList;
}
inline int Player::GetScore()
{
	return mScore;
}
inline void Player::SetCoinAddPoint(int point)
{
	mCoinAddPoint = point;
}
inline int Player::GetCoinAddPoint()
{
	return mCoinAddPoint;
}
inline void Player::SetCoinDoublePoint(int point)
{
	mCoinDoublePoint = point;
}
inline int Player::GetCoinDoublePoint()
{
	return mCoinDoublePoint;
}
inline ThreatenInfo* Player::GetThreatenInfo()
{
	return &mThreatenInfo;
}
inline void Player::SetThreatenInfo(ThreatenInfo waterWaveInfo)
{
	mThreatenInfo = waterWaveInfo;
}
#endif