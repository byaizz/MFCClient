#pragma once

#include "NG_malloc.h"
#include "NG_errno.h"
#include "NG_types.h"
#include "NG_Handle.h"

struct COMM_DATA_HEAD{
	short sTelID;//����ʶ���
	short sTelHeaderLength;//����ͷ�������ֽ���
	short sTelDataLength;//�����ܳ����ֽ���
	short sCounter;//1~32766
	char  szSpare[22];//����
	short sHeaderSum;//����ͷ���ֽ�У���
};


class CPRASGuiSerComm
{
public:
	CPRASGuiSerComm(void);
public:
	~CPRASGuiSerComm(void);
private:
	enum DataLength{
		BUFF_MAX = 5000		//������󳤶�
	};
private:
	HANDLE m_hComm;//ͨ�ž��
	int m_iCount;//ͨ����
	void *m_pBuff;//������
public:
	bool IsCommInit();//�Ƿ��ʼ��ͨ��
	bool InitComm();//��ʼ��ͨ��
	int CloseComm();//�ر�ͨ��
	int GetCommState();//��ȡͨ��״̬
	void CycleRecvData();//ѭ����������
	void SendHeart();//����������Ϣ

	int SendData(void *pData, int iSize);//��������
	void CycleRecvData(int iCount);//����ָ��ͨ������
	void CommHeadInit(COMM_DATA_HEAD &head, int iID, int iSize);
};
