/*****************************************************************************/
/*                                                                           */
/*  项目名称 ：  轧钢过程自动化 **  编写单位 ：  上海优控科技有限公司        */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*  项目说明 ：  本项目适用于轧钢过程自动化控制                              */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*  程序说明 ：  本文件为GraphLegend类实现                                   */
/*                                                                           */
/*****************************************************************************/
/*  作    者 ：                 **  创建日期  ：  2009-12-14                 */
/*****************************************************************************/
/*                              修改记录                                     */
/*                                                                           */
/*  修改日期     **   修改人      **    修改内容                             */
/*                                                                           */
/*****************************************************************************/
/*          审 核 人 ：                         **  审核日期  ：             */
/*****************************************************************************/
/*  文件版本号：0.0.1                                                        */
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

