#ifndef __CLABGRAPH_H__
#define __CLABGRAPH_H__ 

#include "LabBase.h"
#include "LabVertScale.h"
#include "LabHorizScale.h"
#include "LabGrid.h"
#include "LabYPlot.h"
#include "LabChartPlot.h"
#include "LabDigPlot.h"
#include <vector>
#include <list>
#include <string>


class CLabGraph : public CLabBase
{
public:
   CLabGraph();
   virtual ~CLabGraph(){ clear(); };
   BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID);

   /*virtual void mousePressEvent(QMouseEvent *);
   virtual void mouseReleaseEvent(QMouseEvent *);
   virtual void mouseMoveEvent(QMouseEvent *);*/

   int getBorder()
   {
      return _borderSize;
   }

   void setBorder(int border)
   {
      _borderSize = border;
   }

   tGraphType getType()
   {
      return _type;
   }

   void setType(tGraphType type)
   {
      _type = type;
   }

   CRect& getDrawArea()
   {
      return _drawArea;
   }

   CLabScale *xAxis()
   {
      return &_xAxis;
   }

   CLabScale *yAxis()
   {
      return &_yAxis;
   }

   void addPlot(COLORREF plotColor, std::string label);

   void yplot(int plotIndex, unsigned short* data, int nbOfPoints, double x0 = 0.0, double deltaX = 1.0, bool bRepaint = false);
   void yplotmultiple(int nbPlots, unsigned short* data, int nbOfPointsPerPlot, double x0 = 0.0, double deltaX = 1.0, 
                     tPlotDataDirection dir = PlotDataColumn, bool bRepaint = false); 
   
   void yplot(int plotIndex, unsigned int* data, int nbOfPoints, double x0 = 0.0, double deltaX = 1.0, bool bRepaint = false);
   void yplotmultiple(int nbPlots, unsigned int* data, int nbOfPointsPerPlot, double x0 = 0.0, double deltaX = 1.0, 
                     tPlotDataDirection dir = PlotDataColumn, bool bRepaint = false); 
   
   void plotappend(int plotIndex, double *data, int nbPlots, double x0 = 0.0, double deltaX = 1.0, bool bRepaint = false);
   void yplot(int plotIndex, double *data, int nbOfPoints, double x0 = 0.0, double deltaX = 1.0, bool bRepaint = false);
   void yplotmultiple(int nbPlots, double *data, int nbOfPointsPerPlot, double x0 = 0.0, double deltaX = 1.0, 
                     tPlotDataDirection dir = PlotDataColumn, bool bRepaint = false); 
   
   void xyplot(int plotIndex, double* xdata, double* ydata, int nbOfPoints, 
               double x0, double deltax, double y0, double deltay, bool bRepaint = false);
   void clear()
   {
      std::vector<CLabPlot*>::iterator it;
      for(it = _yplots.begin(); it != _yplots.end(); it++)
         delete *it;
      _yplots.clear();
   }

   virtual void drawControl(CDC *pDC, CRect& rect);


protected:
   virtual void Layout(int cx, int cy);
   BOOL RegisterWindowClass();

private:
   int _leftBorderSize;
   int _bottomBorderSize;
   int _borderSize;
   CRect _drawArea;
   CLabVertScale _yAxis;
   CLabHorizScale _xAxis;
   COLORREF _backgroundColor;
   std::vector<CLabPlot*> _yplots;
   CLabGrid _grid;
   tGraphType _type;
      
   bool _clicked;
   CPoint _lastMousePos;

   DECLARE_MESSAGE_MAP()
};


#endif // __CLABGRAPH_H__
