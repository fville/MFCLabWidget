#ifndef __QLABGRID_H__
#define __QLABGRID_H__

#include <math.h>
#include "LabBase.h"
#include "LabScale.h"

class CLabGrid
{
public: 
   CLabGrid(CLabBase *parent):_color(RGB(0,255,0)), _xAxis(NULL), _yAxis(NULL) {};
   virtual ~CLabGrid(){};

   void drawGrid(CDC *pDC)
   {
      CPen p(PS_SOLID, 1, _color);
      CPen pd(PS_SOLID, 1, DARKER(_color));
      CPen *pOldPen = pDC->SelectObject(&p);

      CRgn rgn;
      CRect rect = bounds();
      rgn.CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
      pDC->SelectClipRgn(&rgn);

      for(double x=_xAxis->getTickMin(); x<=_xAxis->maximum(); x=x+_xAxis->tickIncrement())
      {
         double temp = x/(_xAxis->majorTickFrequency()*_xAxis->tickIncrement());
         if(temp == ceil(temp))
         {
            pDC->SelectObject(&p);
         }
         else
         {
           pDC->SelectObject(&pd);
         }

         pDC->MoveTo(_xAxis->translateCoordinate(x), _yAxis->translateCoordinate(_yAxis->minimum()));
         pDC->LineTo(_xAxis->translateCoordinate(x),
                     _yAxis->translateCoordinate(_yAxis->maximum()));
      }

      for(double y=_yAxis->getTickMin(); y<=_yAxis->maximum(); y=y+_yAxis->tickIncrement())
      {
         double temp = y/(_yAxis->majorTickFrequency()*_yAxis->tickIncrement());
         if(temp == ceil(temp))
         {
            pDC->SelectObject(&p);
         }
         else
         {
            pDC->SelectObject(&pd);
         }

         pDC->MoveTo(_xAxis->translateCoordinate(_xAxis->minimum()),
                     _yAxis->translateCoordinate(y));
         pDC->LineTo(_xAxis->translateCoordinate(_xAxis->maximum()),
                     _yAxis->translateCoordinate(y));
      }

      pDC->SelectObject(pOldPen);
   }

   
   void setXAxis(CLabScale *axis)
   {
      _xAxis = axis;
   }

   void setYAxis(CLabScale *axis)
   {
      _yAxis = axis;
   }

   CRect bounds()
   {
      return _bounds;
   }

   void setBounds(CRect bounds)
   {
      _bounds = bounds;
   }

   void setColor(COLORREF color)
   {
      _color = color;
   }
   
protected:
   CLabBase *_parent;

private:
   CRect    _bounds;
   COLORREF   _color;
   CLabScale *_xAxis;
   CLabScale *_yAxis;
};

#endif //__QLABGRID_H__

