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
/*  程序说明 ：  本文件为表格打印辅助的类实现。                              */
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

#include "stdafx.h"
#include "PrintRX.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
/*
  Procedure for use :
  =========================================================================

    1. Declare an object of CPrintRX.
    2. Call the member-function InitToPrint() to choose a Printer and 
       initialize the object.
    3. Call the member-function StartPrint(). This function MUST be called 
       immediately after InitToPrint(), before other class-functions are be 
       called. It creats the print-document in the printer-spooler 
       (at the end EndPrint() will be called, in order to release it). 
    4. Add the fonts, which are needed, with the member-function AddFont(). 
       Principle it is enough to generate one font. The function returns a 
       handle of the type int, which is then needed from various other 
       member-functions. For each necessary font the function must be called 
       once. There are only 10 different fonts possible.After this function 
       you should call SetFontFace() then. Default is m_Fonts[0][0].
    5. Adjust the margins and the line-space with the member-funktions 
       SetMargins() and SetDistance(). MoveTo() set the point of the cursor 
       aginst of m_Margnis.
    6. MoveTo() set the point of the cursor aginst of m_Margnis.
    7. Call member-function StartPage(), in order to begin a new page. If the 
       page ends call EndPage(). Should it be necessary to print more lines 
       between the call of these two functions, than on one page fits, 
       the class ensures that that EndPage() is called followed by a 
       StartPage() automaticaly. A possibly necessary head- and footingline 
       are created.
    8. Lines are printed with the function DrawHLine() and DrwawVLine(). 
        etc.
    9. Call the member-funktion EndPrint(), in order to release the document 
       in the spooler.
    10. there are some thing to do to better it, Draw BItamp, etc
*/
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrintRX::CPrintRX()
{
    for (int i=0; i<10; i++) 
    {
        m_iFace[i] = 0;
        for (int j=0; j<4; j++) 
            m_font[i][j] = new (CFont);
    }
    m_nFonts = 0;
    m_iFont = 0;

    m_pPrintDlg = NULL;    
    m_Margins.SetRect(0, 0, 0, 0);
    m_yCur = 0;
    m_xCur = 0;

    m_iPage = 1;
    m_nCopies = 1;
}

CPrintRX::~CPrintRX()
{
    for (int i=0; i<10; i++) 
        for (int j=0; j<4; j++) 
            delete (m_font[i][j]);
    if (m_pPrintDlg) 
        delete (m_pPrintDlg);
}

int CPrintRX::DrawText(TCHAR *str, int iFont, int iFace, int format)
{
    m_DC.TextOut(m_xCur, m_yCur, str);
    return 1;
}

int CPrintRX::DrawText(TCHAR *str, CRect& m_rt, int iFont, int iFace, 
                       int format)
{
    SIZE Size;
    GetTextExtentPoint32(m_DC.GetSafeHdc(), str, (int)lstrlen(str), &Size);
    int left, top;
    if (format & FORMAT_HCENTER)
    {
        left = CALCX(m_rt.left) + CALCX(m_rt.Width())/2 - Size.cx/2;
        if (left < CALCX(m_rt.left))
            left = CALCX(m_rt.left);
    }
    else if(format & FORMAT_RIGHT)
    {
        left = CALCX(m_rt.left) + CALCX(m_rt.Width()) - Size.cx;
        if (left < CALCX(m_rt.left))
            left = CALCX(m_rt.left);
    }
    else
        left = CALCX(m_rt.left);
    if (format & FORMAT_VCENTER)
    {
        top = CALCY(m_rt.top) + CALCY(m_rt.Height())/2 - Size.cy/2;
        if (top < CALCY(m_rt.top))
            top = CALCY(m_rt.top);
    }
    else top = CALCY(m_rt.top);
    m_DC.TextOut(left, top, str);

    return 1;
}

