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
/*  程序说明 ：  本文件为Graph类声明                                         */
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
#if !defined(AFX_GRAPH_H__9DB68B4D_3C7C_47E2_9F72_EEDA5D2CDBB0__INCLUDED_)
#define AFX_GRAPH_H__9DB68B4D_3C7C_47E2_9F72_EEDA5D2CDBB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Graph.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraph window

#include "GraphSeries.h"
#include "GraphLegend.h"

class CGraph : public CStatic
{
// Construction
public:
    CGraph();
    CGraph(int type);

// Attributes
public:
    int m_iScaler;
    CObList* m_pGraphSeries;

private:
    BOOL m_bGraphHasLegend;
    int m_GraphType;    //0 - bar graph, 1 - line graph, 2 - pie
    int m_GraphAlignment;    //0 - horizontal, 1 - vertical
    int m_iMaxHeight;
    int m_iMaxWidth;
    int m_TickSpace;    //number of pixels between "y" axis ticks
    int m_iYApexPoint;
    int m_iXApexPoint;
    int m_iYAxisHeight;
    int m_iXAxisWidth;
    int m_iTickRange; int m_iTickMin; int m_iLineMore;
    int m_iSeriesSize;    //number of data elements to map per series
    int m_iLegendWidth;
    int m_iXAxisAligh;    //0 - horizontal, # - degree rotation
    int m_iXAxisLabelLength;
    CString m_strAxisYLabel;
    CString m_strAxisXLabel;
    CString m_strGraphTitle;
    CGraphLegend m_GraphLegend;
    COLORREF m_clrDataColor[10]; COLORREF m_clrRef;
    double m_dAmplifier;
// Operations
public:
    void SetTickSpace(int yDist);
    void SetTickRange(int maxTick);
    void SetTickMin(int MinTick);
    void DrawGraph(CDC* pDC,COLORREF colorX);
    void AddSeries(CGraphSeries* dataSet,int&iNumber);
    void SetXAxisLabel(CString label);
    void SetYAxisLabel(CString label);
    void SetLegend(int datagroup, CString label);
    void SetColor(COLORREF Color);
    void SetXAxisAlignment(int alignValue);
    void SetGraphType(int gType);
    void SetGraphTitle(CString title);
    void SetAmplifier(double dX);
    void SetLineMore(int iMore);
private:
    void DrawAxis(CDC* pDC);
    void DrawSeries(CDC* pDC);
    void DrawLegend(CDC* pDC); void vDrawLegendBar(CDC*pDC);
    COLORREF GetColor(int group);
    int GetXAxisAlignment();



// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGraph)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CGraph();

    // Generated message map functions
protected:
    //{{AFX_MSG(CGraph)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before
// the previous line.

#endif 
// !defined(AFX_GRAPH_H__9DB68B4D_3C7C_47E2_9F72_EEDA5D2CDBB0__INCLUDED_)
