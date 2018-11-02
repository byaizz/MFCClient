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
/*  程序说明 ：  本文件为Graph类实现                                         */
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

// Graph.cpp : implementation file
//

#include "stdafx.h"
//#include "testdraw.h"
#include "GraphSeries.h"
#include "GraphLegend.h"
#include "math.h"
#include "Graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraph

CGraph::CGraph()
{
    m_pGraphSeries = new CObList();
    m_iTickRange   = 100;
    m_iSeriesSize  = 0;
    m_iTickMin     = 0;
    m_bGraphHasLegend = FALSE;
    m_iLegendWidth = 0;
    m_clrRef  = RGB(0, 0, 0);
//    m_iBottom   =0;
    m_iScaler   = 1;
    m_GraphType = 0;
    m_clrDataColor[0] = RGB(  0, 155,   0);  //green
    m_clrDataColor[1] = RGB(  0,   0, 255);  //blue
    m_clrDataColor[2] = RGB(255,   0,   0);  //red
    m_clrDataColor[3] = RGB(255, 255,   0);  //yellow
    m_clrDataColor[4] = RGB(255, 153,  51);  //orange
    m_clrDataColor[5] = RGB(255,  51, 153);  //hot pink
    m_clrDataColor[6] = RGB(153,   0, 204);  //purple
    m_clrDataColor[7] = RGB(  0, 255, 255);  //cyan
    m_clrDataColor[8] = RGB(  0,   0,   0);  //black
    m_clrDataColor[9] = RGB(255, 255, 255);  //white
    m_iLineMore   = 0;
    m_iXAxisAligh = 0;  //horizontal
    m_iXAxisLabelLength = 0;
}

CGraph::CGraph(int type)
{
    m_pGraphSeries = new CObList();
    m_iLineMore    = 0;
    m_iTickRange   = 100;
    m_iSeriesSize  = 0;
    m_iScaler      = 1;
    m_clrRef       = RGB(0, 0, 0);
    m_bGraphHasLegend = FALSE;
    m_iLegendWidth = 0;
    m_iTickMin     = 0;
    m_GraphType    = type;
//    m_iBottom   =0;
    m_clrDataColor[0] = RGB(  0, 155,   0);  //green
    m_clrDataColor[1] = RGB(  0,   0, 255);  //blue
    m_clrDataColor[2] = RGB(255,   0,   0);  //red
    m_clrDataColor[3] = RGB(255, 255,   0);  //yellow
    m_clrDataColor[4] = RGB(255, 153,  51);  //orange
    m_clrDataColor[5] = RGB(255,  51, 153);  //hot pink
    m_clrDataColor[6] = RGB(153,   0, 204);  //purple
    m_clrDataColor[7] = RGB(  0, 255, 255);  //cyan
    m_clrDataColor[8] = RGB(  0,   0,   0);  //black
    m_clrDataColor[9] = RGB(255, 255, 255);  //white

    m_iXAxisAligh = 0;  //horizontal
    m_iXAxisLabelLength = 0;
}

CGraph::~CGraph()
{
    m_pGraphSeries->RemoveAll();
    if(m_pGraphSeries)
        delete m_pGraphSeries;
}


BEGIN_MESSAGE_MAP(CGraph, CStatic)
    //{{AFX_MSG_MAP(CGraph)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraph message handlers
void CGraph::SetAmplifier(double dX)
{
    m_dAmplifier = dX;
}
void CGraph::SetLineMore(int iMore)
{
    m_iLineMore = iMore;
}
void CGraph::SetTickSpace(int yDist)
{
    m_TickSpace = yDist;
}

void CGraph::SetTickRange(int maxTick)
{
    m_iTickRange = maxTick;
}
void CGraph::SetTickMin(int MinTick)
{
    m_iTickMin = MinTick;
}
void CGraph::SetGraphType(int gType)
{
    m_GraphType = gType;
}

void CGraph::SetXAxisAlignment(int alignValue)
{
    m_iXAxisAligh = alignValue;
}

int CGraph::GetXAxisAlignment()
{
    return m_iXAxisAligh;
}

