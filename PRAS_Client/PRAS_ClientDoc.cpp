// PRAS_ClientDoc.cpp : CPRAS_ClientDoc 类的实现
//

#include "stdafx.h"
#include "PRAS_Client.h"

#include "PRAS_ClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPRAS_ClientDoc

IMPLEMENT_DYNCREATE(CPRAS_ClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CPRAS_ClientDoc, CDocument)
END_MESSAGE_MAP()


// CPRAS_ClientDoc 构造/析构

CPRAS_ClientDoc::CPRAS_ClientDoc()
{
	// TODO: 在此添加一次性构造代码

}

CPRAS_ClientDoc::~CPRAS_ClientDoc()
{
}

BOOL CPRAS_ClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CPRAS_ClientDoc 序列化

void CPRAS_ClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CPRAS_ClientDoc 诊断

#ifdef _DEBUG
void CPRAS_ClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPRAS_ClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPRAS_ClientDoc 命令
