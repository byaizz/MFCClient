#pragma once



// CFormConfigView ������ͼ

class CFormConfigView : public CFormView
{
	DECLARE_DYNCREATE(CFormConfigView)

protected:
	CFormConfigView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