int CPrintRX::DrawHLine(int x_left, int y_left, int x_right, int y_right)
{
    m_DC.MoveTo(CALCX(m_Margins.left + x_left), CALCY(m_Margins.top + y_left));
    m_DC.LineTo(CALCX(m_Margins.left + x_right), 
                CALCY(m_Margins.top + y_right));
    return 0;
}

int CPrintRX::DrawHLine(int x_left, int y_left, int x_right, int y_right, 
                        CPen &newpen)
{
    CPen*     oldPen = m_DC.SelectObject(&newpen);
    m_DC.MoveTo(CALCX(m_Margins.left + x_left), CALCY(m_Margins.top + y_left));
    m_DC.LineTo(CALCX(m_Margins.left + x_right), 
                CALCY(m_Margins.top + y_right));
    m_DC.SelectObject(oldPen);
    return 0;
}

int CPrintRX::DrawVLine(int x_up, int y_up, int x_bottom, int y_bottom)
{
    m_DC.MoveTo(CALCX(m_Margins.left + x_up), CALCY(m_Margins.top + y_up));
    m_DC.LineTo(CALCX(m_Margins.left + x_bottom), 
                      CALCY(m_Margins.top + y_bottom));
    return 0;
}

int CPrintRX::DrawVLine(int x_up, int y_up, int x_bottom, int y_bottom, 
                        CPen &newpen)
{
    CPen*     oldPen = m_DC.SelectObject(&newpen);
    m_DC.MoveTo(CALCX(m_Margins.left + x_up), CALCY(m_Margins.top + y_up));
    m_DC.LineTo(CALCX(m_Margins.left + x_bottom), 
                CALCY(m_Margins.top + y_bottom));
    m_DC.SelectObject(oldPen);
    return 0;
}

int CPrintRX::AddFont(CFont &newfont)
{
    return -1;
}

int CPrintRX::AddFont(LOGFONT *lf)
{
    if (m_nFonts == 10)
        return -1;

    m_font[m_nFonts][FACE_NORMAL]->CreateFontIndirect(lf);
    
    lf->lfWeight = FW_BLACK;
    m_font[m_nFonts][FACE_NORMALBOLD]->CreateFontIndirect(lf);
    
    lf->lfWeight = FW_REGULAR;
    lf->lfHeight = CALCF(25); 
    m_font[m_nFonts][FACE_BIG]->CreateFontIndirect(lf);

    lf->lfWeight = FW_BLACK;
    m_font[m_nFonts][FACE_BIGBOLD]->CreateFontIndirect(lf);
    m_nFonts ++;
    return 0;
}

int CPrintRX::SetFontFace(int iFont, int iFace)
{
    ASSERT(iFont < 10);
    ASSERT(iFace < 4);
    m_iFont = iFont;
    m_iFace[m_iFont] = iFace;
    m_DC.SelectObject(m_font[m_iFont][m_iFace[m_iFont]]);
    return 0;
}