void CGraph::DrawGraph(CDC* pDC,COLORREF colorX)
{
    CString tickLabel;
    CWnd* graphWnd = pDC->GetWindow();
    CRect graphRect;
    graphWnd->GetClientRect(&graphRect);

    m_iMaxHeight = graphRect.Height();
    m_iMaxWidth = graphRect.Width();

    if(m_GraphType == 2)  //pie
    {

        m_iXAxisWidth =int(m_iMaxWidth*0.99);
        m_iYAxisHeight = int(m_iMaxHeight*0.98);  //10 buffer and 20 for title
        m_iXApexPoint = int(m_iMaxWidth*.01);//5;
        m_iYApexPoint = m_iMaxHeight ;
    }
    else
    {
        tickLabel.Format(_T("%d"), m_iTickRange);

        m_iXApexPoint = (tickLabel.GetLength() * 9);
            // allowing 8 pixels per char in tick label
            // + 30/*(m_strAxisYLabel.GetLength() * 8)*/ + 5; 
            // y apex based on 5 + 15 (x label) + 4 (for the tick)
            // + 4 (text below tick) + 12 (tick label) + 10
        if(!m_iXAxisAligh)  //horizontal
            m_iYApexPoint = int (0.99*m_iMaxHeight);
                         //apex points are the cross section of axis lines
        else
            m_iYApexPoint = int (0.98*m_iMaxHeight);
                                          // - (m_iXAxisLabelLength * 10);
        m_iYAxisHeight = m_iYApexPoint - m_iYApexPoint/10;
        m_iXAxisWidth = (m_iMaxWidth - m_iMaxWidth/10) ;//- m_iXApexPoint;
    }

    //draw legend
    if(m_bGraphHasLegend){
        if(m_GraphType==0)
            vDrawLegendBar(pDC);
        else
            DrawLegend(pDC);
    }

    if(m_GraphType != 2)  //pie
    {
        //draw axis lines
        DrawAxis(pDC);
    }

    //draw series data and labels
    DrawSeries(pDC);

}

