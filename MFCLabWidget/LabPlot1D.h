#ifndef __QLABPLOT1D_H__
#define __QLABPLOT1D_H__

#include <math.h>
#include <vector>
#include <iostream>
#include "LabPlot.h"

template<class T>
class CLabPlot1D : public CLabPlot<T, 1>
{
public:
   CLabPlot1D(CLabBase *parent, T x0, T deltaX):CLabPlot<T, 1>(parent),_x0(x0),_deltaX(deltaX)
   {};
   virtual ~CLabPlot1D(){};

   virtual void drawPlot(CDC *pDC)
   {
      int i,j,k;

      if(_data == NULL)
         return;
   
      CRgn rgn;
      CRect rect = bounds();
      rgn.CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
      pDC->SelectClipRgn(&rgn);

      COLORREF col = color();
      CPen p(PS_SOLID, 1, color());
      CPen* pOldPen = pDC->SelectObject(&p);

      for(k=0; k<_nbTraces; k++)
      {
         CPen pt(PS_SOLID, 1, col);
         pDC->SelectObject(&pt);
         for(i=0; i<_nbPlots; i++)
         {
            for(j=0; j<(_nbPointsPerPlot-1); j++)
            {
               T value1, value2;
               T *data = _data + k*(_nbPlots*_nbPointsPerPlot);
               if(_dir == PlotDataLine)
               {
                  value1 = data[i*_nbPointsPerPlot+j];
                  value2 = data[i*_nbPointsPerPlot+j+1];
               }
               else
               {
                  value1 = data[j*_nbPlots+i];
                  value2 = data[(j+1)*_nbPlots+i];
               }
               pDC->MoveTo(xAxis()->translateCoordinate(_x0 + j * _deltaX), yAxis()->translateCoordinate(value1));
               pDC->LineTo(xAxis()->translateCoordinate(_x0 + (j+1) * _deltaX), yAxis()->translateCoordinate(value2));
            }
         }

         col = DARKER(col);
      }

      pDC->SelectObject(pOldPen);
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

   
private:
   double  _x0;
   double  _deltaX;
};

#endif //__QLABPLOT1D_H__

