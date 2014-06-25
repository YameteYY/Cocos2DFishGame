#ifndef _NETMGR_H__
#define _NETMGR_H__
#include "cocos2d.h"
using namespace cocos2d;

class NetMgr
{
public:
	static NetMgr* Instance()
	{
		if(0 == m_pInstance)
		{
			m_pInstance = new NetMgr();
		}
		return m_pInstance;
	}
	void CreateNet(const CCPoint& startPoint,const CCPoint& endPoint);
	void Init(CCLayer* layer);
	const CCRect& GetNetCatchedRect() const;
	const CCRect& GetNetRect() const;
private:
	CCLayer*  mGameLayer;
	static NetMgr* m_pInstance;
	CCRect		   mNetCatchedRect;
	CCRect		   mNetRect;
	NetMgr(){}
};

inline const CCRect& NetMgr::GetNetCatchedRect() const
{
	return mNetCatchedRect;
}

inline const CCRect& NetMgr::GetNetRect() const
{
	return mNetRect;
}
#endif