#pragma once



// CFormMonitorView ������ͼ

class CFormMonitorView : public CFormView
{
	DECLARE_DYNCREATE(CFormMonitorView)

protected:
	CFormMonitorView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFormMonitorView();

public:
	enum { IDD = IDD_FORMMONITORVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