void CGraph::DrawAxis(CDC* pDC)
{
    pDC->SetTextColor(RGB(0,0,0));

    //draw y axis
    if(m_iLineMore<=1){
        pDC->MoveTo(m_iXApexPoint, int(m_iMaxHeight*0.99));//m_iYAxisHeight);
        pDC->LineTo(m_iXApexPoint, int(0.02*m_iMaxHeight));
                                          //m_iYAxisHeight - m_iYAxisHeight);
        pDC->SetBkMode(TRANSPARENT);
    }
    else{
        pDC->MoveTo(int(m_iMaxWidth*.04),int( m_iMaxHeight*0.99));
                                                            //m_iYAxisHeight);
        pDC->LineTo(int(m_iMaxWidth*.04), int(0.02*m_iMaxHeight));
                                           //m_iYAxisHeight - m_iYAxisHeight);
        pDC->SetBkMode(TRANSPARENT);
    }
    //draw x axis
    pDC->MoveTo(m_iXApexPoint,int(m_iMaxHeight*0.99));//m_iYAxisHeight);  
    if(m_bGraphHasLegend)
        pDC->LineTo(m_iXApexPoint + (m_iXAxisWidth ),int(m_iMaxHeight*0.99));
                                                            //m_iYAxisHeight);
    else
        pDC->LineTo(m_iXApexPoint + m_iXAxisWidth,int(m_iMaxHeight*0.99));
                                                            //m_iYAxisHeight);

    //draw labels
    if(m_iLineMore<=1){
        CFont sideFont;
        sideFont.CreateFont(-9, 0, 900, 0, 700, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,_T("Arial"));
        CFont* pOldFont = (CFont*) pDC->SelectObject(&sideFont);

        pDC->TextOut(int(m_iXApexPoint/2.5), int(m_iMaxHeight*0.04) , 
                     m_strAxisYLabel);
        pDC->SelectObject(pOldFont);

        pDC->TextOut((m_iMaxWidth / 2), int(1.05*m_iMaxHeight), 
                     m_strAxisXLabel);
        //to allow scalability (height may be less than m_iTickRange)
        double tickScale = 0.00;
    //    if(m_iTickRange > m_iYAxisHeight)
            tickScale = ((m_iYAxisHeight * 1.00) / (m_iTickRange * 1.00))
                        * m_TickSpace;
    //    else tickScale = m_TickSpace;
        int iCount = m_iTickRange/m_TickSpace;
        //draw y axis ticks
    //    m_iBottom   =m_iTickMin+ (m_iTickRange-m_iTickMin)/2.0;

         int iy = int(m_iTickMin*1.0/m_TickSpace);
         tickScale =tickScale*iCount/((iCount-iy)*1.0);
         m_iScaler = int(iCount/((iCount-iy)*1.0));

        CFont ctrlFont;
        ctrlFont.CreateFont(-12, 0, 900, 0, 700, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,_T("Arial"));
        CFont* pXFont = (CFont*) pDC->SelectObject(&ctrlFont);

        for(int y =iy; y <= m_iTickRange / m_TickSpace; y++)  //no tick at 0
        {
            int tickYLocation = (int)(m_iMaxHeight - (y-iy)* tickScale);

            pDC->MoveTo(m_iXApexPoint - 4, tickYLocation);
            pDC->LineTo(m_iXApexPoint + 4, tickYLocation);

            //draw tick label
            CString tickLabel;
            tickLabel.Format(_T("%d"), y * m_TickSpace);

        //    pDC->TextOut(m_iXApexPoint - (tickLabel.GetLength() * 9),
        //               tickYLocation, tickLabel);
            pDC->TextOut(int(m_iXApexPoint/3.0), tickYLocation, tickLabel);
        }
        pDC->SelectObject(pXFont);
        //draw X axis tick marks
        POSITION pos;
        pos = m_pGraphSeries->GetHeadPosition();
        CGraphSeries* tmpSeries;
        CFont sideFont2; //(m_iXAxisAligh * 10)
        sideFont2.CreateFont(14, 0, (m_iXAxisAligh * 10), 0, 700, FALSE, FALSE,
                             0,    ANSI_CHARSET, OUT_DEFAULT_PRECIS, 
                             CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                             DEFAULT_PITCH | FF_ROMAN,_T("Arial"));
        pOldFont = (CFont*) pDC->SelectObject(&sideFont2);
        for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
        {
            tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

            int seriesSpace;
            int tickXLocation;
            if(m_bGraphHasLegend)
                seriesSpace= (int)((m_iXAxisWidth) / m_pGraphSeries->GetCount());
            else
                seriesSpace= (int)(m_iXAxisWidth /m_pGraphSeries->GetCount());
            tickXLocation = m_iXApexPoint + ((x * seriesSpace));

            pDC->MoveTo(tickXLocation,int(m_iMaxHeight*0.99 - 4));
            pDC->LineTo(tickXLocation,int(m_iMaxHeight*0.99));

            //draw tick label
            CString tickLabel;
            tickLabel = tmpSeries->strGetLabel();
            if(!m_iXAxisAligh)  //horizontal
                pDC->TextOut(tickXLocation - ((tickLabel.GetLength() * 8) / 2),
                             m_iMaxHeight, tickLabel);
            else
            {
                if(m_iXAxisAligh < 180)
                    pDC->TextOut(tickXLocation , m_iMaxHeight, tickLabel);
                else
                    pDC->TextOut(tickXLocation , m_iMaxHeight, tickLabel);

            }
        }
        pDC->SelectObject(pOldFont);
    }
}

void CGraph::AddSeries(CGraphSeries* dataSet,int&iNumber)
{
    int numData = 0;
    for(int i = 0; i < iNumber; i++)
    {
        if(dataSet->GetData(i) > 0)
            numData++;
        if(dataSet->strGetLabel().GetLength() > m_iXAxisLabelLength)
            m_iXAxisLabelLength = dataSet->strGetLabel().GetLength();
    }
    if(numData > m_iSeriesSize)
        m_iSeriesSize = numData;

    m_pGraphSeries->AddTail(dataSet);
}

void CGraph::SetXAxisLabel(CString label)
{
    m_strAxisXLabel = label;
}
void CGraph::SetYAxisLabel(CString label)
{
    m_strAxisYLabel = label;
}

void CGraph::SetColor(COLORREF Color)
{
    //m_clrDataColor[group] = groupColor;
    m_clrRef = Color; 
}

COLORREF CGraph::GetColor(int group)
{
    return m_clrDataColor[group];
}

