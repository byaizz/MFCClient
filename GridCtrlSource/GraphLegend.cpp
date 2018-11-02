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
/*  ����˵�� ��  ���ļ�ΪGraphLegend��ʵ��                                   */
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

// GraphLegend.cpp : implementation file
//

#include "stdafx.h"
//#include "testdraw.h"
#include "GraphLegend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphLegend

CGraphLegend::CGraphLegend()
{
    m_iLegendLength = 0;
    for(int i = 0; i < 10; i++)
        SetLegendText(i, _T(""));

}

CGraphLegend::~CGraphLegend()
{
}


BEGIN_MESSAGE_MAP(CGraphLegend, CStatic)
    //{{AFX_MSG_MAP(CGraphLegend)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphLegend message handlers

void CGraphLegend::SetLegendText(int datagroup, CString label)
{
    m_strLegendLabels[datagroup] = label;
    if(label.GetLength() > m_iLegendLength)
        m_iLegendLength = label.GetLength();
}

CString CGraphLegend::strGetLegendText(int datagroup)
{
    return m_strLegendLabels[datagroup];
}

int CGraphLegend::GetLegendLength()
{
    return m_iLegendLength;
}

