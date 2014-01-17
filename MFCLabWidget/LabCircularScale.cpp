#include "stdafx.h"
#include "LabCircularScale.h"


CLabCircularScale::CLabCircularScale(CLabBase *parent, double minimum, double maximum, double increment):
CLabScale(parent, minimum, maximum, increment)
{
   _startAngle = 240;
   _arcAngle = 300;
}


void CLabCircularScale::drawScale(CDC *pDC)
{
   int tickSpace = 10;
   int tickLength;
   double xPointerVec;
   double yPointerVec;
   int radius = bounds().Width()/2-tickSpace;
   CPoint center = bounds().CenterPoint();
      
   /*CRgn rgn;
   CRect rect = bounds();
   rgn.CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
   pDC->SelectClipRgn(&rgn);*/

   CPen p(PS_SOLID, 1, RGB(0,0,0));
   CPen* pOldPen = pDC->SelectObject(&p);

   int startX = center.x + (int)(radius * cos(translateCoordinate(minimum())/100.0));
   int startY = center.y - (int)(radius * sin(translateCoordinate(minimum())/100.0));
   int stopX = center.x + (int)(radius * cos(translateCoordinate(maximum())/100.0));
   int stopY = center.y - (int)(radius * sin(translateCoordinate(maximum())/100.0));
   
   pDC->Arc(CRect(bounds().CenterPoint().x - radius, bounds().CenterPoint().y - radius,
                  bounds().CenterPoint().x + radius, bounds().CenterPoint().y + radius),
            CPoint(stopX, stopY),
            CPoint(startX, startY));

   for(double t=getTickMin(); t<=maximum(); t=t+tickIncrement())
   {
      double temp = t/(majorTickFrequency()*tickIncrement());
      if(temp == ceil(temp))
         tickLength = tickSpace;
      else
         tickLength = tickSpace-4;

      xPointerVec = cos(translateCoordinate(t)/100.0);
      yPointerVec = sin(translateCoordinate(t)/100.0);

      pDC->MoveTo(center.x + (int)(radius * xPointerVec),
                  center.y - (int)(radius * yPointerVec));
      pDC->LineTo(center.x + (int)((radius + tickLength) * xPointerVec),
                  center.y - (int)((radius + tickLength) * yPointerVec));

      
      /*temp = t/(tickMarkFrequency() * tickIncrement());
      if(temp == ceil(temp))
      {
         QString tickMarkStr;
         int precision = 2;
         tickMarkStr.sprintf("%.*f", precision, y);
         
         p->drawText(bounds().left(), translateCoordinate(y) + _parent->getCharHeight() /2, 
                     tickMarkStr);

      } */
   }

   pDC->SelectObject(pOldPen);
}


// translate the value to an angle that we can then use
// to draw the ticks, it returns the value in radian.
int CLabCircularScale::translateCoordinate(double coord)
{
   double angleIncrement = arcAngle() / (maximum() - minimum());

   if(coord < minimum())
      coord = minimum();
   else if(coord > maximum())
      coord = maximum();
      
   int pixAngle = (int)floor(((startAngle() - (coord - minimum()) * angleIncrement) * PI / 180.0)*100.0 + 0.5);
   
   return pixAngle;
}

double CLabCircularScale::translateScreenCoordinate(int coord)
{
   return 0.0;
}

int CLabCircularScale::getScaleLength()
{
   return 0;
}

