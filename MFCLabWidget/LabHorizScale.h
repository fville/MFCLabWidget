#ifndef __QLABHORIZSCALE_H__
#define __QLABHORIZSCALE_H__

#include "LabScale.h"


class CLabHorizScale : public CLabScale
{
public: 
   CLabHorizScale(CLabBase *parent, double minimum = 0.0, double maximum = 10.0, double increment = 1.0);
   virtual ~CLabHorizScale(){};

   virtual void drawScale(CDC *pDC);
   virtual int translateCoordinate(double coord);
   virtual double translateScreenCoordinate(int coord);
   virtual int getScaleLength();
};

#endif //__QLABHORIZSCALE_H__

