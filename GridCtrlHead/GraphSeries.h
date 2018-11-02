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
/*  程序说明 ：  本文件为GraphSeries类声明                                   */
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
