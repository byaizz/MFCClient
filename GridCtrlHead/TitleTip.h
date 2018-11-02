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
/*  程序说明 ：  本文件为提示信息的类声明。                                  */
/*                                                                           */
/*****************************************************************************/
/*  作    者 ：                 **  创建日期  ：  2009-10-10                 */
/*****************************************************************************/
/*                              修改记录                                     */
/*                                                                           */
/*  修改日期     **   修改人      **    修改内容                             */
/*  2009-10-10   **               **                                         */
/*                                                                           */
/*****************************************************************************/
/*          审 核 人 ：                         **  审核日期  ：             */
/*****************************************************************************/
/*  文件版本号：0.0.1                                                        */
/*****************************************************************************/
#if !defined(AFX_TITLETIP_H__C7165DA1_187F_11D1_992F_895E185F9C72__INCLUDED_)
#define AFX_TITLETIP_H__C7165DA1_187F_11D1_992F_895E185F9C72__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TitleTip.h : header file
//

#define TITLETIP_CLASSNAME _T("ZTitleTip")

/////////////////////////////////////////////////////////////////////////////
// CTitleTip window

class CTitleTip : public CWnd
{
// Construction
public:
    CTitleTip();
    virtual ~CTitleTip();
    virtual BOOL Create( CWnd *pParentWnd);

// Attributes
public:

// Operations
public:
    void Show(CRect rectTitle, LPCTSTR lpszTitleText, 
              int xoffset = 0, LPRECT lpHoverRect = NULL, 
              LPLOGFONT lpLogFont = NULL);
    void Hide();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTitleTip)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

// Implementation
public:

protected:
    CWnd *m_pParentWnd;
    CRect m_rectTitle;
    CRect m_rectHover;

    // Generated message map functions
protected:
    //{{AFX_MSG(CTitleTip)
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately
// before the previous line.

#endif 
// !defined(AFX_TITLETIP_H__C7165DA1_187F_11D1_992F_895E185F9C72__INCLUDED_)
