#include "Fish.h"
#include "Mgr/FishMgr.h"
#include "Mgr/NetMgr.h"
#include "Definition.h"
#include "Player.h"


Fish* Fish::create(FishInfo* fishInfo)
{
	char str[100] = {0};
	sprintf(str,"%s_01.png",fishInfo->name);
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);

	Fish *fish = new Fish();
	fish->mFishInfo = fishInfo;
	if(pFrame && fish && fish->initWithSpriteFrame(pFrame))
	{
		fish->autorelease();
		return fish;
	}
	return NULL;
}
void Fish::initFish()
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();

	CCArray* animFrames = CCArray::createWithCapacity(mFishInfo->catchedActs);
	char str[100] = {0};
	for(int i=1;i<= mFishInfo->catchedActs;i++)
	{
		sprintf(str,"%s_catch_%02d.png",mFishInfo->name,i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,0.1f);
	mCatchedAct = CCRepeatForever::create(CCAnimate::create(animation));
	mCatchedAct->retain();
	animFrames = CCArray::createWithCapacity(mFishInfo->runActs);
	for(int i=1;i<= mFishInfo->runActs;i++)
	{
		sprintf(str,"%s_%02d.png",mFishInfo->name,i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}

	animation = CCAnimation::createWithSpriteFrames(animFrames,0.1f);
	mRunAct = CCRepeatForever::create(CCAnimate::create(animation));
	mRunAct->retain();


	this->scheduleUpdate();

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCPoint pos;
	while(1)
	{
		pos = ccp(((float)rand()/RAND_MAX) *(visibleSize.width-m_obContentSize.width)+m_obContentSize.width/2,
			((float)rand()/RAND_MAX)*(visibleSize.height-m_obContentSize.height)+m_obContentSize.height/2);

		setPosition(pos);
		mRotated = rand()%360;
		setRotation(mRotated);

		if(!NetMgr::Instance()->GetNetRect().intersectsRect(this->boundingBox()))
			break;
	}
	
	
	mSpeed = ccp(-cos(-CC_DEGREES_TO_RADIANS((float)mRotated)),-sin(-CC_DEGREES_TO_RADIANS((float)mRotated)));
	mFishState = Run;
	mStayTime = 1.0f;
	mRotatedTime = 2.0f;
	mSpeedScale = 1.0f;
	mScheduled = false;
	mIntheNet = false;
}
void Fish::run()
{
	this->runAction(mRunAct);
}
void Fish::beCatched()
{
	this->runAction(mCatchedAct);
}
void Fish::rotated(float dt)
{
	this->stopActionByTag(FishRotateActionFlag);
	CCActionInterval* rotatedTo = CCRotateTo::create(mRotatedTime,mRotated);
	rotatedTo->setTag(FishRotateActionFlag);
	this->runAction(rotatedTo);
	this->unschedule(schedule_selector(Fish::rotatedEnd));
	this->scheduleOnce(schedule_selector(Fish::rotatedEnd),mRotatedTime);
}
void Fish::update(float dt)
{
	if(mScheduled)
		return;
	
	CCPoint endPos = m_obPosition + mSpeed*mSpeedScale*dt*mFishInfo->fishRunSpeed;
	if(endPos.x + m_obContentSize.width/2 > SceneWidth)
	{
		mRotated = RandomFloat(-90.0f,90.0f);
		mSpeed = ccp(-cos(-CC_DEGREES_TO_RADIANS(mRotated)),-sin(-CC_DEGREES_TO_RADIANS(mRotated)));
		mScheduled = true;
		this->unschedule(schedule_selector(Fish::rotatedEnd));
		this->unschedule(schedule_selector(Fish::rotated));
		this->scheduleOnce(schedule_selector(Fish::rotated),mStayTime);
	}
	else if(endPos.x - m_obContentSize.width/2 < 0)
	{
		mRotated = RandomFloat(90.0f,270.0f);
		mSpeed = ccp(-cos(-CC_DEGREES_TO_RADIANS(mRotated)),-sin(-CC_DEGREES_TO_RADIANS(mRotated)));
		mScheduled = true;
		this->unschedule(schedule_selector(Fish::rotatedEnd));
		this->unschedule(schedule_selector(Fish::rotated));
		this->scheduleOnce(schedule_selector(Fish::rotated),mStayTime);
	}
	else  if(endPos.y - m_obContentSize.height/2 < 0)
	{
		mRotated = RandomFloat(0.0f,180.0f);
		mSpeed = ccp(-cos(-CC_DEGREES_TO_RADIANS(mRotated)),-sin(-CC_DEGREES_TO_RADIANS(mRotated)));
		mScheduled = true;
		this->unschedule(schedule_selector(Fish::rotatedEnd));
		this->unschedule(schedule_selector(Fish::rotated));
		this->scheduleOnce(schedule_selector(Fish::rotated),mStayTime);
	}
	else  if(endPos.y + m_obContentSize.height/2 > SceneHeight)
	{
		mRotated = RandomFloat(180.0f,360.0f);
		mSpeed = ccp(-cos(-CC_DEGREES_TO_RADIANS(mRotated)),-sin(-CC_DEGREES_TO_RADIANS(mRotated)));
		mScheduled = true;
		this->unschedule(schedule_selector(Fish::rotatedEnd));
		this->unschedule(schedule_selector(Fish::rotated));
		this->scheduleOnce(schedule_selector(Fish::rotated),mStayTime);
	}
	else
	{
		CCRect fishRect = this->boundingBox();
		fishRect.origin = fishRect.origin + mSpeed*dt*mFishInfo->fishRunSpeed;
		if(mFishState == Threaten)
		{
			if(NetMgr::Instance()->GetNetCatchedRect().containsPoint(endPos))
			{
				ChangeFishState(Catched,mRotated);
				mScheduled = true;
				return;
			}
		}
		else  if(NetMgr::Instance()->GetNetRect().intersectsRect(fishRect))
		{
			if(!mIntheNet)
			{
				mIntheNet = true;
				mRotated += 180;
				mSpeed = ccp(-cos(-CC_DEGREES_TO_RADIANS(mRotated)),-sin(-CC_DEGREES_TO_RADIANS(mRotated)));
				mScheduled = true;
				this->unschedule(schedule_selector(Fish::rotatedEnd));
				this->unschedule(schedule_selector(Fish::rotated));
				this->scheduleOnce(schedule_selector(Fish::rotated),mStayTime);
				return;
			}
		}
		else
		{
			mIntheNet = false;
		}
		this->setPosition(endPos);
	}
}
void Fish::rotatedEnd(float dt)
{
	if(mScheduled == false)
		CCLOG("error");
	mScheduled = false;
}
void Fish::ThreatenFish(const CCPoint& pos,float scale)
{
	CCPoint dir = this->getPosition() - pos;
	float roatedAngle = dir.getAngle();
	roatedAngle = 180.0 - CC_RADIANS_TO_DEGREES(roatedAngle);

	mRotated = roatedAngle;
	ThreatenInfo* info = Player::Instance()->GetThreatenInfo();
	mSpeedScale = mFishInfo->theatenSpeedScale * scale * info->mSpeedScale;
	mSpeed = ccp(-cos(-CC_DEGREES_TO_RADIANS((float)mRotated)),-sin(-CC_DEGREES_TO_RADIANS((float)mRotated)));
	mStayTime = 0.1f;
	mRotatedTime = 0.2f;
	this->unschedule(schedule_selector(Fish::rotatedEnd));
	this->unschedule(schedule_selector(Fish::rotated));
	rotated(0);
	this->unschedule(schedule_selector(Fish::ThreatenEnd));
	this->scheduleOnce(schedule_selector(Fish::ThreatenEnd),mFishInfo->theatenTime*scale*info->mTimeScale);
	mScheduled = true;
	mFishState = Threaten;
}
void Fish::ChangeFishState(FishState fishState)
{
	ChangeFishState(fishState,mRotated);
}
void Fish::ChangeFishState(FishState fishState,float rotatedAngle)
{
	if(mFishState == Catched)
		return;
	mRotated = rotatedAngle;
	switch(fishState)
	{
	case Run:
		mSpeedScale = 1.0f;
		mStayTime = 1.0f;
		mRotatedTime = 2.0f;
		break;
	case Threaten:
		mSpeedScale = mFishInfo->theatenSpeedScale;
		mSpeed = ccp(-cos(-CC_DEGREES_TO_RADIANS((float)mRotated)),-sin(-CC_DEGREES_TO_RADIANS((float)mRotated)));
		mStayTime = 0.1f;
		mRotatedTime = 0.2f;
		this->unschedule(schedule_selector(Fish::rotatedEnd));
		this->unschedule(schedule_selector(Fish::rotated));
		rotated(0);
		this->unschedule(schedule_selector(Fish::ThreatenEnd));
		this->scheduleOnce(schedule_selector(Fish::ThreatenEnd),mFishInfo->theatenTime);
		mScheduled = true;
		break;
	case Catched:
		mSpeed.x = 0;
		mSpeed.y = 0;
		this->unscheduleAllSelectors();
		this->stopAction(mRunAct);
		this->runAction(mCatchedAct);
		this->scheduleOnce(schedule_selector(Fish::over),1.0f);
		break;
	}
	this->mFishState = fishState;
}
void Fish::ThreatenEnd(float dt)
{
	ChangeFishState(Run,mRotated);
}
void Fish::over(float dt)
{
	FishMgr::Instance()->CatchedFish(this);
}
void Fish::Clear()
{
	mCatchedAct->release();
	mRunAct->release();
	cleanup();
}