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
/*  ����˵�� ��  ���ļ�Ϊ����б༭��Ԫ����ʵ��                              */
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

// InPlaceEdit.cpp : implementation file
//
// Written by Chris Maunder (chrismaunder@codeguru.com)
// Copyright (c) 1998.
//
// The code contained in this file is based on the original
// CInPlaceEdit from http://www.codeguru.com/listview/edit_subitems.shtml
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
// Modifed 10 May 1998  Uses GVN_ notifications instead of LVN_,
//                      Sends notification messages to the parent, 
//                      instead of the parent's parent.
//
//         15 May 1998  There was a problem when editing with the 
//                        in-place editor, there arises a general protection 
//                        fault in user.exe, with a few qualifications:
//                         (1) This only happens with owner-drawn buttons;
//                         (2) This only happens in Win95
//                         (3) This only happens if the handler for the button
//                               does not create a new window (even an 
//                               AfxMessageBox will avoid the crash)
//                         (4) This will not happen if Spy++ is running.
//                      PreTranslateMessage was added to route messages 
//                        correctly. (Matt Weagle found and fixed this problem)
//         26 Jul 1998  Removed the ES_MULTILINE style - that fixed a few 
//                        probs!
//          6 Aug 1998  Added nID to the constructor param list
//          6 Sep 1998  Space no longer clears selection when starting edit 
//                        (Franco Bez)
//         10 Apr 1999  Enter, Tab and Esc key prob fixed (Koay Kah Hoe)
//                      Workaround for bizzare "shrinking window" problem in CE
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TCHAR.h"
#include "InPlaceEdit.h"

#include "GridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit

CInPlaceEdit::CInPlaceEdit(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
                           int nRow, int nColumn, CString sInitText, 
                           UINT nFirstChar)
{
    m_sInitText     = sInitText;
    m_nRow          = nRow;
    m_nColumn       = nColumn;
    m_nLastChar     = 0; 
    m_bExitOnArrows = (nFirstChar != VK_LBUTTON);    // If mouse click brought
                                                     // us here,
                                                     // then no exit on arrows

    m_Rect = rect;  // For bizarre CE bug.
    
    DWORD dwEditStyle = WS_BORDER|WS_CHILD|WS_VISIBLE
                        | ES_AUTOHSCROLL //|ES_MULTILINE 
                        | dwStyle;
    if (!Create(dwEditStyle, rect, pParent, nID)) return;
    
    SetFont(pParent->GetFont());
    
    SetWindowText(sInitText);
    SetFocus();
    
    switch (nFirstChar){
        case VK_LBUTTON: 
        case VK_RETURN:   SetSel((int)_tcslen(m_sInitText), -1); return;
        case VK_BACK:     SetSel((int)_tcslen(m_sInitText), -1); break;
        case VK_TAB:
        case VK_DOWN: 
        case VK_UP:   
        case VK_RIGHT:
        case VK_LEFT:  
        case VK_NEXT:  
        case VK_PRIOR: 
        case VK_HOME:
        case VK_SPACE:
        case VK_END:      SetSel(0,-1); return;
        default:          SetSel(0,-1);
    }
    
    SendMessage(WM_CHAR, nFirstChar);
}

CInPlaceEdit::~CInPlaceEdit()
{
}

BEGIN_MESSAGE_MAP(CInPlaceEdit, CEdit)
    //{{AFX_MSG_MAP(CInPlaceEdit)
    ON_WM_KILLFOCUS()
    ON_WM_CHAR()
    ON_WM_KEYDOWN()
    ON_WM_GETDLGCODE()
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit message handlers

// If an arrow key (or associated) is pressed, then exit if
//  a) The Ctrl key was down, or
//  b) m_bExitOnArrows == TRUE
void CInPlaceEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
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
    
    CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

// As soon as this edit loses focus, kill it.
void CInPlaceEdit::OnKillFocus(CWnd* pNewWnd)
{
    CEdit::OnKillFocus(pNewWnd);
    EndEdit();
}

void CInPlaceEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (nChar == VK_TAB || nChar == VK_RETURN)
    {
        m_nLastChar = nChar;
        GetParent()->SetFocus();    // This will destroy this window
        return;
    }
    if (nChar == VK_ESCAPE) 
    {
        SetWindowText(m_sInitText);    // restore previous text
        m_nLastChar = nChar;
        GetParent()->SetFocus();
        return;
    }
    
    CEdit::OnChar(nChar, nRepCnt, nFlags);
    
    // Resize edit control if needed
    
    // Get text extent
    CString str;
    GetWindowText( str );

    // add some extra buffer
    str += _T("  ");
    
    CWindowDC dc(this);
    CFont *pFontDC = dc.SelectObject(GetFont());
    CSize size = dc.GetTextExtent( str );
    dc.SelectObject( pFontDC );
       
    // Get client rect
    CRect ParentRect;
    GetParent()->GetClientRect( &ParentRect );
    
    // Check whether control needs to be resized
    // and whether there is space to grow
    if (size.cx > m_Rect.Width())
    {
        if( size.cx + m_Rect.left < ParentRect.right )
            m_Rect.right = m_Rect.left + size.cx;
        else
            m_Rect.right = ParentRect.right;
        MoveWindow( &m_Rect );
    }
}

