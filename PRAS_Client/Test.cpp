// Test.cpp : 实现文件
//

#include "stdafx.h"
#include "PRAS_Client.h"
#include "Test.h"


// CTest 对话框

IMPLEMENT_DYNAMIC(CTest, CDialog)

CTest::CTest(CWnd* pParent /*=NULL*/)
	: CDialog(CTest::IDD, pParent)
{

}

CTest::~CTest()
{
}

void CTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTest, CDialog)
END_MESSAGE_MAP()


// CTest 消息处理程序
