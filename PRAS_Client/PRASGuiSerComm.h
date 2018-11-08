#pragma once

#include "NG_malloc.h"
#include "NG_errno.h"
#include "NG_types.h"
#include "NG_Handle.h"

struct COMM_DATA_HEAD{
	short sTelID;//电文识别号
	short sTelHeaderLength;//电文头部长度字节数
	short sTelDataLength;//电文总长度字节数
	short sCounter;//1~32766
	char  szSpare[22];//备用
	short sHeaderSum;//电文头部字节校验和
};


class CPRASGuiSerComm
{
public:
	CPRASGuiSerComm(void);
public:
	~CPRASGuiSerComm(void);
private:
	enum DataLength{
		BUFF_MAX = 5000		//缓存最大长度
	};
private:
	HANDLE m_hComm;//通信句柄
	int m_iCount;//通道数
	void *m_pBuff;//缓存区
public:
	bool IsCommInit();//是否初始化通信
	bool InitComm();//初始化通信
	int CloseComm();//关闭通信
	int GetCommState();//获取通信状态
	void CycleRecvData();//循环接受数据
	void SendHeart();//发送心跳信息

	int SendData(void *pData, int iSize);//发送数据
	void CycleRecvData(int iCount);//接受指定通道数据
	void CommHeadInit(COMM_DATA_HEAD &head, int iID, int iSize);
};
