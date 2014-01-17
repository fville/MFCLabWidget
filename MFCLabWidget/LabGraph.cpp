#include "stdafx.h"
#include <math.h>
#include "LabGraph.h"

#define PI  3.14159

BEGIN_MESSAGE_MAP(CLabGraph, CLabBase)
	//{{AFX_MSG_MAP(CLabGraph)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CLabGraph::CLabGraph():
CLabBase(),
_leftBorderSize(30),
_bottomBorderSize(30),
_borderSize(8),
_drawArea(_borderSize + _leftBorderSize, _borderSize, 400, 325),
_yAxis(this),
_xAxis(this),
_backgroundColor(RGB(0,0,0)),
_grid(this),
_type(YGraph)
{
   RegisterWindowClass();
   _grid.setXAxis(static_cast<CLabScale *>(&_xAxis));
   _grid.setYAxis(static_cast<CLabScale *>(&_yAxis));
}


BOOL CLabGraph::Create(const RECT& rect, CWnd* pParentWnd, UINT nID) 
{
	return CWnd::CreateEx(WS_EX_CLIENTEDGE, "MFCLabGraph", _T(""),
		0x50010000, rect, pParentWnd, nID);
}


BOOL CLabGraph::RegisterWindowClass()
{
   WNDCLASS wndcls;
   HINSTANCE hInst = AfxGetInstanceHandle();
   HBRUSH background;
   background = ::GetSysColorBrush(COLOR_BTNFACE);

   if (!(::GetClassInfo(hInst, "MFCLabGraph", &wndcls)))
   {
      // otherwise we need to register a new class
      wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
      wndcls.lpfnWndProc      = ::DefWindowProc;
      wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
      wndcls.hInstance        = hInst;
      wndcls.hIcon            = NULL;
      wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
      wndcls.hbrBackground    = background;
      wndcls.lpszMenuName     = NULL;
      wndcls.lpszClassName    = "MFCLabGraph";

      if (!AfxRegisterClass(&wndcls))
      {
         AfxThrowResourceException();
         return FALSE;
      }
   }

   return TRUE;
}


/*void CLabGraph::mousePressEvent(QMouseEvent *e)
{
   // Deal with event related to curosr manipulation
}


void CLabGraph::mouseReleaseEvent(QMouseEvent *e)
{
   // Deal with events related to cursor manipulation
}


void CLabGraph::mouseMoveEvent(QMouseEvent *e)
{
   // Deal with events related to cursor manipulation
}*/

void CLabGraph::Layout(int cx, int cy)
{
   if(cx > (2 * _borderSize + _leftBorderSize))
      _drawArea.right = _drawArea.left + cx - 2 * _borderSize - _leftBorderSize;
   else
      _drawArea.right = _drawArea.left;

   if(cy > (2 * _borderSize + _bottomBorderSize))
      _drawArea.bottom = _drawArea.top + cy - 2 * _borderSize - _bottomBorderSize;
   else
      _drawArea.bottom = _drawArea.top;
}

void CLabGraph::addPlot(COLORREF plotColor, std::string label)
{
   CLabPlot *newPlot;
   switch(_type)
   {
   case YGraph:
      newPlot = new CLabYPlot<double>(this, 0.0, 1.0);
      break;
   case Digital:
      newPlot = new CLabDigPlot<unsigned short>(this, 0.0, 1.0);
      break;
   case StripChart:
   case ScopeChart:
      newPlot = new CLabChartPlot<double>(this, 0.0, 1.0);
      break;
   case XYGraph:
   default:
      break;
   }

   newPlot->setXAxis(static_cast<CLabScale *>(&_xAxis));
   newPlot->setYAxis(static_cast<CLabScale *>(&_yAxis));
   newPlot->setColor(plotColor);

   _yplots.push_back(newPlot);
}

