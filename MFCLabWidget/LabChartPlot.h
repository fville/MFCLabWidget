#ifndef __CLABCHARTPLOT_H__
#define __CLABCHARTPLOT_H__

#include <math.h>
#include <vector>
#include <iostream>
#include "LabPlot.h"

template<class T>
class CLabChartPlot : public CLabPlot
{
public:
   CLabChartPlot(CLabBase *parent, double x0, double deltaX):
      CLabPlot(parent, x0, deltaX),
      _data(NULL),
      _currentPoint(0),
      _historyLength(1000),
      _numTotalPoints(0),
      _min(DBL_MAX),
      _max(-DBL_MAX)
   {
   };
   virtual ~CLabChartPlot()
   {
      if(_data != NULL)
         free(_data);
   };

   virtual void drawPlot(CDC *pDC)
   {
      int i,j,k;

      if(_data == NULL)
         return;

      int numPointsPerChart = (int)((xAxis()->maximum() - xAxis()->minimum())/_deltaX);
         
      CRgn rgn;
      CRect rect = bounds();
      rgn.CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
      pDC->SelectClipRgn(&rgn);

      COLORREF col = color();
      CPen p(PS_SOLID, 1, color());
      CPen* pOldPen = pDC->SelectObject(&p);

      tGraphType type = ((CLabGraph*)_parent)->getType();

      for(k=0; k<_nbTraces; k++)
      {
         CPen pt(PS_SOLID, 1, col);
         pDC->SelectObject(&pt);
         for(i=0; i<_nbPlots; i++)
         {
            int numPoints = _numTotalPoints < numPointsPerChart ? _numTotalPoints : numPointsPerChart; 
            int firstPoint;
            
            if(_currentPoint < numPoints)
            {
               firstPoint = _historyLength - numPoints + _currentPoint;
            }
            else
            {
               firstPoint = _currentPoint-numPoints;
            }

            //TRACE("FirstPoint = %d, NumPoints=%d\n", firstPoint, numPoints);

            T val = _data[i*_historyLength+firstPoint];
            
            int lastX = xAxis()->translateCoordinate(0);
            int lastY =  yAxis()->translateCoordinate(val);

            for(j=0; j<(numPoints-1); j++)
            {
               int x, y;
               int nextPoint;
               if((firstPoint+j) >= _historyLength)
               {
                  nextPoint = firstPoint+j - _historyLength;
               }
               else
               {
                  nextPoint = firstPoint+j;
               }

               val = _data[i*_historyLength+nextPoint];

               x = xAxis()->translateCoordinate((j+1) * _deltaX);
               y = yAxis()->translateCoordinate(val);
                              
               pDC->MoveTo(lastX, lastY);
               pDC->LineTo(x, y);

               lastX = x;
               lastY = y;
            }
         }

         col = DARKER(col);
      }

      pDC->SelectObject(pOldPen);
   }

   void addData(T *data, int nbPlots)
   {     
      _dir = PlotDataColumn;
   
      if(_nbPlots != nbPlots)
      {
         if(_data != NULL)
            free(_data);

         _data = (T*)malloc(_historyLength*nbPlots*sizeof(T));
         _nbPlots = nbPlots;
      }

      if(_currentPoint >= _historyLength)
         _currentPoint = 0;
      
      for(int i=0; i<nbPlots; i++)
      {
         _data[i*_historyLength + _currentPoint] = data[i];
         if(data[i] < _min)
            _min = data[i];
         if(data[i] > _max)
            _max = data[i];
      }

      if(yAxis()->autoScale())
      {        
         yAxis()->setMinimum(floor(_min));
         yAxis()->setMaximum(floor(_max+0.5));
         //yAxis()->setTickIncrement((_max - _min) / 10.0);
      }

      _currentPoint++;
      _numTotalPoints++;
   }   

private:
   T *_data;
   int _historyLength;
   int _currentPoint;
   int _numTotalPoints;
   double _min;
   double _max;
};

#endif //__CLABCHARTPLOT_H__