int CPrintRX::InitToPrint(TCHAR *PrinterName = NULL, int Copies = 1)
{
    if (m_pPrintDlg == NULL)    // delete it in ~CPrintRX()
        m_pPrintDlg = new CPrintDialog(FALSE,PD_DISABLEPRINTTOFILE);

    ASSERT(m_pPrintDlg != NULL);
    
    if (PrinterName == NULL)    // which printer ist desired, 
                                // and how much copies?
    {
        if (m_pPrintDlg->DoModal() == IDCANCEL) 
            return (-1);
        m_hPrinter = m_pPrintDlg->GetPrinterDC();
        m_nCopies = m_pPrintDlg->GetCopies();
    } 
    else                         // a printer is given by name..
    {
        if (m_PrinterDC.CreateDC(NULL, PrinterName, NULL, NULL) == 0)
        {
            m_LastErrNo = PRERR_CANTCREATEPRINTERDC;
            return (-1);        // failed, then set the num of Last Error
        }
        m_hPrinter = m_PrinterDC;
        m_nCopies = Copies;
    }
    if (m_DC.Attach(m_hPrinter) == 0) 
        return (-1);
    m_DC.m_bPrinting = TRUE;

    if (m_pPrintDlg) 
        delete (m_pPrintDlg);
    m_pPrintDlg = NULL;

    LOGFONT      log,log2,log3,log4,log5;    
    log.lfHeight = CALCF(7);   //add a kind of fond,let height equles 13
//    log.lfHeight = -14;
    log.lfWidth = 0;
    log.lfEscapement = 0;   
    log.lfOrientation = 0;   
    log.lfWeight = FW_REGULAR;   
    log.lfItalic =  false;
    log.lfUnderline = false;   
    log.lfStrikeOut = 0;   
    log.lfCharSet = ANSI_CHARSET;
    log.lfOutPrecision = OUT_DEFAULT_PRECIS;   
    log.lfClipPrecision = CLIP_DEFAULT_PRECIS;   
    log.lfQuality = DEFAULT_QUALITY;
    log.lfPitchAndFamily = DEFAULT_PITCH || FF_ROMAN;   
    lstrcpy (log.lfFaceName,_T("Arial"));
    AddFont(&log);
//    m_iFont = 0;                //set default font is index of 0
    log2.lfHeight = CALCF(10);   //add a kind of fond,let height equles 13
//    log.lfHeight = -14;
    log2.lfWidth = 0;
    log2.lfEscapement = 0;   
    log2.lfOrientation = 0;   
    log2.lfWeight = FW_REGULAR;   
    log2.lfItalic =  false;
    log2.lfUnderline = false;   
    log2.lfStrikeOut = 0;   
    log2.lfCharSet = ANSI_CHARSET;
    log2.lfOutPrecision = OUT_DEFAULT_PRECIS;   
    log2.lfClipPrecision = CLIP_DEFAULT_PRECIS;   
    log2.lfQuality = DEFAULT_QUALITY;
    log2.lfPitchAndFamily = DEFAULT_PITCH || FF_ROMAN;   
    lstrcpy (log2.lfFaceName,_T("Arial"));
    AddFont(&log2);

    log3.lfHeight = CALCF(12);   //add a kind of fond,let height equles 13
//    log.lfHeight = -14;
    log3.lfWidth = 0;
    log3.lfEscapement = 0;   
    log3.lfOrientation = 0;   
    log3.lfWeight = FW_REGULAR;   
    log3.lfItalic =  false;
    log3.lfUnderline = false;   
    log3.lfStrikeOut = 0;   
    log3.lfCharSet = ANSI_CHARSET;
    log3.lfOutPrecision = OUT_DEFAULT_PRECIS;   
    log3.lfClipPrecision = CLIP_DEFAULT_PRECIS;   
    log3.lfQuality = DEFAULT_QUALITY;
    log3.lfPitchAndFamily = DEFAULT_PITCH || FF_ROMAN;   
    lstrcpy (log3.lfFaceName,_T("Arial"));
    AddFont(&log3);

    log4.lfHeight = CALCF(6);   //add a kind of fond,let height equles 13
//    log.lfHeight = -14;
    log4.lfWidth = 0;
    log4.lfEscapement = 0;   
    log4.lfOrientation = 0;   
    log4.lfWeight = FW_REGULAR;   
    log4.lfItalic =  false;
    log4.lfUnderline = false;   
    log4.lfStrikeOut = 0;   
    log4.lfCharSet = ANSI_CHARSET;
    log4.lfOutPrecision = OUT_DEFAULT_PRECIS;   
    log4.lfClipPrecision = CLIP_DEFAULT_PRECIS;   
    log4.lfQuality = DEFAULT_QUALITY;
    log4.lfPitchAndFamily = DEFAULT_PITCH || FF_ROMAN;   
    lstrcpy (log4.lfFaceName,_T("Arial"));
    AddFont(&log4);

    log5.lfHeight = CALCF(9);   //add a kind of fond,let height equles 13
//    log.lfHeight = -14;
    log5.lfWidth = 0;
    log5.lfEscapement = 0;   
    log5.lfOrientation = 0;   
    log5.lfWeight = FW_REGULAR;   
    log5.lfItalic =  false;
    log5.lfUnderline = false;   
    log5.lfStrikeOut = 0;   
    log5.lfCharSet = ANSI_CHARSET;
    log5.lfOutPrecision = OUT_DEFAULT_PRECIS;   
    log5.lfClipPrecision = CLIP_DEFAULT_PRECIS;   
    log5.lfQuality = DEFAULT_QUALITY;
    log5.lfPitchAndFamily = DEFAULT_PITCH || FF_ROMAN;   
    lstrcpy (log5.lfFaceName,_T("Arial"));
    AddFont(&log5);

    return 0;
}

