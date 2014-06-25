#ifndef __COINMGR_H__
#define __COINMGR_H__
#include "cocos2d.h"
using namespace cocos2d;
class Coin;
class Player;
class CoinMgr
{
public:
	static CoinMgr* Instance()
	{
		if(0 == m_pInstance)
		{
			m_pInstance = new CoinMgr();
		}
		return m_pInstance;
	}
	void Init(CCLayer* layer);
	int GetScore(const CCPoint& pos,int score);
	void DeleteCoin(Coin* coin);
	CCLayer* GetGameLayer();
private:
	Player*								mPlayer;
	CCLayer*							mGameLayer;
	CCSpriteBatchNode*					mGoldItemSpritebatch;
	static CoinMgr* m_pInstance;
	CoinMgr(){}

};
inline CCLayer* CoinMgr::GetGameLayer()
{
	return mGameLayer;
}

#endif