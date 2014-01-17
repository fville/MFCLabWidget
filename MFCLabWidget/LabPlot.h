#ifndef __QLABPLOT_H__
#define __QLABPLOT_H__

#include <math.h>
#include <vector>
#include "LabBase.h"
#include "LabScale.h"

typedef enum _plotDataDirection
{
   PlotDataColumn,
   PlotDataLine
} tPlotDataDirection;

typedef enum _graphType
{
   StripChart,
   ScopeChart,
   YGraph,
   XYGraph,
   Digital
} tGraphType;

class CLabPlot
{
public: 
   CLabPlot(CLabBase *parent, double x0, double deltaX):
   _plotColor(RGB(0,255,0)),
   _xAxis(NULL),
   _yAxis(NULL),
   _nbPointsPerPlot(0),
   _nbPlots(0),
   _nbTraces(1),
   _x0(x0),
   _deltaX(deltaX),
   _parent(parent)
   {
   }

   virtual ~CLabPlot()
   {
   }

   virtual void drawPlot(CDC *pDC) = 0;

   CRect bounds()
   {
      return _bounds;
   }

   void setBounds(CRect bounds)
   {
      _bounds = bounds;
   }

   
   void setXAxis(CLabScale *scale)
   {
      _xAxis = scale;
   }

   void setYAxis(CLabScale *scale)
   {
      _yAxis = scale;
   }

   CLabScale *xAxis()
   {
      return _xAxis;
   }

   CLabScale *yAxis()
   {
      return _yAxis;
   }

   void setColor(COLORREF color)
   {
      _plotColor = color;
   }

   COLORREF color()
   {
      return _plotColor;
   }

   void setNbTraces(int nbTraces)
   {
      _nbTraces = nbTraces;
   }

   void setX0(double x0)
   {
      _x0 = x0;
   }

   double x0()
   {
      return _x0;
   }

   void setDeltaX(double deltaX)
   {
      _deltaX = deltaX;
   }

   double deltaX()
   {
      return _deltaX;
   }   

protected:
   CLabBase *_parent;
   int _nbTraces;
   int _nbPointsPerPlot;
   int _nbPlots;
   tPlotDataDirection _dir;
   double  _x0;
   double  _deltaX;

private:
   CRect _bounds;
   COLORREF _plotColor;
   CLabScale *_xAxis;
   CLabScale *_yAxis;
};

#endif //__QLABPLOT_H__

