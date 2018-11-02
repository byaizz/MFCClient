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
/*  程序说明 ：  本文件为表格打印辅助的类声明。                              */
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
#pragma warning(disable : 4996)

#if !defined(AFX_PRINTRX_H__592C1902_0E73_4C23_A133_350A66362613__INCLUDED_)
#define AFX_PRINTRX_H__592C1902_0E73_4C23_A133_350A66362613__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//////////////////////////////////////////////////////////////////////////
// caculate the logic x and y, change into physics x and y.(int printer DC)
#define CALCF(x)        (-MulDiv(x, GetDeviceCaps(m_DC.m_hDC, LOGPIXELSY), 72))
#define CALCY(y)        (MulDiv(y, GetDeviceCaps(m_DC.m_hDC, LOGPIXELSY), 72))
#define CALCX(x)        (MulDiv(x, GetDeviceCaps(m_DC.m_hDC, LOGPIXELSX), 72))

// each added font can have 4 attributes
#define     FACE_NORMAL         0
#define     FACE_NORMALBOLD     1
#define     FACE_BIG            2
#define     FACE_BIGBOLD        3

// for Print text, you should let it by left or right, and up or bottom
// these formats can be combined with the | operator
#define FORMAT_NORMAL   0         //default should be by left and top
#define FORMAT_HCENTER  1
#define FORMAT_VCENTER  2
#define FORMAT_RIGHT    4
#define FORMAT_LEFT     8
#define FORMAT_UP       16
#define FORMAT_BOTTOM   32


// Error-codes
#define PRERR_OK                    0
#define PRERR_NOIMAGES              1
#define PRERR_LOADBITMAPFAILED      2
#define PRERR_NOGETOBJECT           3
#define PRERR_NOCOMPATIBLEDC        4
#define PRERR_NOSELECTOBJECT        5
#define PRERR_STRETCHBLTFAILED      6
#define PRERR_STARTPAGEFAILED       7
#define PRERR_CANTCREATEPRINTERDC   8
#define PRERR_NOBITBLT              9
///////////////////////////////////////////////////////////////////////
class CPrintRX  
{
public:
    void MoveTo(int xCur, int yCur);
    int GetStrSize(TCHAR *str, CSize& size);
    int GetWidth();
    void NewPage();
    void EndPage();
    int StartPage();
    void SetDistance (int punkte);
    int SetMargins(int Top, int Bottom, int Left, int Right);
    int EndPrint();
    int StartPrint();
    int InitToPrint(TCHAR *PrinterName, int Copies);
    int SetFontFace(int iFont, int iFace);
    int AddFont(LOGFONT *lf);
    int AddFont(CFont &newfont);
    int DrawVLine(int x_up, int y_up, int x_bottom, int y_bottom, 
                  CPen &newpen);
    int DrawVLine(int x_up, int y_up, int x_bottom, int y_bottom);
    int DrawHLine(int x_left, int y_left, int x_right, int y_right, 
                  CPen & newpen);
    int DrawHLine(int x_left, int y_left, int x_right, int y_right);
    int DrawText(TCHAR *str, CRect& m_rt, int iFont = 0, int iFace = 0, 
                 int format = FORMAT_NORMAL);
    int DrawText(TCHAR *str, int iFont = 0, int iFace = 0, 
                 int format = FORMAT_NORMAL);
    CPrintRX();
    virtual ~CPrintRX();

private:
    CDC     m_DC;            // device-context for printing
    HDC     m_hPrinter;     // used when given a printer name that chosed
    CDC     m_PrinterDC;    // used when no given a printer chosed, 
                            // you should craeate it youeself

    CFont*  m_font[10][4];  // 10 different fonts with 4 different apperances
                            // for each
    int        m_nFonts;        // number of added fonts, max. 10 possible
    int     m_iFont;        // the index of fonts now
    int     m_iFace[10];    // the index of faces in each font now

    int     m_nCopies;        // number of copies, which should printed
    CSize   m_WorkSize;        // max width/height, which the printer allowes 
                            // on the paper
    CRect   m_Margins;        // desired margins
    int     m_yCur;            // cursor-position at page during the printing
    int     m_xCur;         // cursor-position at page during the printing
    int     m_Abstand;        // distance of lines in points
    int     m_iPage;        // actual page-number
    int     m_LastErrNo;    // contains in error-case the error-number. 
                            // can get with GetErrorCode()
    CPrintDialog    *m_pPrintDlg; // pointer to a various dialog-class, 
                                  // if desired
};

#endif 
// !defined(AFX_PRINTRX_H__592C1902_0E73_4C23_A133_350A66362613__INCLUDED_)
