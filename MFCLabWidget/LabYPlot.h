#ifndef __CLABYPLOT_H__
#define __CLABYPLOT_H__

#include <math.h>
#include <vector>
#include <iostream>
#include "LabPlot.h"

template<class T>
class CLabYPlot : public CLabPlot
{
public:
   CLabYPlot(CLabBase *parent, double x0, double deltaX):
      CLabPlot(parent, x0, deltaX),
      _data(NULL)
   {};
   virtual ~CLabYPlot()
   {
      if(_data != NULL)
         free(_data);
   };

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

   void setData(T *data, int nbOfPoints, int nbPlots = 1, tPlotDataDirection dir=PlotDataLine)
   {     
      _dir = dir;

      if((_nbPointsPerPlot != nbOfPoints) || (_nbPlots != nbPlots))
      {
         if(_data != NULL)
            free(_data);

         _data = (T*)malloc(nbOfPoints*nbPlots*sizeof(T)*_nbTraces);
         _nbPointsPerPlot = nbOfPoints;
         _nbPlots = nbPlots;
      }

      if(_nbTraces > 1)
      {
         int bufSize = (_nbTraces-1)*_nbPlots*_nbPointsPerPlot*sizeof(T);
         T *pTemp = (T*)malloc(bufSize);
         memcpy(pTemp, _data, bufSize);
         memcpy(_data + _nbPlots*_nbPointsPerPlot, pTemp, bufSize);
         free(pTemp);
      }
      memcpy(_data, data, nbOfPoints*nbPlots*sizeof(T));

      if(yAxis()->autoScale())
      {
         double min = DBL_MAX;
         double max = -DBL_MAX;
         for(int i=0; i<nbPlots; i++)
         {
            for(int j=0; j<nbOfPoints; j++)
            {
               if(_data[i*nbOfPoints+j] < min)
                  min = _data[i*nbOfPoints+j];
               if(_data[i*nbOfPoints+j] > max)
                  max = _data[i*nbOfPoints+j];
            }
         }
         
         yAxis()->setMinimum(floor(min));
         yAxis()->setMaximum(floor(max+0.5));
         //yAxis()->setTickIncrement((max - min) / 10.0);
      }
   }

private:
   T *_data;
};

#endif //__CLABYPLOT_H__

