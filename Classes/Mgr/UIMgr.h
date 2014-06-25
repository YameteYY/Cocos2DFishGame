#ifndef __UIMGR_H__
#define __UIMGR_H__
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace ui;
class MainFrame;
class SkillFrame;
class UIMgr
{
public:
	static UIMgr* Instance()
	{
		if(0 == m_pInstance)
			m_pInstance = new UIMgr();
		return m_pInstance;
	}
	void Init(CCLayer* gameLayer);
	void ShowSkillUI();
	void CloseSkillUI();
	MainFrame* GetMainFrame();
	SkillFrame* GetSkillFrame();
private:
	CCLayer* mGameLayer;
	MainFrame*	mMainFrame;
	SkillFrame* mSkillFrame;
	UILayer*	mCurrentFrame;
	UIMgr(){}
	static UIMgr* m_pInstance;
};
inline MainFrame* UIMgr::GetMainFrame()
{
	return mMainFrame;
}
inline SkillFrame* UIMgr::GetSkillFrame()
{
	return mSkillFrame;
}
#endif