void CLabGraph::plotappend(int plotIndex, double *data, int nbPlots, double x0, double deltaX, bool bRepaint)
{
   CLabChartPlot<double>* pPlot = dynamic_cast<CLabChartPlot<double>*>(_yplots[plotIndex]);
   if(pPlot != NULL)
   {
      pPlot->setX0(x0);
      pPlot->setDeltaX(deltaX);
      pPlot->addData(data, nbPlots);

      if(bRepaint)
         Invalidate();
   }
}

void CLabGraph::yplot(int plotIndex, double *data, int nbOfPoints, double x0, double deltaX, bool bRepaint)
{
   CLabYPlot<double>* pPlot = dynamic_cast<CLabYPlot<double>*>(_yplots[plotIndex]);
   if(pPlot != NULL)
   {
      pPlot->setX0(x0);
      pPlot->setDeltaX(deltaX);
      pPlot->setData(data, nbOfPoints);

      if(bRepaint)
         Invalidate();
   }
}

void CLabGraph::yplot(int plotIndex, unsigned short *data, int nbOfPoints, double x0, double deltaX, bool bRepaint)
{
   CLabDigPlot<unsigned short>* pPlot = dynamic_cast<CLabDigPlot<unsigned short>*>(_yplots[plotIndex]);
   if(pPlot != NULL)
   {
      pPlot->setX0(x0);
      pPlot->setDeltaX(deltaX);
      pPlot->setData(data, nbOfPoints);

      if(bRepaint)
         Invalidate();
   }
}

void CLabGraph::yplotmultiple(int nbPlots, double *data, int nbOfPointsPerPlot, double x0, double deltaX, tPlotDataDirection dir,bool bRepaint)
{
   CLabYPlot<double>* pPlot = dynamic_cast<CLabYPlot<double>*>(_yplots[0]);
   if(pPlot != NULL)
   {
      pPlot->setX0(x0);
      pPlot->setDeltaX(deltaX);
      pPlot->setData(data, nbOfPointsPerPlot, nbPlots, dir);

      if(bRepaint)
         Invalidate();
   }
}  

void CLabGraph::yplotmultiple(int nbPlots, unsigned short *data, int nbOfPointsPerPlot, double x0, double deltaX, tPlotDataDirection dir,bool bRepaint)
{
   CLabDigPlot<unsigned short>* pPlot = dynamic_cast<CLabDigPlot<unsigned short>*>(_yplots[0]);
   if(pPlot != NULL)
   {
      pPlot->setX0(x0);
      pPlot->setDeltaX(deltaX);
      pPlot->setData(data, nbOfPointsPerPlot, nbPlots, dir);

      if(bRepaint)
         Invalidate();
   }
}  

void CLabGraph::drawControl(CDC *pDC, CRect& rect)
{
   // draw graph background
   CBrush brush1;
   brush1.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));      
   pDC->FillRect(rect, &brush1); 
      
   // draw rectangle around the control
   drawRaisedFrame(pDC, rect, RGB(255,255,255));

   // draw graph background
   CBrush brush2;
   brush2.CreateSolidBrush(_backgroundColor);
   pDC->FillRect(_drawArea, &brush2);  

   // draw axis
   _yAxis.setBounds(CRect(_borderSize, _borderSize, _borderSize+_leftBorderSize, _borderSize+_drawArea.Height()));
   _yAxis.drawScale(pDC);

   _xAxis.setBounds(CRect(_borderSize + _leftBorderSize, 
                          _borderSize + _drawArea.Height(),
                          _borderSize + _leftBorderSize + _drawArea.Width(), 
                          _borderSize + _drawArea.Height() + _bottomBorderSize));
   _xAxis.drawScale(pDC);
   
   _grid.setBounds(_drawArea);
   _grid.drawGrid(pDC);

   std::vector<CLabPlot* >::iterator plotIt;
   for(plotIt = _yplots.begin(); plotIt != _yplots.end(); plotIt++)
   {
      (*plotIt)->setBounds(_drawArea);
      (*plotIt)->drawPlot(pDC);
   }
}  



