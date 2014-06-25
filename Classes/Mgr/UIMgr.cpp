#include "UIMgr.h"
#include "Definition.h"
#include "Ui/MainFrame.h"
#include "Ui/SkillFrame.h"

UIMgr* UIMgr::m_pInstance = 0;
void UIMgr::Init(CCLayer* gameLayer)
{
	mGameLayer = gameLayer;
	mMainFrame = MainFrame::create();
	mMainFrame->Init();
	gameLayer->addChild(mMainFrame,UILayerID);
	mCurrentFrame = mMainFrame;

	mSkillFrame = SkillFrame::create();
	mSkillFrame->Init();
	mSkillFrame->retain();
}
void UIMgr::ShowSkillUI()
{
	mGameLayer->addChild(mSkillFrame,UILayerID+1);
	mSkillFrame->Show();
}
void UIMgr::CloseSkillUI()
{
	mGameLayer->removeChild(mSkillFrame,false);
}