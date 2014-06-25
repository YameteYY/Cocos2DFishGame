#include "FishMgr.h"
#include "Obj/Fish.h"
#include "Mgr/CoinMgr.h"
#include "LevelMgr.h"
#include "Obj/Player.h"
#include "Obj/WaterWave.h"

FishMgr* FishMgr::m_pInstance = 0;

void FishMgr::Init(CCLayer* layer)
{
	std::string str1 = CCFileUtils::sharedFileUtils()->fullPathForFilename("fish/fish.png");
	mSpritebatch = CCSpriteBatchNode::create(str1.c_str());
	layer->addChild(mSpritebatch,2);
	mGameLayer = layer;
	/*
	spritebatch =  CCSpriteBatchNode::create("fish/fish2.png");
	layer.addChild(spritebatch);

	spritebatch =  CCSpriteBatchNode::create("fish/fish3.png");
	layer.addChild(spritebatch);*/

	CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	str1 = CCFileUtils::sharedFileUtils()->fullPathForFilename("fish/fish.plist");
	spriteFrameCache->addSpriteFramesWithFile(str1.c_str());
	//spriteFrameCache->addSpriteFramesWithFile("fish/fish2.plist");
	//spriteFrameCache->addSpriteFramesWithFile("fish/fish3.plist");

	//¶ÁfishInfo
	const char* testPlistPath = "fish/FishInfo.plist";
	str1 = CCFileUtils::sharedFileUtils()->fullPathForFilename(testPlistPath);
	CCDictionary* plistDic = CCDictionary::createWithContentsOfFile(str1.c_str());
	int fishCount = plistDic->count();
	char str[64] = {0};
	for(int i=1;i<=fishCount;i++)
	{
		sprintf(str,"fish%02d",i);
		CCDictionary* fishDic = dynamic_cast<CCDictionary*>(plistDic->objectForKey(str));
		FishInfo fishInfo;
		strcpy(fishInfo.name,str);
		fishInfo.fishRunSpeed = fishDic->valueForKey("fishRunSpeed")->intValue();
		fishInfo.worth = fishDic->valueForKey("worth")->intValue();
		fishInfo.runActs = fishDic->valueForKey("runActs")->intValue();
		fishInfo.catchedActs = fishDic->valueForKey("catchedActs")->intValue();
		fishInfo.theatenSpeedScale = fishDic->valueForKey("theatenSpeedScale")->floatValue();
		fishInfo.theatenTime = fishDic->valueForKey("theatenTime")->floatValue();

		mFishInfoMap.insert(std::map<std::string,FishInfo>::value_type(str,fishInfo));
	}
	mFishList = NULL;
}
void FishMgr::StoneInWater(WaterWave* waterWave)
{
	const CCPoint& pos = waterWave->getPosition();
	int fishCount = mFishList->count();
	for(int i=0;i<fishCount;i++)
	{
		Fish* fish = (Fish*)mFishList->objectAtIndex(i);
		CCRect fishRect;
		const CCSize& size = fish->getContentSize();
		const CCPoint& fishPos = fish->getPosition();
		fishRect.origin = fishPos - size*0.5;
		fishRect.size = size;
		float length = (fishPos - pos).getLength();
		float scale = -1;
		length /= Player::Instance()->GetThreatenInfo()->mRangeScale;
		if(length < ThreatenMaxDistance )
		{
			scale = 1.0f - length/ThreatenMaxDistance;
		}
		if(scale > 0)
		{
			fish->ThreatenFish(pos,scale);
		}
	}
}
void FishMgr::CatchedFish(Fish* fish)
{
	int score = CoinMgr::Instance()->GetScore(fish->getPosition(),fish->GetFishInfo()->worth);
	mFishList->removeObject(fish,true);
	mSpritebatch->removeChild(fish,true);
	Player::Instance()->AddScore(score);
	fish->Clear();

	if(mFishList->count() == 0)
	{
		LevelMgr::Instance()->NextLevel();
		Player::Instance()->AddScore(100);
	}
}
void FishMgr::Clear()
{
	int fishCount = mFishList->count();
	for(int i=0;i<fishCount;i++)
	{
		Fish* fish = (Fish*)mFishList->objectAtIndex(i);
		fish->Clear();
	}
	mSpritebatch->removeAllChildren();
	mFishList->removeAllObjects();
	mFishList->release();
}
void FishMgr::Load(const char* fishList,const char* fishCount)
{
	if(mFishList != NULL)
	{
		Clear();
	}
	
	int fishListLen = strlen(fishList);
	int fishCountLen = strlen(fishCount);
	int i = 0;
	int j =0;
	int tempFish = 0;
	std::vector<int> fishCountList;
	fishCountList.clear();
	while(i < fishCountLen)
	{
		if(fishCount[i] == ';')
		{
			fishCountList.push_back(tempFish);
			tempFish = 0;
			i++;
			continue;
		}
		tempFish = tempFish *10 + fishCount[i] - '0';
		i++;
	}
	fishCountList.push_back(tempFish);
	tempFish = 0;
	for(i = 0;i<fishCountList.size();i++)
	{
		tempFish += fishCountList[i];
	}
	mFishList = CCArray::createWithCapacity(tempFish);
	int k=0;
	for (i = 0;i<fishCountList.size();i++)
	{
		j = k;
		char fishStr[64];
		int p =0;
		while(j < fishListLen && fishList[j] != ';')
		{
			fishStr[p++] = fishList[j];
			j++;
		}
		k = j+1;
		fishStr[p] = '\0';

		FishInfo* fishinfo = GetFishInfo(fishStr);
		if(fishinfo == NULL)
		{
			CCLOG("error fish!!!");
			continue;
		}
		for(p=0;p<fishCountList[i];p++)
		{
			Fish* fish = Fish::create(fishinfo);
			fish->initFish();
			mSpritebatch->addChild(fish);
			fish->run();
			mFishList->addObject(fish);
		}
	}
	mFishList->retain();
}
void FishMgr::ThreatenAllFish()
{
	int fishCount = mFishList->count();
	for(int i=0;i<fishCount;i++)
	{
		Fish* fish = (Fish*)mFishList->objectAtIndex(i);
		fish->ChangeFishState(Threaten);
	}
}