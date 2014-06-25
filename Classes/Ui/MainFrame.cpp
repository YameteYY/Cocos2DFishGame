#include "MainFrame.h"
#include "Definition.h"
#include "Mgr/FishMgr.h"
#include "Mgr/WaterWaveMgr.h"

MainFrame* MainFrame::create()
{
	MainFrame *pRet = new MainFrame();
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
void MainFrame::Init()
{
	mMainUILayout =  static_cast<ui::Layout*>(GUIReader::shareReader()->widgetFromJsonFile("MainFrame/MainFrame.ExportJson"));
	addWidget(mMainUILayout);

	Button* btn = (Button*)mMainUILayout->getChildByTag(ThreatenButtonTag);  
	btn->addTouchEventListener(this, toucheventselector(MainFrame::ThreatenSkill));

	btn = (Button*)mMainUILayout->getChildByTag(AddSkillTag);
	btn->addTouchEventListener(this, toucheventselector(MainFrame::AddSkillUI));

	mLevelText = (LabelAtlas*)mMainUILayout->getChildByTag(LevelTag); 
	mExperienceBar = (LoadingBar*)mMainUILayout->getChildByTag(ExperienceTag);
}
void MainFrame::SetScore(int score)
{
	ui::LabelAtlas* label =  (ui::LabelAtlas*)(mMainUILayout->getChildByTag(GoldNumTag));
	char str[10];
	sprintf(str,"%d",score);
	label->setStringValue(str);
}
void MainFrame::SetTime(int time)
{
	ui::LabelAtlas* label =  (ui::LabelAtlas*)(mMainUILayout->getChildByTag(TimeNumTag));
	char str[10];
	sprintf(str,"%d",time);
	label->setStringValue(str);
}
void MainFrame::ThreatenSkill(CCObject* obj, ui::TouchEventType eventType)
{
	switch (eventType)  
	{  
	case ui::TOUCH_EVENT_ENDED:  
		FishMgr::Instance()->ThreatenAllFish();
		WaterWaveMgr::Instance()->ScreenWave();
		break; 
	}
}
void MainFrame::AddSkillUI(CCObject* obj, ui::TouchEventType eventType)
{
	if(eventType == ui::TOUCH_EVENT_ENDED)
	{
		CCDirector::sharedDirector()->pause();
		UIMgr::Instance()->ShowSkillUI();
	}
}
void MainFrame::SetLevel(int level)
{
	char str[10];
	sprintf(str,"%d",level);
	mLevelText->setStringValue(str);
}
void MainFrame::SetExperience(int percent)
{
	mExperienceBar->setPercent(percent);
}