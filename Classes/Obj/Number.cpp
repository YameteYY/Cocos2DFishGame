#include "Number.h"
#include "Mgr/NumFactory.h"
#include "Mgr/CoinMgr.h"
#include "Definition.h"

Number* Number::create(int number,const CCPoint& pos,bool withMulty /* = false */)
{
	Number* numberObj = new Number();

	if (numberObj && numberObj->init())
	{
		numberObj->autorelease();
	}

	numberObj->mNumberSprite = NumFactory::Instance()->GetScoreSprite(number,withMulty);

	CCPoint scorePos = pos;
	scorePos.x += GoldWidth/2+10;
	for(int i=0;i<numberObj->mNumberSprite->count();i++)
	{
		CCSprite* sprite = (CCSprite*)numberObj->mNumberSprite->objectAtIndex(i);
		sprite->setPosition(scorePos);
		CCActionInterval* moveby = CCMoveBy::create(0.5, ccp(0, 20));  
		sprite->runAction(moveby);
		scorePos.x += NumWidth;
	}
	numberObj->scheduleOnce(schedule_selector(Number::dead),1.0);
	
	CoinMgr::Instance()->GetGameLayer()->addChild(numberObj);

	return numberObj;
}
Number::~Number()
{

}
void Number::dead(float dt)
{
	NumFactory::Instance()->DeleteScore(mNumberSprite);
	mNumberSprite->removeAllObjects();
	mNumberSprite->release();
	CoinMgr::Instance()->GetGameLayer()->removeChild(this,true);
	this->cleanup();
}