#include "PlayScene.h"
#include "Mgr/FishMgr.h"
#include "Mgr/BackgroundMgr.h"
#include "Mgr/WaterWaveMgr.h"
#include "Mgr/NetMgr.h"
#include "Mgr/CoinMgr.h"
#include "Mgr/NumFactory.h"
#include "Obj/Player.h"
#include "Mgr/LevelMgr.h"
#include "Mgr/UIMgr.h"
#include "SimpleAudioEngine.h"
#include "Definition.h"

CCScene* PlayScene::scene()
{
	CCScene* scene = CCScene::create();

	PlayScene* layer = PlayScene::create();

	scene->addChild(layer);

	return scene;
}
bool PlayScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	UIMgr::Instance()->Init(this);
	BackGroundMgr::Instance()->Init(this);
	WaterWaveMgr::Instance()->Init(this);
	NetMgr::Instance()->Init(this);
	NetMgr::Instance()->CreateNet(ccp(visibleSize.width/2,0),ccp(visibleSize.width/2,visibleSize.height));
	FishMgr::Instance()->Init(this);
	CoinMgr::Instance()->Init(this);
	NumFactory::Instance()->Init(this);
	Player::Instance()->initPlayer(this);
	LevelMgr::Instance()->Init(this);
	LevelMgr::Instance()->Load(0);
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
	schedule(schedule_selector(LevelMgr::NextSecond), 1.0f);
	// ÉèÖÃÄ¬ÈÏÒôÁ¿
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);

	
	return true;
}
bool PlayScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(Player::Instance()->GetScore() < 5)
		return true;
	Player::Instance()->DeleteScore(5);
	WaterWaveMgr::Instance()->PlayWaterWave(pTouch->getLocation());
	return true;
}