int CPrintRX::StartPrint()
{
    CString            strTitle;    // Get the application title
    DOCINFO            di;         // Initialise print document details
    strTitle.LoadString(AFX_IDS_APP_TITLE);
    ::ZeroMemory(&di, sizeof (DOCINFO));
    di.cbSize = sizeof (DOCINFO);
    di.lpszDocName = strTitle;

    // Begin a new print job
    //"winerror.h"  #define FAILED(Status) ((HRESULT)(Status)<0)
    if FAILED(m_DC.StartDoc(&di) == -1) return (-1);
    
    // Get the printing extents and store in the m_DimDraw fields
    m_WorkSize.cx = m_DC.GetDeviceCaps(HORZRES);
    m_WorkSize.cy = m_DC.GetDeviceCaps(VERTRES);

    return  0;
}

int CPrintRX::EndPrint()
{
    m_DC.EndDoc();                // end a print job
    m_DC.Detach();              // detach the printer DC
    return 0;
}

int CPrintRX::SetMargins(int Top, int Bottom, int Left, int Right)
{
    if (Top > 0) 
        m_Margins.top = Top;
    if (Bottom > 0) 
        m_Margins.bottom = Bottom;
    if (Left > 0) 
        m_Margins.left = Left;
    if (Right > 0) 
        m_Margins.right = Right;

    m_yCur = CALCY(m_Margins.top);
    m_xCur = CALCX(m_Margins.left);
    return 0;
}

void CPrintRX::SetDistance(int punkte)
{
    m_Abstand = punkte;
}

int CPrintRX::StartPage()
{
    if (m_DC.StartPage() < 0) 
    {
        m_LastErrNo = PRERR_STARTPAGEFAILED;
        return (-1);
    }
    m_yCur = CALCY(m_Margins.top);
    m_xCur = CALCX(m_Margins.left);
    return 0;
}

void CPrintRX::EndPage()
{
        m_DC.EndPage();  
}

void CPrintRX::NewPage()
{
    m_DC.EndPage(); 
    m_DC.StartPage();
    m_yCur = CALCY(m_Margins.top);
    m_xCur = CALCX(m_Margins.left);
}

int CPrintRX::GetWidth()
{
    return MulDiv(m_WorkSize.cx, 72, GetDeviceCaps(m_DC.m_hDC, LOGPIXELSX));
}

int CPrintRX::GetStrSize(TCHAR *str, CSize &size)
{
    GetTextExtentPoint32(m_DC.GetSafeHdc(), str, (int)lstrlen(str), &size);
    size.cx = MulDiv(size.cx, 72, GetDeviceCaps(m_DC.m_hDC, LOGPIXELSX));
    size.cy = MulDiv(size.cy, 72, GetDeviceCaps(m_DC.m_hDC, LOGPIXELSY));
    return 0;
}

void CPrintRX::MoveTo(int xCur, int yCur)
{
    m_xCur = CALCX(m_Margins.left + xCur);
    m_yCur = CALCY(m_Margins.right + yCur);
}
