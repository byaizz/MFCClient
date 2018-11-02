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
/*  程序说明 ：  本文件为表格中编辑下拉列表类实现                            */
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

// InPlaceList.cpp : implementation file
//
// Written by Chris Maunder (chrismaunder@codeguru.com)
// Copyright (c) 1998.
//
// The code contained in this file is based on the original
// CInPlaceList from http://www.codeguru.com/listview
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file 
// (in whatever form you wish).
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// Expect bugs!
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 
//
// 6 Aug 1998 - Added CComboEdit to subclass the edit control
//              - code provided by Roelf Werkman <rdw@inn.nl>.
//              Added nID to the constructor param list.
// 29 Nov 1998 - bug fix in onkeydown (Markus Irtenkauf)
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InPlaceList.h"

#include "GridCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CComboEdit
CComboEdit::CComboEdit()
{
}

CComboEdit::~CComboEdit()
{
}

// Stoopid win95 accelerator key problem workaround - Matt Weagle.
BOOL CComboEdit::PreTranslateMessage(MSG* pMsg) 
{
    // Make sure that the keystrokes continue to the appropriate handlers
    if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP)
    {
        ::TranslateMessage(pMsg);
        ::DispatchMessage(pMsg);
        return TRUE;
    }    

    // Catch the Alt key so we don't choke 
    // if focus is going to an owner drawn button
    if (pMsg->message == WM_SYSCHAR)
        return TRUE;

    return CEdit::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CComboEdit, CEdit)
    //{{AFX_MSG_MAP(CComboEdit)
    ON_WM_KILLFOCUS()
    ON_WM_KEYDOWN()
    ON_WM_KEYUP()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboEdit message handlers

void CComboEdit::OnKillFocus(CWnd* pNewWnd) 
{
    CEdit::OnKillFocus(pNewWnd);
    
    // This MUST be a CInPlaceList
    CInPlaceList* pOwner = (CInPlaceList*) GetOwner();
    if (pOwner)
        pOwner->EndEdit();    
}

void CComboEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    if ((nChar == VK_PRIOR || nChar == VK_NEXT ||
         nChar == VK_DOWN  || nChar == VK_UP   ||
         nChar == VK_RIGHT || nChar == VK_LEFT) &&
        (GetKeyState(VK_CONTROL) < 0 && GetDlgCtrlID() == IDC_COMBOEDIT))
    {
        CWnd* pOwner = GetOwner();
        if (pOwner)
            pOwner->SendMessage(WM_KEYDOWN, nChar, 
                                nRepCnt + (((DWORD)nFlags)<<16));
        return;
    }

    CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CComboEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    if (nChar == VK_ESCAPE) 
    {
        CWnd* pOwner = GetOwner();
        if (pOwner)
            pOwner->SendMessage(WM_KEYUP, nChar, 
                                nRepCnt + (((DWORD)nFlags)<<16));
        return;
    }

    if (nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
    {
        CWnd* pOwner = GetOwner();
        if (pOwner)
            pOwner->SendMessage(WM_KEYUP, nChar, 
                                nRepCnt + (((DWORD)nFlags)<<16));
        return;
    }

    CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CInPlaceList
CStringArray CInPlaceList::m_ListItems;

CInPlaceList::CInPlaceList(CWnd* pParent, CRect& rect, DWORD dwStyle,
                           UINT nID, int nRow, int nColumn, 
                           CString sInitText, UINT nFirstChar)
{
    m_nNumLines = 2;
    m_sInitText = sInitText;
     m_nRow        = nRow;
     m_nCol      = nColumn;
     m_nLastChar = 0;
    //(nFirstChar != VK_LBUTTON);    // If mouse click brought us here,
    m_bExitOnArrows = FALSE;

    // Modified by PRAS，如果用户没有初始化下拉框的数据，则赋默认值
    if (m_ListItems.GetSize() < 1)
    {
        m_ListItems.Add(_T("11"));
        m_ListItems.Add(_T("22"));
        m_ListItems.Add(_T("33"));
    }
    // Create the combobox
    // Modified by PRAS 添加CBS_DROPDOWN属性
     DWORD dwComboStyle = WS_BORDER|WS_CHILD|WS_VISIBLE|WS_VSCROLL|
                          CBS_AUTOHSCROLL | CBS_DROPDOWN | dwStyle;

    int nHeight = rect.Height();
    rect.bottom = rect.bottom + m_nNumLines*nHeight 
                    + ::GetSystemMetrics(SM_CYHSCROLL);
    if (!Create(dwComboStyle, rect, pParent, nID)) return;

    // Add the strings
    for (int i = 0; i < m_ListItems.GetSize(); i++) 
        AddString(m_ListItems[i]);

    // Get the maximum width of the text strings
    int nMaxLength = 0;
    CClientDC dc(GetParent());
    CFont* pOldFont = dc.SelectObject(pParent->GetFont());

    for (int i = 0; i < m_ListItems.GetSize(); i++) 
        nMaxLength = max(nMaxLength, dc.GetTextExtent(m_ListItems[i]).cx);

    nMaxLength += (::GetSystemMetrics(SM_CXVSCROLL) 
                    + dc.GetTextExtent(_T(" ")).cx*2);
    dc.SelectObject(pOldFont);

    if (nMaxLength > rect.Width())
        rect.right = rect.left + nMaxLength;

    // Resize the edit window and the drop down window
    MoveWindow(rect);

    SetFont(pParent->GetFont());
    SetItemHeight(-1, nHeight);

    SetDroppedWidth(nMaxLength);
    SetHorizontalExtent(0); // no horz scrolling

    // Set the initial text to m_sInitText
    if (SelectString(-1, m_sInitText) == CB_ERR)
        // No text selected, so restore what was there before
        SetWindowText(m_sInitText);

    // Subclass the combobox edit control if style includes CBS_DROPDOWN
    if ((dwStyle & CBS_DROPDOWNLIST) != CBS_DROPDOWNLIST)
    {
        m_edit.SubclassDlgItem(IDC_COMBOEDIT, this);
         SetFocus();
        switch (nFirstChar)
        {
            case VK_LBUTTON: 
            case VK_RETURN:   
                m_edit.SetSel((int)_tcslen(m_sInitText), -1); 
                return;
            case VK_BACK:     
                m_edit.SetSel((int)_tcslen(m_sInitText), -1); 
                break;
            case VK_DOWN: 
            case VK_UP:   
            case VK_RIGHT:
            case VK_LEFT:  
            case VK_NEXT:  
            case VK_PRIOR: 
            case VK_HOME:  
            case VK_END:      m_edit.SetSel(0,-1); return;
            default:          m_edit.SetSel(0,-1);
        }
        SendMessage(WM_CHAR, nFirstChar);
    }
    else
         SetFocus();
}

CInPlaceList::~CInPlaceList()
{
}

void CInPlaceList::EndEdit()
{
    CString str;
    GetWindowText(str);
 
    // Send Notification to parent
    GV_DISPINFO dispinfo;

    dispinfo.hdr.hwndFrom = GetSafeHwnd();
    dispinfo.hdr.idFrom   = GetDlgCtrlID();
    dispinfo.hdr.code     = GVN_ENDLABELEDIT;
 
    dispinfo.item.mask    = LVIF_TEXT|LVIF_PARAM;
    dispinfo.item.row     = m_nRow;
    dispinfo.item.col     = m_nCol;
    dispinfo.item.szText  = str;
    dispinfo.item.lParam  = (LPARAM) m_nLastChar; 
 
    CWnd* pOwner = GetOwner();
    if (IsWindow(pOwner->GetSafeHwnd()))
        pOwner->SendMessage(WM_NOTIFY, GetDlgCtrlID(), (LPARAM)&dispinfo );
 
    // Close this window (PostNcDestroy will delete this)
    PostMessage(WM_CLOSE, 0, 0);
}

void CInPlaceList::PostNcDestroy() 
{
    CComboBox::PostNcDestroy();

    delete this;
}

BEGIN_MESSAGE_MAP(CInPlaceList, CComboBox)
    //{{AFX_MSG_MAP(CInPlaceList)
    ON_WM_KILLFOCUS()
    ON_WM_KEYDOWN()
    ON_WM_KEYUP()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CInPlaceList message handlers

void CInPlaceList::OnKillFocus(CWnd* pNewWnd) 
{
    CComboBox::OnKillFocus(pNewWnd);

    if (GetSafeHwnd() == pNewWnd->GetSafeHwnd())
        return;

    // Only end editing on change of focus 
    // if we're using the CBS_DROPDOWNLIST style
    if ((GetStyle() & CBS_DROPDOWNLIST) == CBS_DROPDOWNLIST)
        EndEdit();
}

// If an arrow key (or associated) is pressed, then exit if
//  a) The Ctrl key was down, or
//  b) m_bExitOnArrows == TRUE
void CInPlaceList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    if ((nChar == VK_PRIOR || nChar == VK_NEXT ||
         nChar == VK_DOWN  || nChar == VK_UP   ||
         nChar == VK_RIGHT || nChar == VK_LEFT) &&
        (m_bExitOnArrows || GetKeyState(VK_CONTROL) < 0))
    {
        m_nLastChar = nChar;
        GetParent()->SetFocus();
        return;
    }

    CComboBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Need to keep a lookout for Tabs, Esc and Returns.
void CInPlaceList::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    if (nChar == VK_ESCAPE) 
        SetWindowText(m_sInitText);    // restore previous text

    if (nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
    {
        m_nLastChar = nChar;
        GetParent()->SetFocus();    // This will destroy this window
        return;
    }

    CComboBox::OnKeyUp(nChar, nRepCnt, nFlags);
}

// Modified by PRAS 设定下拉框数据
void CInPlaceList::SetItems(CStringArray &Items)
{
    for (int i = 0; i < Items.GetSize(); i++)
    {
        m_ListItems.Add(Items[i]);
    }
    return;
}

// Modified by PRAS 清空表格下拉框数据
void CInPlaceList::RemoveItems()
{
    m_ListItems.RemoveAll();
    return;
}
