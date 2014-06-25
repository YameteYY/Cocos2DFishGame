#ifndef __SKILLFRAME_H__
#define __SKILLFRAME_H__
#include "Mgr/UIMgr.h"

enum SkillPanelButton
{
	AddRange,
	AddTime,
	AddSpeed,
	AddCoinAdd,
	AddCoinDouble,
	Save,
	Cancel
};
class Player;
class PopupLayer;
class SkillFrame : public UILayer
{
public:
	static SkillFrame* create();
	void Init();
	void Show();
private:
	PopupLayer* mPopLayer;
	int*  mPointList;
	void AddSkill(CCObject* obj, ui::TouchEventType eventType);
	void cancelUI(CCObject* obj, ui::TouchEventType eventType);
	void _update();
	void popupLayerCallback(CCNode* obj);
	Layout*  mSkillUILayout;
	Player* mPlayer;
};

#endif