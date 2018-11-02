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
/*  ����˵�� ��  ���ļ�ΪGraphSeries��ʵ��                                   */
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

// GraphSeries.cpp : implementation file
//

#include "stdafx.h"
//#include "testdraw.h"
#include "GraphSeries.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphSeries

CGraphSeries::CGraphSeries()
{
    for(int i = 0; i < TOTALPASS; i++)
        m_iDataValue[i] = 0;
}

CGraphSeries::~CGraphSeries()
{
}


BEGIN_MESSAGE_MAP(CGraphSeries, CStatic)
    //{{AFX_MSG_MAP(CGraphSeries)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphSeries message handlers

void CGraphSeries::SetLabel(CString label)
{
    m_strSeriesLabel = label;
}

void CGraphSeries::SetData(int group, int dValue)
{
    m_iDataValue[group] = dValue;
}

CString CGraphSeries::strGetLabel()
{
    return m_strSeriesLabel;
}

int CGraphSeries::GetData(int group)
{
    return m_iDataValue[group];
}

