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
/*  程序说明 ：  本文件为表格打印预览的类实现。                              */
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

// ViewPrintPreview.cpp : implementation file
//

#include "stdafx.h"
#include "ViewPrintPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview

IMPLEMENT_DYNCREATE(CViewPrintPreview, CView)

CViewPrintPreview::CViewPrintPreview()
{
    m_pOldFrame=NULL;

    m_hDevMode = NULL;      // Modified by PRAS
    m_hDevNames = NULL;     // Modified by PRAS

}

CViewPrintPreview::~CViewPrintPreview()
{
    if (m_hDevMode)  GlobalFree(m_hDevMode);    // Modified by PRAS
    if (m_hDevNames) GlobalFree(m_hDevNames);   // Modified by PRAS
}


BEGIN_MESSAGE_MAP(CViewPrintPreview, CView)
    //{{AFX_MSG_MAP(CViewPrintPreview)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview drawing

void CViewPrintPreview::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
    // TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview diagnostics

#ifdef _DEBUG
void CViewPrintPreview::AssertValid() const
{
    CView::AssertValid();
}

void CViewPrintPreview::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview message handlers

void CViewPrintPreview::OnFilePrintPreview()
{
    CView::OnFilePrintPreview();
}

// Modified by PRAS
BOOL CViewPrintPreview::OnPreparePrinting(CPrintInfo* pInfo) 
{
    PRINTDLG pd;
    // Save MFC's printer and install ours instead.
    AfxGetApp()->GetPrinterDeviceDefaults(&pd);

    m_hDevMode = CopyHandle(pd.hDevMode);
    m_hDevNames = CopyHandle(pd.hDevNames);

    LPDEVMODE lpDevMode = (LPDEVMODE)GlobalLock(m_hDevMode);
     // Modified by PRAS 强制为横向打印
    lpDevMode->dmOrientation = DMORIENT_LANDSCAPE;
    GlobalUnlock(m_hDevMode);
    
    AfxGetApp()->SelectPrinter(m_hDevNames, m_hDevMode, FALSE);

    // Perform default MFC handling.
    BOOL b = DoPreparePrinting(pInfo);

    // Reinstall MFC's printer.
    AfxGetApp()->SelectPrinter(pd.hDevNames, pd.hDevMode, FALSE);

    return b;
}

// Modified by PRAS
void CViewPrintPreview::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
    m_pCtrl->OnBeginPrinting(pDC, pInfo);
}

// Modified by PRAS
void CViewPrintPreview::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
    m_pCtrl->OnPrint(pDC, pInfo);
}

void CViewPrintPreview::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
    m_pCtrl->OnEndPrinting(pDC, pInfo);
}

void CViewPrintPreview::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, 
                                          POINT point, CPreviewView* pView)
{
    CView::OnEndPrintPreview(pDC, pInfo, point, pView);
    // Show the original frame
    m_pOldFrame->ShowWindow(SW_SHOW);
    // Restore main frame pointer
    AfxGetApp()->m_pMainWnd=m_pOldFrame;
    m_pCtrl->m_bPrintPreview=FALSE;
    // Kill parent frame and itself
    GetParentFrame()->DestroyWindow();
}

// Modified by PRAS
HANDLE CViewPrintPreview::CopyHandle(HANDLE h)
{
    // Return a handle to a copy of the data
    // that the passed handle was for.
    if (!h) return NULL;

    BYTE*   lpCopy;
    BYTE*   lp;
    HANDLE   hCopy;
    DWORD   dwLen = (DWORD)GlobalSize(h);
    if (hCopy = GlobalAlloc(GHND, dwLen))
    {
        lpCopy = (BYTE*)GlobalLock(hCopy);
        lp     = (BYTE*)GlobalLock(h);

        CopyMemory(lpCopy,lp,dwLen);

        GlobalUnlock(hCopy);
        GlobalUnlock(h);
    }

    return hCopy;
}
