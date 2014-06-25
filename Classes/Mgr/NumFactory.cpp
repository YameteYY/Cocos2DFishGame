#include "NumFactory.h"

NumFactory* NumFactory::m_pInstance = 0;
void NumFactory::Init(CCLayer* layer)
{	
	std::string str1 = CCFileUtils::sharedFileUtils()->fullPathForFilename("score/num_gold.png");
	mNumGoldSpritebatch = CCSpriteBatchNode::create(str1.c_str());
	layer->addChild(mNumGoldSpritebatch,901);
	
	CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	str1 = CCFileUtils::sharedFileUtils()->fullPathForFilename("score/num_gold.plist");
	spriteFrameCache->addSpriteFramesWithFile(str1.c_str());
}
CCArray* NumFactory::GetScoreSprite(int score,bool withMulty /* = false */)
{
	char str[100]={0};
	sprintf(str,"%d",score);
	int len = strlen(str);
	CCArray* numArray = CCArray::createWithCapacity(len);
	CCSpriteFrame *pFrame;
	CCSprite* sprite;
	if(withMulty)
	{
		CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("multy.png");
		sprite = CCSprite::createWithSpriteFrame(pFrame);
		mNumGoldSpritebatch->addChild(sprite);
		numArray->addObject(sprite);
	}
	for(int i=0;i<len;i++)
	{
		char str1[100] = {0};
		sprintf(str1,"num_%c.png",str[i]);
		pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str1);
		sprite = CCSprite::createWithSpriteFrame(pFrame);
		mNumGoldSpritebatch->addChild(sprite);
		numArray->addObject(sprite);
	}
	numArray->retain();
	return numArray;
}
void NumFactory::DeleteScore(CCArray* scoreArray)
{
	for(int i=0;i<scoreArray->count();i++)
	{
		CCSprite* sprite = (CCSprite*)scoreArray->objectAtIndex(i);
		mNumGoldSpritebatch->removeChild(sprite,true);
	}
}