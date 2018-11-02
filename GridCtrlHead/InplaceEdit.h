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
/*  程序说明 ：  本文件为表格中编辑单元格类声明                              */
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

#if !defined(AFX_INPLACEEDIT_H__ECD42821_16DF_11D1_992F_895E185F9C72\
__INCLUDED_)
#define AFX_INPLACEEDIT_H__ECD42821_16DF_11D1_992F_895E185F9C72__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// InPlaceEdit.h : header file
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
/////////////////////////////////////////////////////////////////////////////

#define EDIT_DOUBLE_CHECK_SUCCESS   FALSE
#define EDIT_DOUBLE_CHECK_FAILED    TRUE

/////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit window
 
class CInPlaceEdit : public CEdit
{
// Construction
public:
    CInPlaceEdit(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
                 int nRow, int nColumn, CString sInitText, UINT nFirstChar);
    CInPlaceEdit()          {}  // Modified by PRAS 默认构造函数

// Attributes
public:
 
// Operations
public:
     void EndEdit();
 
// Overrides
     // ClassWizard generated virtual function overrides
     //{{AFX_VIRTUAL(CInPlaceEdit)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    virtual void PostNcDestroy();
    //}}AFX_VIRTUAL
 
// Implementation
public:
     virtual ~CInPlaceEdit();
 
// Generated message map functions
protected:
    //{{AFX_MSG(CInPlaceEdit)
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg UINT OnGetDlgCode();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

//private:
protected: // Modified by PRAS 使得子类可以访问
    int     m_nRow;
    int     m_nColumn;
    CString m_sInitText;
    UINT    m_nLastChar;
    BOOL    m_bExitOnArrows;
    CRect   m_Rect;
};

 
/////////////////////////////////////////////////////////////////////////////
// Modified by PRAS
class CInPlaceIntEdit : public CInPlaceEdit  
{
// Construction
public:
    CInPlaceIntEdit(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
                    int nRow, int nColumn, CString sInitText, UINT nFirstChar);
    CInPlaceIntEdit() {}

// Operations
public:
 
// Overrides
     // ClassWizard generated virtual function overrides
     //{{AFX_VIRTUAL(CInPlaceIntEdit)
    protected:
    virtual void PostNcDestroy();
    //}}AFX_VIRTUAL
 
// Implementation
public:
    virtual ~CInPlaceIntEdit();
 
// Generated message map functions
protected:
    //{{AFX_MSG(CInPlaceIntEdit)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// Modified by PRAS
class CInPlaceDoubleEdit : public CInPlaceEdit  
{
// Construction
public:
    CInPlaceDoubleEdit(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
                    int nRow, int nColumn, CString sInitText, UINT nFirstChar);
    CInPlaceDoubleEdit() {}

// Operations
public:
 
// Overrides
     // ClassWizard generated virtual function overrides
     //{{AFX_VIRTUAL(CInPlaceDoubleEdit)
    protected:
    virtual void PostNcDestroy();
    //}}AFX_VIRTUAL
 
// Implementation
public:
    virtual ~CInPlaceDoubleEdit();
 
// Generated message map functions
protected:
    void _CheckDouble(const CString &strCheckString, BOOL &bCheckResult,
                      CString &strResult);
    //{{AFX_MSG(CInPlaceDbouleEdit)
    afx_msg void OnEnUpdate();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations 
// immediately before the previous line.

#endif
// !defined(AFX_INPLACEEDIT_H__ECD42821_16DF_11D1_992F_895E185F9C72__INCLUDED_)
