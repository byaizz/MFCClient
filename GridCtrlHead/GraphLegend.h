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
/*  程序说明 ：  本文件为GraphLegend类声明                                   */
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

#if !defined(AFX_GRAPHLEGEND_H__99A8A552_4029_40CC_839A_D8210C46CD8B\
__INCLUDED_)
#define AFX_GRAPHLEGEND_H__99A8A552_4029_40CC_839A_D8210C46CD8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphLegend.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphLegend window

class CGraphLegend : public CStatic
{
// Construction
public:
    CGraphLegend();

// Attributes
public:


private:
    CString m_strLegendLabels[10];  // to match dataValue size from 
                                    // CGraphSeries class
    int m_iLegendLength;

// Operations
public:
    void SetLegendText(int datagroup, CString label);
    CString strGetLegendText(int datagroup);
    int GetLegendLength();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGraphLegend)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CGraphLegend();

    // Generated message map functions
protected:
    //{{AFX_MSG(CGraphLegend)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately 
// before the previous line.

#endif 
// !defined(AFX_GRAPHLEGEND_H__99A8A552_4029_40CC_839A_D8210C46CD8B__INCLUDED_)