UINT CInPlaceEdit::OnGetDlgCode() 
{
    return DLGC_WANTALLKEYS;
}

////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit overrides

// Stoopid win95 accelerator key problem workaround - Matt Weagle.
BOOL CInPlaceEdit::PreTranslateMessage(MSG* pMsg) 
{
    // Catch the Alt key so we don't choke if focus is going to 
    // an owner drawn button
    if (pMsg->message == WM_SYSCHAR)
        return TRUE;
    
    return CWnd::PreTranslateMessage(pMsg);
}

// Auto delete
void CInPlaceEdit::PostNcDestroy() 
{
    CEdit::PostNcDestroy();
    
    delete this;    
}

////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit implementation

void CInPlaceEdit::EndEdit()
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
    dispinfo.item.col     = m_nColumn;
    dispinfo.item.szText  = str;
    dispinfo.item.lParam  = (LPARAM) m_nLastChar; 
    
    CWnd* pOwner = GetOwner();
    if (pOwner)
        pOwner->SendMessage(WM_NOTIFY, GetDlgCtrlID(), (LPARAM)&dispinfo );
    
    // Close this window (PostNcDestroy will delete this)
    PostMessage(WM_CLOSE, 0, 0);
}


//////////////////////////////////////////////////////////////////////
// CInPlaceIntEdit Class
//////////////////////////////////////////////////////////////////////
// Modified by PRAS this class is added by PRAS

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInPlaceIntEdit::CInPlaceIntEdit(CWnd* pParent, CRect& rect, DWORD dwStyle,
                                 UINT nID, int nRow, int nColumn, 
                                 CString sInitText, UINT nFirstChar)
{
    dwStyle |= ES_NUMBER;  // ����֮�⣬���๹�췽ʽ��InPlaceEdit��ͬ
    
    m_sInitText     = sInitText;
    m_nRow          = nRow;
    m_nColumn       = nColumn;
    m_nLastChar     = 0; 
    m_bExitOnArrows = (nFirstChar != VK_LBUTTON);    // If mouse click 
                                                     // brought us here,
                                                     // then no exit on arrows

    m_Rect = rect;  // For bizarre CE bug.
    
    DWORD dwEditStyle = WS_BORDER|WS_CHILD|WS_VISIBLE| ES_AUTOHSCROLL
                        //|ES_MULTILINE
                        | dwStyle;
    if (!Create(dwEditStyle, rect, pParent, nID)) return;
    
    SetFont(pParent->GetFont());
    
    SetWindowText(sInitText);
    SetFocus();
    
    switch (nFirstChar){
        case VK_LBUTTON: 
        case VK_RETURN:   SetSel((int)_tcslen(m_sInitText), -1); return;
        case VK_BACK:     SetSel((int)_tcslen(m_sInitText), -1); break;
        case VK_TAB:
        case VK_DOWN: 
        case VK_UP:   
        case VK_RIGHT:
        case VK_LEFT:  
        case VK_NEXT:  
        case VK_PRIOR: 
        case VK_HOME:
        case VK_SPACE:
        case VK_END:      SetSel(0,-1); return;
        default:          SetSel(0,-1);
    }

    SendMessage(WM_CHAR, nFirstChar);
}

CInPlaceIntEdit::~CInPlaceIntEdit()
{

}

BEGIN_MESSAGE_MAP(CInPlaceIntEdit, CInPlaceEdit)
    //{{AFX_MSG_MAP(CInPlaceIntEdit)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Auto delete
void CInPlaceIntEdit::PostNcDestroy() 
{
    CEdit::PostNcDestroy(); // cannot use CInPlaceEdit::PostNcDestroy();

    delete this;    
}


//////////////////////////////////////////////////////////////////////
// CInPlaceDoubleEdit Class
//////////////////////////////////////////////////////////////////////
// Modified by PRAS this class is added by PRAS

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CInPlaceDoubleEdit::CInPlaceDoubleEdit(CWnd* pParent, CRect& rect, 
                                       DWORD dwStyle, UINT nID,
                                       int nRow, int nColumn, 
                                       CString sInitText, UINT nFirstChar)
{
    // ���캯����CInPlaceEdit��ͬ
    m_sInitText     = sInitText;
    m_nRow          = nRow;
    m_nColumn       = nColumn;
    m_nLastChar     = 0; 
    m_bExitOnArrows = (nFirstChar != VK_LBUTTON);    // If mouse click
                                                     // brought us here,
                                                     // then no exit on arrows

    m_Rect = rect;  // For bizarre CE bug.
    
    DWORD dwEditStyle = WS_BORDER|WS_CHILD|WS_VISIBLE| ES_AUTOHSCROLL
                        //|ES_MULTILINE
                        | dwStyle;
    if (!Create(dwEditStyle, rect, pParent, nID)) return;
    
    SetFont(pParent->GetFont());
    
    SetWindowText(sInitText);
    SetFocus();
    
    switch (nFirstChar){
        case VK_LBUTTON: 
        case VK_RETURN:   SetSel((int)_tcslen(m_sInitText), -1); return;
        case VK_BACK:     SetSel((int)_tcslen(m_sInitText), -1); break;
        case VK_TAB:
        case VK_DOWN: 
        case VK_UP:   
        case VK_RIGHT:
        case VK_LEFT:  
        case VK_NEXT:  
        case VK_PRIOR: 
        case VK_HOME:
        case VK_SPACE:
        case VK_END:      SetSel(0,-1); return;
        default:          SetSel(0,-1);
    }

    SendMessage(WM_CHAR, nFirstChar);
}

