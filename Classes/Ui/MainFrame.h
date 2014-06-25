#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__
#include "Mgr/UIMgr.h"

class MainFrame : public UILayer
{
public:
	static MainFrame* create();
	void SetScore(int score);
	void SetTime(int time);
	void SetLevel(int level);
	void SetExperience(int percent);
	void Init();
private:
	void ThreatenSkill(CCObject* obj, ui::TouchEventType eventType) ;
	void AddSkillUI(CCObject* obj, ui::TouchEventType eventType) ;
	LabelAtlas* mLevelText;
	LoadingBar*	mExperienceBar;
	Layout*  mMainUILayout;
};

#endif