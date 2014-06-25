#ifndef __DEFINITION_H__
#define __DEFINITION_H__

const float SceneWidth = 800;
const float SceneHeight = 480;
const int   WaterCount = 50;
const int   GoldWidth = 38;
const int   NumWidth = 12;
const int   GoldSpeed = 300;
const int   UILayerID = 900;

const float ThreatenMaxDistance = 80;

const int   FishRotateActionFlag = 101;
const int	ThreatenButtonTag    = 103;
const int   GoldNumTag			 = 104;
const int   TimeNumTag			 = 105;
const int   AddSkillTag			 = 106;
const int	ExperienceTag        = 107;
const int	LevelTag			 = 108;
const int	SkillCancelTag		 = 207;
const int	SkillGoldNumTag		 = 220;
const int	RangePointTag		 = 221;
const int	TimePointTag		 = 222;
const int	SpeedPointTag        = 223;
const int	CoinAddPointTag      = 224;
const int	CoinDoublePointTag   = 225;

const int   TotalPoint[5]        = {10,10,10,20,100};
const int   GoldNeed[5]			 = {1000,1000,1000,2000,5000};


#define    RAND_LIMIT    32767

#define SaveStringToXML CCUserDefault::sharedUserDefault()->setStringForKey

#define SaveIntegerToXML CCUserDefault::sharedUserDefault()->setIntegerForKey

#define SaveBooleanToXML CCUserDefault::sharedUserDefault()->setBoolForKey

#define LoadStringFromXML CCUserDefault::sharedUserDefault()->getStringForKey

#define LoadIntegerFromXML CCUserDefault::sharedUserDefault()->getIntegerForKey

#define LoadBooleanFromXML CCUserDefault::sharedUserDefault()->getBoolForKey


inline float RandomFloat(float lo, float hi)
{
	float r = (float)(std::rand() & (RAND_LIMIT));
	r /= RAND_LIMIT;
	r = (hi - lo) * r + lo;
	return r;
}
inline int GetTotalExperience(int level)
{
	if(level < 9)
		return 200 + level*100;
	if(level < 19)
		return level*200;
	if(level < 29)
		return level*300;
	if(level < 39)
		return level*400;
	return level*500;
}
#define min(a,b)            (((a) < (b)) ? (a) : (b))

#endif
