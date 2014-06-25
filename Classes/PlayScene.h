#ifndef __PLAYSCENE_H__
#define __PLAYSCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Definition.h"

using namespace cocos2d::extension;
using namespace cocos2d;
class PlayScene : public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();
	CREATE_FUNC(PlayScene);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
};


#endif //__PLAYSCENE_H__