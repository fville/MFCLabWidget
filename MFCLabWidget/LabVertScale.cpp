#include "stdafx.h"
#include "LabVertScale.h"

CLabVertScale::CLabVertScale(CLabBase *parent, double minimum, double maximum, double increment):
CLabScale(parent, minimum, maximum, increment)
{
}


void CLabVertScale::drawScale(CDC *pDC)
{
   int tickLength;
   
   CRgn rgn;
   CRect rect = bounds();
   rgn.CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
   pDC->SelectClipRgn(&rgn);
            
   for(double y=getTickMin(); y<=maximum(); y=y+tickIncrement())
   {
      double temp = y/(majorTickFrequency()*tickIncrement());
      if(temp == ceil(temp))
         tickLength = 7;
      else
         tickLength = 3;

      pDC->MoveTo(rect.right - tickLength, translateCoordinate(y));
      pDC->LineTo(rect.right, translateCoordinate(y));

      temp = y/(tickMarkFrequency() * tickIncrement());
      if(temp == ceil(temp))
      {
         CString tickMarkStr;
         tickMarkStr.Format("%.*f", precision(), y);
         
         pDC->TextOut(rect.left, translateCoordinate(y) - _parent->getCharHeight() /2, 
                     tickMarkStr);

      }
   }
}


// translate the value to an angle that we can then use
// to draw the ticks
int CLabVertScale::translateCoordinate(double coord)
{
   int pixCoord = (int)((maximum() - coord) * (bounds().Height()-1) / (maximum() - minimum()));
   return(bounds().top + pixCoord);
}


double CLabVertScale::translateScreenCoordinate(int coord)
{
   double value = (coord - bounds().top) * (maximum() - minimum()) / (bounds().Height()-1);
   return(maximum() - value);
}


int CLabVertScale::getScaleLength()
{
   return bounds().Height();
}

