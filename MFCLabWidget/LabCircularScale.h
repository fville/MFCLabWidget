#ifndef __QLABCIRCULARSCALE_H__
#define __QLABCIRCULARSCALE_H__

#include "LabBase.h"
#include "LabScale.h"
  
#define PI  3.14159                           
  
class CLabCircularScale : public CLabScale
{
public:
   CLabCircularScale(CLabBase *parent, double minimum = 0.0, double maximum = 10.0, double increment = 1.0);
   
   float startAngle()
   {
      return _startAngle;
   }

   void setStartAngle(float startAngle)
   {
      _startAngle = startAngle;
   }

   float arcAngle()
   {
      return _arcAngle;
   }

   void setArcAngle(float arcAngle)
   {
      _arcAngle = arcAngle;
   }

   virtual void drawScale(CDC *pDC);
   virtual int translateCoordinate(double coord);
   virtual double translateScreenCoordinate(int coord);
   virtual int getScaleLength();

private:
   float _startAngle;
   float _arcAngle;
};

#endif // __QLABCIRCULARSCALE_H__
