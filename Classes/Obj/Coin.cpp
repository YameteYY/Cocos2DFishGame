#include "Coin.h"
#include "Mgr/NumFactory.h"
#include "Mgr/CoinMgr.h"
#include "Definition.h"

Coin* Coin::create()
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gold01.png");

	Coin *coin = new Coin();

	if(pFrame && coin && coin->initWithSpriteFrame(pFrame))
	{
		coin->autorelease();
		return coin;
	}
	return NULL;
}
void Coin::initCoin(int score,const CCPoint& pos)
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();

	CCArray* animFrames = CCArray::createWithCapacity(9);
	char str[100] = {0};
	for(int i=1;i<= 9;i++)
	{
		sprintf(str,"gold%02d.png",i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,0.05f);
	CCAction* action = CCRepeatForever::create(CCAnimate::create(animation));
	this->runAction(action);
	this->setPosition(pos);

	float runTime = (pos - ccp(SceneWidth/2.0f, 0)).getLength()/GoldSpeed;

	CCFiniteTimeAction *forward =  CCSequence::create(
		CCMoveTo::create(runTime, ccp(SceneWidth/2.0f, 0)),
		CCCallFunc::create(this,callfunc_selector(Coin::dead)),  
		NULL
		);
	
	this->runAction(forward);

	mStar = CCParticleSun::createWithTotalParticles(100);
	mStar->setLife(0.2);
	mStar->setStartColor(ccc4f(1,1,1,1));
	mStar->setEndColor(ccc4f(1,1,1,0));
	mStar->setEndSize(0);
	mStar->setTexture(CCTextureCache::sharedTextureCache()->addImage("fish/tenstar.png"));
	CoinMgr::Instance()->GetGameLayer()->addChild(mStar,100);
	mStar->setPosition(m_obPosition);

	forward = CCMoveTo::create(runTime, ccp(SceneWidth/2.0f, 0));  
	mStar->runAction(forward);

}
void Coin::dead()
{
	CoinMgr::Instance()->GetGameLayer()->removeChild(mStar,true);
	mStar->removeAllChildrenWithCleanup(true);
	mStar->cleanup();
	CoinMgr::Instance()->DeleteCoin(this);
}