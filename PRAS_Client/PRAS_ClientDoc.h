// PRAS_ClientDoc.h : CPRAS_ClientDoc ��Ľӿ�
//


#pragma once


class CPRAS_ClientDoc : public CDocument
{
protected: // �������л�����
	CPRAS_ClientDoc();
	DECLARE_DYNCREATE(CPRAS_ClientDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CPRAS_ClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


