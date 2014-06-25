#ifndef __FISH_H__
#define __FISH_H__
#include "cocos2d.h"
#include "FishInfo.h"
#include "Definition.h"

using namespace cocos2d;
enum FishState
{
	Run,
	Threaten,
	Catched
};
class Fish : public CCSprite
{
public:
	Fish(){}
	static Fish* create(FishInfo* fishInfo);
	void initFish();
	void run();
	void beCatched();
	void update(float dt);
	void ChangeFishState(FishState fishState,float rotatedAngle);
	void ChangeFishState(FishState fishState);
	void ThreatenFish(const CCPoint& pos,float scale);
	const FishInfo* GetFishInfo()const;
	void Clear(void);
private:
	bool	  mScheduled;
	void rotatedEnd(float dt);
	void over(float dt);
	void rotated(float dt);
	void ThreatenEnd(float dt);
	FishInfo* mFishInfo;
	CCAction* mRunAct;
	CCAction* mCatchedAct;
	CCPoint   mSpeed;
	float     mSpeedScale;
	float     mRotated;
	float     mStayTime;
	float     mRotatedTime;
	FishState mFishState;
	bool      mIntheNet;
};
inline const FishInfo* Fish::GetFishInfo()const
{
	return mFishInfo;
}

#endif