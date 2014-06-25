#include "CoinMgr.h"
#include "Obj/Coin.h"
#include "SimpleAudioEngine.h"
#include "Obj/Player.h"
#include "Definition.h"
#include "Obj/Number.h"
CoinMgr* CoinMgr::m_pInstance = 0;

void CoinMgr::Init(CCLayer* layer)
{
	mGameLayer = layer;
	std::string str = CCFileUtils::sharedFileUtils()->fullPathForFilename("score/goldItem.png");
	mGoldItemSpritebatch = CCSpriteBatchNode::create(str.c_str());
	layer->addChild(mGoldItemSpritebatch,101);

	CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	str = CCFileUtils::sharedFileUtils()->fullPathForFilename("score/goldItem.plist");
	spriteFrameCache->addSpriteFramesWithFile(str.c_str());
	str = CCFileUtils::sharedFileUtils()->fullPathForFilename("bgm/coinanimate.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(str.c_str());
	mPlayer = Player::Instance();
}
int CoinMgr::GetScore(const CCPoint& pos,int score)
{
	score += (int)(mPlayer->GetCoinAddPoint()/5);
	Coin* coin = Coin::create();
	bool doubleFlag = false;
	if(rand()%100 < mPlayer->GetCoinDoublePoint())
	{
		score *= 2;
		doubleFlag = true;
	}
	coin->initCoin(score,pos);

	Number* number = Number::create(score,pos,true);

	number->scheduleOnce(schedule_selector(Number::dead),0.6);

	mGoldItemSpritebatch->addChild(coin);
	std::string str = CCFileUtils::sharedFileUtils()->fullPathForFilename("bgm/coinanimate.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(str.c_str(),false);

	return score;
}
void CoinMgr::DeleteCoin(Coin* coin)
{
	mGoldItemSpritebatch->removeChild(coin,true);
}
