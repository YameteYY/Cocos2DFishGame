#ifndef __NUMFACTORY_H__
#define __NUMFACTORY_H__
#include "cocos2d.h"
using namespace cocos2d;
class NumFactory
{
public:
	static NumFactory* Instance()
	{
		if(0 == m_pInstance)
		{
			m_pInstance = new NumFactory();
		}
		return m_pInstance;
	}
	void Init(CCLayer* layer);
	CCArray* GetScoreSprite(int score,bool withMulty = false);
	void DeleteScore(CCArray* scoreArray);
private:
	CCSpriteBatchNode*					mNumGoldSpritebatch;
	static NumFactory* m_pInstance;
	NumFactory(){}
};
#endif