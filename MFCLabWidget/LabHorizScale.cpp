#include "stdafx.h"
#include "LabHorizScale.h"


CLabHorizScale::CLabHorizScale(CLabBase *parent, double minimum, double maximum, double increment):
CLabScale(parent, minimum, maximum, increment)
{
}


void CLabHorizScale::drawScale(CDC *pDC)
{
   int tickLength;
   
   CRgn rgn;
   CRect rect = bounds();
   rgn.CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
   pDC->SelectClipRgn(&rgn);
      
   for(double x=getTickMin(); x<=maximum(); x=x+tickIncrement())
   {
      double temp = x/(majorTickFrequency()*tickIncrement());
      if(temp == ceil(temp))
         tickLength = 7;
      else
         tickLength = 3;


      pDC->MoveTo(translateCoordinate(x), rect.top);
      pDC->LineTo(translateCoordinate(x), rect.top + tickLength);

      temp = x/(tickMarkFrequency() * tickIncrement());
      if(temp == ceil(temp))
      {
         CString tickMarkStr;
         tickMarkStr.Format("%.*f", precision(), x);
         
         pDC->TextOut(translateCoordinate(x) - _parent->getCharWidth() * tickMarkStr.GetLength()/2, 
                      rect.top + 7 /* _parent->getCharHeight()*/, 
                      tickMarkStr);

      }
   }
}


// translate the value to a screen coordinate that we can then use
// to draw the ticks
int CLabHorizScale::translateCoordinate(double coord)
{
   int pixCoord = (int)((coord - minimum()) * (bounds().Width()-1) / (maximum() - minimum()));
   return(bounds().left + pixCoord);
}

double CLabHorizScale::translateScreenCoordinate(int coord)
{
   double value = (coord - bounds().left) * (maximum() - minimum()) / (bounds().Width()-1);
   return(value + minimum());
}

int CLabHorizScale::getScaleLength()
{
   return bounds().Width();
}
