#ifndef __FISHInfo_H__
#define __FISHInfo_H__

struct FishInfo
{
	char name[64];					//����
	int fishRunSpeed;				//�ƶ��ٶ�
	int worth;						//��ֵ
	int runActs;					//�ζ�֡��
	int catchedActs;				//����֡��
	float theatenSpeedScale;		//���ź���ٶȱ���
	float theatenTime;				//���ų���ʱ��
};

#endif