#include "StdAfx.h"
#include "PRASGuiSerComm.h"
#include "NG_Path.h"
#include "MP_Comm.h"
#include "NG_sock.h"
#include <fstream>

#define GUI_SERVICE_COMM_CFG	"PRASGUIServiceComm.cfg"
#define BUFF_MAX	5000

CPRASGuiSerComm::CPRASGuiSerComm(void)
:m_hComm(NULL)
,m_iCount(0)
{
	m_pBuff = NG_malloc(BUFF_MAX);
}

CPRASGuiSerComm::~CPRASGuiSerComm(void)
{
	CloseComm();
	if (NULL != m_pBuff)
	{
		NG_free(m_pBuff);
	}
}

bool CPRASGuiSerComm::InitComm()
{
	int ret = 0;
	char path[512] = {0};

	//获取配置文件全路径名
	ret = NG_Path_GetRunPath(path,sizeof(path)-1);
	if (ret == ERR_FAILED)
	{
		return false;
	}
	strcat(path,GUI_SERVICE_COMM_CFG);

	//创建通信连接
	m_hComm = MP_Comm_Create(path);
	if (m_hComm == NULL)
	{
		std::fstream fs;
		fs.open(path);
		if (fs)
		{
			fs.close();
		}
		return false;
	}
	

	m_iCount = MP_Comm_GetTunnelCount(m_hComm);
	return true;
}

int CPRASGuiSerComm::CloseComm()
{
	if (m_hComm != NULL)
	{
		NG_CloseHandle(m_hComm);
		m_hComm = NULL;
	}
	return ERR_SUCCESS;
}

int CPRASGuiSerComm::GetCommState()
{
	if (m_hComm == NULL)
	{
		return ERR_FAILED;
	}

	for (int i = 0; i < m_iCount; ++i)
	{
		if (0 != MP_Comm_GetStatus(m_hComm,i))
		{
			return ERR_FAILED;
		}
	}
	return ERR_SUCCESS;
}

void CPRASGuiSerComm::CycleRecvData()
{
	for (int i = 0; i < m_iCount; ++i)
	{
		CycleRecvData(i);
	}
}

void CPRASGuiSerComm::CycleRecvData(int iCount)
{
	if (!IsCommInit())
	{
		return;
	}

	int iSize = 0;

	do 
	{
		iSize = MP_Comm_RecvNoBlock(m_hComm,iCount,m_pBuff,BUFF_MAX);
		if (iSize >= sizeof(COMM_DATA_HEAD))
		{
			MessageBox(NULL,(LPCTSTR)m_pBuff,_T("ReceiveData"),MB_OK);
		}
	} while (iSize != 0);
}

void CPRASGuiSerComm::CommHeadInit(COMM_DATA_HEAD& head, int iID, int iSize)
{
	head.sTelID = iID;
	head.sTelHeaderLength = sizeof(COMM_DATA_HEAD);
	head.sTelDataLength = iSize;
	head.sTelHeaderLength = 0;//等待修改
}

void CPRASGuiSerComm::SendHeart()
{
	int i = 0;
	SendData(&i, sizeof(int));
}

int CPRASGuiSerComm::SendData(void *pData, int iSize)
{
	if(pData == NULL)
	{
		return 1;
	}
	if (iSize <= 0)
	{
		return 1;
	}
	if (!IsCommInit())
	{
		return 1;
	}
	int res = 0;
	for (int i = 0; i < m_iCount; ++i)
	{
		if (1 == MP_Comm_SendNoBlock(m_hComm,i,pData,iSize))
		{
			res = 1;
		}
	}
	return res;
}

bool CPRASGuiSerComm::IsCommInit()
{
	return (m_hComm != NULL);
}