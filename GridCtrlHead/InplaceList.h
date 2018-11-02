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
/*  程序说明 ：  本文件为表格中编辑下拉列表类声明                            */
/*                                                                           */
/*****************************************************************************/
/*  作    者 ：                 **  创建日期  ：  2009-12-14                 */
/*****************************************************************************/
/*                              修改记录                                     */
/*                                                                           */
/*  修改日期     **   修改人      **    修改内容                             */
/*                                                                           */
/*****************************************************************************/
/*  审  核  人：                  **  审核日期  ：                           */
/*****************************************************************************/
/*  文件版本号：0.0.1                                                        */
/*****************************************************************************/

#if !defined(AFX_INPLACELIST_H__ECD42822_16DF_11D1_992F_895E185F9C72\
__INCLUDED_)
#define AFX_INPLACELIST_H__ECD42822_16DF_11D1_992F_895E185F9C72__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// InPlaceList.h : header file
//
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
/////////////////////////////////////////////////////////////////////////////

#define IDC_COMBOEDIT 1001

/////////////////////////////////////////////////////////////////////////////
// CComboEdit window

class CComboEdit : public CEdit
{
// Construction
public:
    CComboEdit();

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CComboEdit)
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CComboEdit();

    // Generated message map functions
protected:
    //{{AFX_MSG(CComboEdit)
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CInPlaceList window

class CInPlaceList : public CComboBox
{
    friend class CComboEdit;

// Construction
public:
    CInPlaceList(CWnd* pParent,         // parent
                 CRect& rect,           // dimensions & location
                 DWORD dwStyle,         // window/combobox style
                 UINT nID,              // control ID
                 int nRow, int nColumn, // row and column
                 // Modified by PRAS 去掉了新建对象时传入的CStringArray数组
                 CString sInitText,     // initial selection
                 UINT nFirstChar);      // first character to pass to control

// Attributes
public:
   CComboEdit m_edit;  // subclassed edit control

// Operations
public:
    static void SetItems(CStringArray &Items);  // Modified by PRAS
    static void RemoveItems();                  // Modified by PRAS

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CInPlaceList)
    protected:
    virtual void PostNcDestroy();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CInPlaceList();
protected:
    void EndEdit();

// Generated message map functions
protected:
    //{{AFX_MSG(CInPlaceList)
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

private:
    int        m_nNumLines;
    CString m_sInitText;
    int        m_nRow;
    int        m_nCol;
    UINT    m_nLastChar;
    BOOL    m_bExitOnArrows;
    static  CStringArray m_ListItems;  // Modified by PRAS 保存下拉框的数据
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately 
// before the previous line.

#endif
// !defined(AFX_INPLACELIST_H__ECD42822_16DF_11D1_992F_895E185F9C72__INCLUDED_)
