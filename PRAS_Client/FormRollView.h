#pragma once



// CFormRollView ������ͼ

class CFormRollView : public CFormView
{
	DECLARE_DYNCREATE(CFormRollView)

protected:
	CFormRollView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFormRollView();

public:
	enum { IDD = IDD_FORMROLLVIEW };
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


