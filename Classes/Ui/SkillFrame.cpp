#include "SkillFrame.h"
#include "Definition.h"
#include "Obj/Player.h"
#include "Ui/PopupLayer.h"

SkillFrame* SkillFrame::create()
{
	SkillFrame *pRet = new SkillFrame();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}
void SkillFrame::Init()
{
	mSkillUILayout =  static_cast<ui::Layout*>(GUIReader::shareReader()->widgetFromJsonFile("SkillFrame/SkillFrame.ExportJson"));
	addWidget(mSkillUILayout);

	LoadingBar* bar = (LoadingBar*)mSkillUILayout->getChildByTag(RangePointTag);  
	bar->addTouchEventListener(this, toucheventselector(SkillFrame::AddSkill));

	bar = (LoadingBar*)mSkillUILayout->getChildByTag(TimePointTag);  
	bar->addTouchEventListener(this, toucheventselector(SkillFrame::AddSkill));

	bar = (LoadingBar*)mSkillUILayout->getChildByTag(SpeedPointTag);  
	bar->addTouchEventListener(this, toucheventselector(SkillFrame::AddSkill));

	bar = (LoadingBar*)mSkillUILayout->getChildByTag(CoinAddPointTag);  
	bar->addTouchEventListener(this, toucheventselector(SkillFrame::AddSkill));

	bar = (LoadingBar*)mSkillUILayout->getChildByTag(CoinDoublePointTag);  
	bar->addTouchEventListener(this, toucheventselector(SkillFrame::AddSkill));

	Button* but = (Button*)mSkillUILayout->getChildByTag(SkillCancelTag);
	but->addTouchEventListener(this, toucheventselector(SkillFrame::cancelUI));

	mPlayer = Player::Instance();
	mPointList = mPlayer->GetPointList();
}
void SkillFrame::_update()
{
	int score = mPlayer->GetScore();
	LoadingBar* bar;
	LabelAtlas* atlas;
	char str[10];
	bar = (LoadingBar*)mSkillUILayout->getChildByTag(RangePointTag);
	bar->setPercent(mPointList[0]*10);
	sprintf(str,"%d",1000*(mPointList[0]+1));
	atlas = (LabelAtlas*)bar->getChildByTag(SkillGoldNumTag);
	
	bar = (LoadingBar*)mSkillUILayout->getChildByTag(TimePointTag);
	bar->setPercent(mPointList[1]*10);
	sprintf(str,"%d",1000*(mPointList[1]+1));
	atlas = (LabelAtlas*)bar->getChildByTag(SkillGoldNumTag);

	bar = (LoadingBar*)mSkillUILayout->getChildByTag(SpeedPointTag);
	sprintf(str,"%d",1000*(mPointList[2]+1));
	bar->setPercent(mPointList[2]*10);
	atlas = (LabelAtlas*)bar->getChildByTag(SkillGoldNumTag);

	bar = (LoadingBar*)mSkillUILayout->getChildByTag(CoinAddPointTag);
	sprintf(str,"%d",2000*(mPointList[3]+1));
	bar->setPercent(mPointList[3]*20);
	atlas = (LabelAtlas*)bar->getChildByTag(SkillGoldNumTag);

	bar = (LoadingBar*)mSkillUILayout->getChildByTag(CoinDoublePointTag);
	sprintf(str,"%d",5000*(mPointList[4]+1));
	bar->setPercent(mPointList[4]);
	atlas = (LabelAtlas*)bar->getChildByTag(SkillGoldNumTag);

	atlas =  (LabelAtlas*)mSkillUILayout->getChildByTag(SkillGoldNumTag);
	sprintf(str,"%d",score);
	atlas->setStringValue(str);

	ThreatenInfo* info = mPlayer->GetThreatenInfo();
	info->mRangeScale = 1.0f + 0.1*mPointList[0];
	info->mTimeScale = 1.0f + 0.1*mPointList[1];
	info->mSpeedScale = 1.0f + 0.1*mPointList[2];
	mPlayer->SetCoinAddPoint(mPointList[3]);
	mPlayer->SetCoinDoublePoint(mPointList[4]);
}
void SkillFrame::popupLayerCallback(CCNode* obj)
{
	this->removeChild(mPopLayer);
}
void SkillFrame::cancelUI(CCObject* obj, ui::TouchEventType eventType)
{
	if(eventType != ui::TOUCH_EVENT_ENDED)
		return;
	UIMgr::Instance()->CloseSkillUI();
	CCDirector::sharedDirector()->resume();
	mPlayer->SavePlayerData();
}
void SkillFrame::AddSkill(CCObject* obj, ui::TouchEventType eventType)
{
	if(eventType != ui::TOUCH_EVENT_ENDED)
		return;
	LoadingBar* btn = (LoadingBar*)obj;
	char str[10];
	LabelAtlas* atlas;
	int flag = -1;
	switch(btn->getTag())
	{
	case RangePointTag:
		flag = 0;
		break;
	case TimePointTag:
		flag = 1;
		break;
	case SpeedPointTag:
		flag = 2;
		break;
	case CoinAddPointTag:
		flag = 3;
		break;
	case CoinDoublePointTag:
		flag = 4;
		break;
	}
	if(mPointList[flag] >= TotalPoint[flag])
		return;
	if(Player::Instance()->DeleteScore(GoldNeed[flag]*(mPointList[flag]+1)))
	{
		mPointList[flag]++;
		_update();
		return;
	}
	mPopLayer = PopupLayer::create("SkillFrame/96-37.png");
	mPopLayer->setTitle("Message");
	mPopLayer->setContentText("test£¿",20,50,150);
	mPopLayer->setCallBackFunc(this,callfuncN_selector(SkillFrame::popupLayerCallback));

	mPopLayer->addButton("SkillFrame/111-5.png","SkillFrame/111-6.png","OK",0);

	mPopLayer->addButton("SkillFrame/111-5.png","SkillFrame/111-6.png","Cancel",1);
	this->addChild(mPopLayer);
}
void SkillFrame::Show()
{
	_update();
}