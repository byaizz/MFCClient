#pragma once
#include "afxwin.h"



// CFormConfigView 窗体视图

class CFormConfigView : public CFormView
{
	DECLARE_DYNCREATE(CFormConfigView)

protected:
	CFormConfigView();           // 动态创建所使用的受保护的构造函数
	virtual ~CFormConfigView();

public:
	enum { IDD = IDD_FORMCONFIGVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 下拉框
	CComboBox m_ComboBoxCtrl;
public:
	virtual void OnInitialUpdate();
public:
	afx_msg void OnCbnSelendokCombo1();
private:
	CToolTipCtrl m_toolTips;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


