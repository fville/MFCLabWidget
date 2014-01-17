#ifndef __QLABVERTSCALE_H__
#define __QLABVERTSCALE_H__

#include "LabScale.h"


class CLabVertScale : public CLabScale
{
public: 
   CLabVertScale(CLabBase *parent, double minimum = 0.0, double maximum = 10.0, double increment = 1.0);
   virtual ~CLabVertScale(){};

   virtual void drawScale(CDC *pDC);
   virtual int translateCoordinate(double coord);
   virtual double translateScreenCoordinate(int coord);
   virtual int getScaleLength();
};

#endif //__QLABVERTSCALE_H__