void CGraph::DrawSeries(CDC* pDC)
{
    int barWidth;
    int dataPlotSize;   //used to plot rects of data
    int barL, barT, barR, barB;
    int tickXLocation;
    int seriesSpace;
    double barHeight;  //for scalability
    POSITION pos;
    CGraphSeries* tmpSeries;

    if(m_GraphType == 0) //bar
    {
        //determine width of barchart data blocks
    //    if(m_bGraphHasLegend)
            seriesSpace = (int)((m_iXAxisWidth - m_iLegendWidth ) 
                          / m_pGraphSeries->GetCount());
    //    else
    //        seriesSpace = m_iXAxisWidth / m_pGraphSeries->GetCount();
        barWidth =int( (seriesSpace * .35) / m_iSeriesSize);
        dataPlotSize = m_iSeriesSize * barWidth;

        pos = m_pGraphSeries->GetHeadPosition();

        for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
        {
            tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

            tickXLocation = m_iXApexPoint 
                            + ((x * seriesSpace) - (seriesSpace / 2));

            for(int s = 0; s < m_iSeriesSize; s++)
            {
                barHeight = 0.00;
                //to allow scalability (height may be less than m_iTickRange)
                double dataScale = 0.00;
            ///    if(m_iTickRange > m_iYAxisHeight)
                    dataScale = (m_iYAxisHeight * 1.00) 
                                / (m_iTickRange * 1.00);
            //    else dataScale = 1;
                barHeight = (tmpSeries->GetData(s) * 1.00) * dataScale;
                barL =  (s * barWidth) + int(tickXLocation/1.6)
                        - (dataPlotSize / 2);
                barT = (int)(m_iYApexPoint - barHeight);
                barR = barL + barWidth;
                barB = m_iYApexPoint;
                
                COLORREF barColor;
                barColor = GetColor(s);
                CBrush brush (barColor);
                CBrush* pOldBrush;
                pOldBrush = pDC->SelectObject(&brush);
                pDC->Rectangle(barL, barT, barR, barB);
                pDC->SelectObject(&pOldBrush);
            }
        }
    }

    if(m_GraphType == 1)  //line
    {
        if(m_iLineMore<=1){
            CFont sideFont2; //(m_iXAxisAligh * 10)
            sideFont2.CreateFont(14, 0, (m_iXAxisAligh * 10), 0, 700, 
                                 FALSE, FALSE, 0, ANSI_CHARSET, 
                                 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                 DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,
                                 _T("Arial"));
            CFont *pOldFont = (CFont*) pDC->SelectObject(&sideFont2);
            pDC->SetBkMode(TRANSPARENT);
            pDC->SetTextColor(m_clrRef);
            pDC->TextOut(int(m_iMaxWidth/2.0),
                         int(m_iMaxHeight*0.1),m_strGraphTitle);
            pDC->SelectObject(pOldFont);
        }
        int lastXLoc, lastYLoc;
        for(int s = 0; s < m_iSeriesSize; s++)
        {
            //determine width of barchart data blocks
            if(m_bGraphHasLegend)
                seriesSpace = (int)((m_iXAxisWidth - m_iLegendWidth - 10) 
                              / m_pGraphSeries->GetCount());
            else
                seriesSpace = (int)(m_iXAxisWidth / m_pGraphSeries->GetCount());
            barWidth = int((seriesSpace * .6) / m_iSeriesSize);
            dataPlotSize = m_iSeriesSize * barWidth;

            pos = m_pGraphSeries->GetHeadPosition();

            for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
            {
                tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

                tickXLocation = m_iXApexPoint + 
                                ((x * seriesSpace) - (seriesSpace / 2));
                barHeight = 0.00;
                //to allow scalability (height may be less than m_iTickRange)
                double dataScale = 0.00;
            //    if(m_iTickRange > m_iYAxisHeight)
                    dataScale = (m_iYAxisHeight * 1.00) 
                                / ((m_iTickRange-m_iTickMin) * 1.00);
            //    else dataScale = 1;
           //      dataScale*=1.0*m_iScaler /m_TickSpace;
        
                barHeight = ((tmpSeries->GetData(s)-m_iTickMin) * 1.00) 
                            * dataScale;

            //    int yDataLocation = m_iYApexPoint - barHeight;
                int yDataLocation =(int)((m_iMaxHeight*0.99 )- barHeight);    
                //now have x and y location of center of ellipse
                //COLORREF barColor;
            //    barColor = GetColor(s);
                CBrush brush (m_clrRef);
                CBrush* pOldBrush;
                pOldBrush = pDC->SelectObject(&brush);
                //draw line back to last data member
                if(x > 1)
                {
                    CPen* pOldPen;
                    CPen linePen (PS_SOLID, 1, m_clrRef);
                    pOldPen = pDC->SelectObject(&linePen);
                    pDC->MoveTo(lastXLoc , lastYLoc);
                    pDC->LineTo(tickXLocation, yDataLocation);
                    pDC->SelectObject(pOldPen);
                }
                //now draw ellipse...
                pDC->Ellipse(tickXLocation -2, yDataLocation - 2,
                    tickXLocation + 2, yDataLocation + 2);
                lastXLoc = tickXLocation;
                lastYLoc = yDataLocation;
                pDC->SelectObject(&pOldBrush);
            }
        }
    }

    if(m_GraphType == 2)  //pie
    {
        double dataSum = 0.00;  //for storing cumulative sum
        int lastXLocation, lastYLocation;
        int newXLocation, newYLocation;
        double percent = 0.00;
        int degrees;
        double totalSum = 0.00;
        int deltaXY;
        int radius;
            
        lastXLocation = 0;
        lastYLocation = 0;
        pDC->SetBkMode(TRANSPARENT);
        //determine width of pie display area
        if(m_bGraphHasLegend)
            if(((m_iXAxisWidth - m_iLegendWidth - 5) 
                / m_pGraphSeries->GetCount())
               > (m_iYAxisHeight - 10))
                seriesSpace = (int)((m_iYAxisHeight - 5) 
                              / m_pGraphSeries->GetCount());
            else
                seriesSpace = (int)((m_iXAxisWidth - m_iLegendWidth - 5) 
                              / m_pGraphSeries->GetCount());
        else
            if(m_iXAxisWidth > m_iYAxisHeight)
                seriesSpace = (int)(m_iYAxisHeight / m_pGraphSeries->GetCount());
            else
                seriesSpace = (int)(m_iXAxisWidth / m_pGraphSeries->GetCount());
        double tmpD = (seriesSpace - 20)* .9;  //max width of any pie
        radius = (int)(tmpD / 2);  

        int centerYPie = m_iYAxisHeight / 2;
        
        pos = m_pGraphSeries->GetHeadPosition();
        for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
        {
            tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);
            totalSum = 0;
            for(int s = 0; s < 10; s++)
                totalSum += tmpSeries->GetData(s);
            int pieLeft, pieRight;
            if(m_pGraphSeries->GetCount() == 1)
            {
                pieLeft = ((m_iXAxisWidth - m_iLegendWidth - 5) / 2) - radius
                          - 15;
            }
            else
            {
                pieLeft = m_iXApexPoint + 25 + (x * 50) + ((x - 1) 
                          * (2 * radius));
            }
            pieRight = pieLeft + (2 * radius);
            CRect pieRect (pieLeft, 
                    centerYPie - radius,
                    pieRight, 
                    centerYPie + radius);
            int centerXPie = pieLeft + radius;

            //plot series label
            pDC->TextOut(centerXPie 
                            - ((tmpSeries->strGetLabel().GetLength() * 8) / 2),
                         centerYPie + radius + 30, tmpSeries->strGetLabel());
            lastXLocation = pieLeft;
            lastYLocation = centerYPie;
            
            dataSum = 0;
            for(int s = 0; s < 10; s++)
            {
                if(tmpSeries->GetData(s) > 0)
                {
                    dataSum += tmpSeries->GetData(s);
                    percent = (dataSum * 100) / totalSum;
                    degrees = (int)((360 * percent) / 100);

                        //degress / 90 will never exceed 4.
                        //this can tell us the quadrant of destination
                    deltaXY = (degrees * radius) / 90;
                        //deltaXY is change from start point of pie 0
                        //this value is total change.  so if radius is 300
                        //and degrees is 270, delta is 300.  The change 
                        //would move both x and y 300 pixels.  For x, 100
                        //to right is center, another 100 to right edge,
                        //100 back to center.  For y, 100 to bottom, 100
                        //back to center, 100 to top. thus gives 270 degree
                        //rotation.

                    //determine destination quadrant...
                        //and set newXLocation and newYLocation values...
                    int quadrant = degrees / 90;  //truncates decimal
                    switch(quadrant)
                    {
                        //in the computations below, the remarked line is
                        //the original computation.  The line above it, for
                        //actual use, is the simplified line, and gives the
                        //exact same result
                        case 0 : newXLocation = pieLeft + deltaXY;
                                 newYLocation = centerYPie + deltaXY;
                                 break;
                        case 1 : newXLocation = pieLeft + deltaXY;
                                 newYLocation = centerYPie + (2 * radius)
                                                - deltaXY;
//                                 newYLocation = centerYPie + radius
//                                              - (deltaXY - radius);
                                 break;
                        case 2 : newXLocation = pieLeft + (4 * radius)
                                                - deltaXY;
//                                 newXLocation = pieLeft + (2 * radius)
//                                              - (deltaXY - (2 * radius));
                                 newYLocation = centerYPie + (2 * radius)
                                                - deltaXY;
//                                 newYLocation = centerYPie
//                                              - (deltaXY - (2 * radius));
                                 break;
                        case 3 : newXLocation = pieLeft + (4 * radius)
                                                - deltaXY;
//                                 newXLocation = pieLeft + radius
//                                              - (deltaXY - (3 * radius));
                                 newYLocation = centerYPie - (4 * radius)
                                                + deltaXY;
//                                 newYLocation = centerYPie - radius
//                                              + (deltaXY - (3 * radius));
                                 break;
                        case 4 : newXLocation = pieLeft;
                                 newYLocation = centerYPie - 1;
                                 break;
                    }
                    
                    if(s == 0)
                        lastYLocation -= 1;

                    CPoint p1 (lastXLocation, lastYLocation);
                    CPoint p2 (newXLocation, newYLocation);
                    COLORREF barColor;
                    barColor = GetColor(s);
                    CBrush brush (barColor);
                    CBrush* pOldBrush;
                    pOldBrush = pDC->SelectObject(&brush);
                    pDC->Pie(pieRect, p1, p2); 
                    pDC->SelectObject(pOldBrush);

                    lastXLocation = newXLocation;
                    lastYLocation = newYLocation;
                }
            }
            
        }
    }

}

