#ifndef __FISHInfo_H__
#define __FISHInfo_H__

struct FishInfo
{
	char name[64];					//名字
	int fishRunSpeed;				//移动速度
	int worth;						//价值
	int runActs;					//游动帧数
	int catchedActs;				//被捕帧数
	float theatenSpeedScale;		//惊吓后的速度倍数
	float theatenTime;				//惊吓持续时间
};

#endif