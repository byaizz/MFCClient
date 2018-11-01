#pragma once



// CFormFurnaceView 窗体视图

class CFormFurnaceView : public CFormView
{
	DECLARE_DYNCREATE(CFormFurnaceView)

protected:
	CFormFurnaceView();           // 动态创建所使用的受保护的构造函数
	virtual ~CFormFurnaceView();

public:
	enum { IDD = IDD_FORMFURNACEVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


