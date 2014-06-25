#include "BackgroundMgr.h"
#include "Definition.h"
BackGroundMgr* BackGroundMgr::m_pInstance = 0;

void BackGroundMgr::Init(CCLayer* layer)
{
	mGameLayer = layer;
	CCTextureCache* cache = CCTextureCache::sharedTextureCache();
	std::string str = CCFileUtils::sharedFileUtils()->fullPathForFilename("bg\\fishlightbg_2.jpg");
	cache->addImage(str.c_str());
	str = CCFileUtils::sharedFileUtils()->fullPathForFilename("bg\\fishlightbg_1.jpg");
	cache->addImage(str.c_str());
	str = CCFileUtils::sharedFileUtils()->fullPathForFilename("bg\\fishlightbg_0.jpg");
	cache->addImage(str.c_str());

	cache->addImageAsync("bg/fishlightbg_3.jpg",mGameLayer,NULL);
	cache->addImageAsync("bg/fishlightbg_4.jpg",mGameLayer,NULL);
	cache->addImageAsync("bg/fishlightbg_5.jpg",mGameLayer,NULL);
	cache->addImageAsync("bg/fishlightbg_6.jpg",mGameLayer,NULL);
	
	mSprite = NULL;
}
void BackGroundMgr::Load(int level)
{
	if(mSprite != NULL)
	{
		mGameLayer->removeChild(mSprite);
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	char str[64];
	sprintf(str,"bg/fishlightbg_%d.jpg",level);
	std::string str1 = CCFileUtils::sharedFileUtils()->fullPathForFilename(str);
	CCTexture2D* texure = CCTextureCache::sharedTextureCache()->addImage(str1.c_str());
	mSprite = CCSprite::createWithTexture(texure);
	const CCSize& size = mSprite->getContentSize();
	float scale_Y = winSize.width/size.width;
	float scale_X = winSize.height/size.height;
	mSprite->setScaleX(scale_X);
	mSprite->setScaleY(scale_Y);
	mSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
	mGameLayer->addChild(mSprite,0);
}
void BackGroundMgr::ScreenWave()
{
	//CCActionInterval * waves = CCRipple3D::create(10,ccp(100,100),mSprite->getPosition(),10,2,2);
	//mSprite->runAction(waves);
}