void CGraph::SetLegend(int datagroup, CString label)
{
    m_GraphLegend.SetLegendText(datagroup, label);
    m_bGraphHasLegend = TRUE;
}

void CGraph::DrawLegend(CDC* pDC)
{
    int legendHeight =( (m_iSeriesSize * 18) )/4;
    int legendL, legendT, legendR, legendB;
    int barL, barT, barR, barB;
    CGraphSeries* pSeries =  (CGraphSeries*)m_pGraphSeries->GetHead();
    ASSERT(pSeries!=NULL);
    CFont sideFont,Font1;
    sideFont.CreateFont(-14, 0, 0, 0, 400, FALSE, FALSE, 0,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Arial"));

//    pDC->SelectObject(pOldFont);
    legendT = (m_iMaxHeight / 20) - (legendHeight / 20);
    legendB = legendT + legendHeight;
    legendR = int(m_iMaxWidth *0.99);
    legendL = legendR -int ((m_GraphLegend.GetLegendLength() * 12)*1.1);
     pDC->SetBkMode(TRANSPARENT);
        //allows 50 pixels for display of legend bar 45 + 5 space.
//    m_iLegendWidth = legendR - legendL;
    CFont* pOldFont = (CFont*) pDC->SelectObject(&sideFont);
    pDC->TextOut(int(legendR*0.55),int(legendT*0.8), _T("项组份(%)"));
    pDC->SelectObject(pOldFont);
    Font1.CreateFont(-12, 0, 0, 0, 400, FALSE, FALSE, 0,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Arial"));
    pOldFont = (CFont*) pDC->SelectObject(&Font1);
    m_iLegendWidth = int(m_iMaxWidth*0.1);
//    pDC->Rectangle(legendL, legendT, legendR, legendB);
//    pDC->TextOut(legendL + (m_iLegendWidth / 2) + 24, 
    int barLbackup= legendL 
                    + (m_GraphLegend.strGetLegendText(0).GetLength() * 8) ;
    CString str;
    for(int i = 0; i < m_iSeriesSize; i++)
    {
        //draw bar
        COLORREF barColor;
        barColor = GetColor(i);
        CBrush brush (barColor);
        CBrush* pOldBrush;
        pOldBrush = pDC->SelectObject(&brush);
        str.Format(_T("%4d"),pSeries->GetData(i));
        str+=_T("%");
    //    barL = legendL + 5
    //         + (m_GraphLegend.strGetLegendText(i).GetLength() * 8) + 5;
        barL = barLbackup;
        barT = legendT + 30 + (i * 18)
               + 1, m_GraphLegend.strGetLegendText(i);
        barR = legendR - 5;
        barB = barT + 20;
        pDC->SetBkColor(RGB(214,214,214));
        pDC->Rectangle(int(1.9*barL+10), barT,int(1.9*barL+55), barB);
        pDC->SetTextColor(barColor);
        pDC->TextOut(legendR-60, 12+legendT + (i+1) * 19, 
                     m_GraphLegend.strGetLegendText(i));
         pDC->SetBkMode(TRANSPARENT);

        pDC->TextOut(legendR-5, 12+legendT + (i+1) * 19,str);
        pDC->SelectObject(&pOldBrush);
    }
    pDC->SelectObject(&pOldFont);
}

void CGraph::SetGraphTitle(CString title)
{
    m_strGraphTitle = title;
}
void CGraph::vDrawLegendBar(CDC*pDC)
{
    int legendHeight =( (m_iSeriesSize * 18) )/4;
    int legendL, legendT, legendR, legendB;
    int barL, barT, barR, barB;
    CGraphSeries* pSeries =  (CGraphSeries*)m_pGraphSeries->GetHead();
    ASSERT(pSeries!=NULL);
    CFont sideFont,Font1;
    sideFont.CreateFont(-14, 0, 0, 0, 400, FALSE, FALSE, 0,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Arial"));
    CFont* pOldFont = (CFont*) pDC->SelectObject(&sideFont);

//    pDC->SelectObject(pOldFont);
    legendT = (m_iMaxHeight / 20) - (legendHeight / 20);
    legendB = legendT + legendHeight;
    legendR =int(m_iMaxWidth*0.99);
    legendL = legendR - int((m_GraphLegend.GetLegendLength() * 12)*1.1);
//    pDC->SetBkColor(RGB(214,214,214));
    pDC->SetBkMode(TRANSPARENT);
    pDC->TextOut(int(legendR*0.5),int(legendT*0.8), _T("转变温度(℃)"));

    Font1.CreateFont(-11, 0, 0, 0, 400, FALSE, FALSE, 0,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Arial"));
    pOldFont = (CFont*) pDC->SelectObject(&Font1);
    m_iLegendWidth =int( m_iMaxWidth*0.1);
//    pDC->Rectangle(legendL, legendT, legendR, legendB);
//    pDC->TextOut(legendL + (m_iLegendWidth / 2) + 24, 
    int barLbackup= legendL
                    + (m_GraphLegend.strGetLegendText(0).GetLength() * 8) ;
    CString str;
    for(int i = 0; i < m_iSeriesSize; i++)
    {
    
    //    pDC->TextOut(legendL + 5, legendT + 24 + (i * 18),
    //               m_GraphLegend.strGetLegendText(i));
        //draw bar
        COLORREF barColor;
        barColor = GetColor(i);
        CBrush brush (barColor);
        CBrush* pOldBrush;
        pOldBrush = pDC->SelectObject(&brush);
        str.Format(_T("%4d"),pSeries->GetData(i));
    //    barL = legendL + 5
    //         + (m_GraphLegend.strGetLegendText(i).GetLength() * 8) + 5;
        barL = barLbackup;
        barT = legendT*3+(i*16) ;
        //+ (i * 18), m_GraphLegend.strGetLegendText(i);
        barR = legendR - 5;
        barB = barT + 20;
    //    pDC->Rectangle(1.3*barL+10, barT,1.3*barL+40,barB);
    //    pDC->SetBkColor(RGB(214,214,214));
        pDC->SetTextColor(barColor);
        pDC->TextOut(int(0.95*barL), int(barB-(barB-barT)/1.4), 
                     m_GraphLegend.strGetLegendText(i));
         pDC->SetBkColor(barColor);
    //    pDC->TextOut(legendR*0.6, 11+legendT + (i+1) * 19,str);
        pDC->TextOut(int(1.3*barL+10),int(barB-(barB-barT)/1.4),str);
        pDC->SelectObject(&pOldBrush);
    }
    pDC->SelectObject(&pOldFont);
}
