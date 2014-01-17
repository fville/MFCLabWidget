#ifndef __CLABDIGPLOT_H__
#define __CLABDIGPLOT_H__

#include <math.h>
#include <vector>
#include <iostream>
#include "LabPlot.h"

template<class T>
class CLabDigPlot : public CLabPlot
{
public:
   CLabDigPlot(CLabBase *parent, double x0, double deltaX):
      CLabPlot(parent, x0, deltaX),
      _data(NULL)
   {};

   virtual ~CLabDigPlot()
   {
      if(_data != NULL)
         free(_data);
   };

   virtual void drawPlot(CDC *pDC)
   {
      int i;

      if(_data == NULL)
         return;
   
      CRgn rgn;
      CRect rect = bounds();
      rgn.CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
      pDC->SelectClipRgn(&rgn);

      CPen p(PS_SOLID, 1, color());
      CPen* pOldPen = pDC->SelectObject(&p);

      CPoint* pPoints = new CPoint[_nbPointsPerPlot * sizeof(T)*8];
      int nbPoints;
      for(i=0; i<_nbPlots; i++)
      {
         GetPolyLine(i, pPoints, &nbPoints);

         for(int j=0; j<(sizeof(T)*8); j++)
            pDC->Polyline(pPoints+(j*_nbPointsPerPlot), nbPoints);
      }

      delete[] pPoints;

      pDC->SelectObject(pOldPen);
   }

   void GetPolyLine(int plot, CPoint *pPoints, int *pNbPoints)
   {
      double nbPointsPerPixel = bounds().Width()/_nbPointsPerPlot;
      *pNbPoints = _nbPointsPerPlot;

      for(int j=0; j<_nbPointsPerPlot; j++)
      {
         T value1;
         T *data = _data;
         if(_dir == PlotDataLine)
         {
            value1 = data[plot*_nbPointsPerPlot+j];
         }
         else
         {
            value1 = data[j*_nbPlots+plot];
         }

         // plot one curve for each bit
         for(int k=0; k<(sizeof(T)*8); k++)
         {
            T val1 = (value1 >> k) & 0x1;
            
            pPoints[k*_nbPointsPerPlot + j].x = xAxis()->translateCoordinate(_x0 + j * _deltaX);
            pPoints[k*_nbPointsPerPlot + j].y = yAxis()->translateCoordinate(k + (double)val1/2.0);
         }
      }
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

      // Set y scale precision to 0
      yAxis()->setPrecision(0);
      yAxis()->setMinimum(0.0);
      yAxis()->setMaximum(sizeof(T)*8);
   }

private:
   T *_data;
};

#endif //__CLABDIGPLOT_H__

