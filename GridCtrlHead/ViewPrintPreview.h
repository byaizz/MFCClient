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
/*  程序说明 ：  本文件为表格打印预览的类声明                                */
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

#if !defined(AFX_VIEWPRINTPREVIEW_H__137FC880_1607_11D3_9317_8F51A5F9742F\
__INCLUDED_)
#define AFX_VIEWPRINTPREVIEW_H__137FC880_1607_11D3_9317_8F51A5F9742F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ViewPrintPreview.h : header file
//

#include "GridCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview view

class CViewPrintPreview : public CView
{
protected:
    CViewPrintPreview();      // protected constructor used by dynamic creation
    DECLARE_DYNCREATE(CViewPrintPreview)

// Attributes
public:
    CGridCtrl *m_pCtrl;
    CFrameWnd *m_pOldFrame;

private:

// Operations
public:
    virtual void OnFilePrintPreview();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CViewPrintPreview)
    protected:
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
    //}}AFX_VIRTUAL


// Implementation
protected:
    virtual ~CViewPrintPreview();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    HANDLE CopyHandle(HANDLE h);    // Modified by PRAS
    HANDLE m_hDevMode;              // Modified by PRAS
    HANDLE m_hDevNames;             // Modified by PRAS

    // Generated message map functions
protected:
    //{{AFX_MSG(CViewPrintPreview)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately
// before the previous line.

#endif
// !defined(AFX_VIEWPRINTPREVIEW_H__137FC880_1607_11D3_9317_8F51A5F9742\
// F__INCLUDED_)
