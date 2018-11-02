/*****************************************************************************/
/*                                                                           */
/*  ��Ŀ���� ��  ���ֹ����Զ��� **  ��д��λ ��  �Ϻ��ſؿƼ����޹�˾        */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*  ��Ŀ˵�� ��  ����Ŀ���������ֹ����Զ�������                              */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*  ����˵�� ��  ���ļ�ΪGraphSeries������                                   */
/*                                                                           */
/*****************************************************************************/
/*  ��    �� ��                 **  ��������  ��  2009-12-14                 */
/*****************************************************************************/
/*                              �޸ļ�¼                                     */
/*                                                                           */
/*  �޸�����     **   �޸���      **    �޸�����                             */
/*                                                                           */
/*****************************************************************************/
/*          �� �� �� ��                         **  �������  ��             */
/*****************************************************************************/
/*  �ļ��汾�ţ�0.0.1                                                        */
/*****************************************************************************/

#if !defined(AFX_GRAPHSERIES_H__A059628E_F6C8_4DA0_9E2F_820131D257E7\
__INCLUDED_)
#define AFX_GRAPHSERIES_H__A059628E_F6C8_4DA0_9E2F_820131D257E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphSeries.h : header file
//
#define TOTALPASS 40
/////////////////////////////////////////////////////////////////////////////
// CGraphSeries window

class CGraphSeries : public CStatic
{
// Construction
public:
    CGraphSeries();

// Attributes
public:


private:
    CString m_strSeriesLabel;
    int m_iDataValue[TOTALPASS];    //allows 10 data values in a group

// Operations
public:

    void SetLabel(CString label);
    void SetData(int group, int dValue);
    CString strGetLabel();
    int GetData(int group);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGraphSeries)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CGraphSeries();

    // Generated message map functions
protected:
    //{{AFX_MSG(CGraphSeries)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately 
// before the previous line.

#endif 
// !defined(AFX_GRAPHSERIES_H__A059628E_F6C8_4DA0_9E2F_820131D257E7__INCLUDED_)