CInPlaceDoubleEdit::~CInPlaceDoubleEdit()
{

}

BEGIN_MESSAGE_MAP(CInPlaceDoubleEdit, CInPlaceEdit)
    //{{AFX_MSG_MAP(CInPlaceDoubleEdit)
    ON_CONTROL_REFLECT(EN_UPDATE, OnEnUpdate)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Auto delete
void CInPlaceDoubleEdit::PostNcDestroy() 
{
    CEdit::PostNcDestroy(); // cannot use CInPlaceEdit::PostNcDestroy();

    delete this;    
}

void CInPlaceDoubleEdit::OnEnUpdate()
{
    /* 
     * �����������ı����е�ֵ�Ƿ�Ϊdouble
     */
    
    /*
    * ��������
    */
    BOOL bStatus;                                /* ����У����             */
    CString cstrInput;                           /* �ı���������Ϣ           */
    CString cstrResult;                          /* У��󷵻ص��ַ���       */

    /*
    * ��ȡ�ı����ֵ
    */
    GetWindowText(cstrInput);

    /*
    * ���ı������ݲ�Ϊ���������֤
    */
    if (!cstrInput.IsEmpty())
    {
        /*
        * ��������У�麯����У������ֵ
        */
        _CheckDouble(cstrInput, bStatus, cstrResult);
        if (bStatus == EDIT_DOUBLE_CHECK_FAILED) /* У��ûͨ��               */
        {
            SetWindowText(cstrResult);
            SetSel(cstrResult.GetLength(), cstrResult.GetLength(), FALSE);
        }
        else;
    }
}

void CInPlaceDoubleEdit::_CheckDouble(const CString &cstrCheckString, 
                                      BOOL &bCheckResult, 
                                      CString &cstrResult)
{
    /*
     * ��������
     */
    int i;                                       /* ��λ����Ҫ������ַ���   */
    int j;                                       /* �����ַ�����             */
    int iLength;                                 /* ���������ַ����ĳ���     */
    char cDouble[]="0123456789.+-e";             /* double�����ݰ������ַ�   */
    int iTimes;                                  /* ��¼"."���ֵĴ���        */
    int iTimese;                                 /* ��¼"e"���ֵĴ���        */

    bCheckResult = EDIT_DOUBLE_CHECK_FAILED;
    iTimes = 0;
    iTimese = 0;
    iLength = cstrCheckString.GetLength();
    cstrResult = "";
    
    for(i = 0; i < iLength; i++)
    {
        bCheckResult = EDIT_DOUBLE_CHECK_FAILED;
        for(j = 0; j < 14; j++)
        {
            if(cstrCheckString[i] == cDouble[j])
            {
                /*
                 * �����"."����"."�����ڵ�һλ��Ҳ���ܳ�������
                 */
                if(cstrCheckString[i] == '.')
                {
                    iTimes++;
                    if((i == 0) || (iTimes > 1) || (iTimese > 0))
                    {
                        break;
                    }
                    else ;
                }
                else ;
                /*
                 * �����"e"����"e"�����ڵ�һλ��Ҳ���ܳ�������
                 */
                if(cstrCheckString[i] == 'e')
                {
                    iTimese++;
                    if ((i == 0) || (iTimese > 1))
                    {
                        break;
                    }
                    else;
                }
                else ;

                /*
                 * �ж�"+","-"�Ƿ�����λ,���������λ������Ƿ���e�ĺ���
                 */
                if ((cstrCheckString[i] == '+')||(cstrCheckString[i] == '-'))
                {
                    if (i > 0)
                    {
                        if (cstrCheckString[i - 1] != 'e')
                        {
                            break;
                        }
                        else;
                    }
                    else;
                }
                else;

                bCheckResult = EDIT_DOUBLE_CHECK_SUCCESS;
                break;
            }                                    /* for (j = 0;...)          */
            else ;

        }

        if(bCheckResult == EDIT_DOUBLE_CHECK_FAILED)
        {
            return;
        }
        else
        {
            cstrResult += cstrCheckString[i];    /* У��ɹ����ַ��ӵ�����
                                                    �ַ�����                 */
        }
    }                                            /* for (i = 0;...)          */

    bCheckResult = EDIT_DOUBLE_CHECK_SUCCESS;    /* �ַ���ƥ��ɹ�           */
    return ;
}
