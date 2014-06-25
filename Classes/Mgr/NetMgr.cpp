#include "NetMgr.h"

NetMgr* NetMgr::m_pInstance = 0;
void NetMgr::Init(CCLayer* layer)
{
	mGameLayer = layer;
}
void NetMgr::CreateNet(const CCPoint& startPoint,const CCPoint& endPoint)
{
	CCSprite* sprite = CCSprite::create("net/net.png");
	sprite->setAnchorPoint(CCPoint(0.5,0));
	sprite->setPosition(startPoint);
	mGameLayer->addChild(sprite,10);

	sprite = CCSprite::create("net/net.png");
	sprite->setAnchorPoint(CCPoint(0.5,0));
	sprite->setPosition(ccp(startPoint.x,startPoint.y + sprite->getContentSize().height));
	mGameLayer->addChild(sprite,10);
	mNetCatchedRect.setRect(startPoint.x - 3,startPoint.y,6,endPoint.y);
	mNetRect = mNetCatchedRect;
	mNetRect.origin.x -= 10;
	mNetRect.size.width += 20;
}