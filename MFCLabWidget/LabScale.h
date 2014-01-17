#ifndef __CLabScale_H__
#define __CLabScale_H__

#include <math.h>
#include "LabBase.h"

class CLabScale
{
public: 
   CLabScale(CLabBase *parent, double minimum = 0.0, double maximum = 10.0, double increment = 1.0);
   virtual ~CLabScale(){};

   virtual void drawScale(CDC *pDC) = 0;
   virtual int translateCoordinate(double coord) = 0;
   virtual double translateScreenCoordinate(int coord) = 0;
   virtual int getScaleLength() = 0;

   double getTickSpace();
   
   double minimum()
   {
      return _min;
   }

   void setMinimum(double min)
   {
      _min = min;
   }

   double maximum()
   {
      return _max;
   }

   void setMaximum(double max)
   {
      _max = max;
   }

   CRect bounds()
   {
      return _bounds;
   }

   void setBounds(CRect bounds)
   {
      _bounds = bounds;
   }

   double tickIncrement()
   {
      return _tickIncrement;
   }

   void setTickIncrement(double newTickIncrement)
   {
      _tickIncrement = newTickIncrement;
   }

   int majorTickFrequency()
   {
      return _majorTickFrequency;
   }

   int tickMarkFrequency()
   {
      return _tickMarkFrequency;
   }

   double getTickMin()
   {
      // get closest tick greater than minimum
     return(ceil(_min / _tickIncrement) * _tickIncrement);
   }

   inline int precision()
   {
      return _precision;
   }

   inline void setPrecision(int precision)
   {
      _precision = precision;
   }

   inline bool autoScale()
   {
      return _autoScale;
   }

   inline void setAutoScale(bool autoScale)
   {
      _autoScale = autoScale;
   }

protected:
   CLabBase *_parent;

private:
   double _min;
   double _max;
   CRect _bounds;
   bool _logMapping;
   double _tickIncrement;
   int _nbOfTick;
   int _majorTickFrequency;
   int _tickMarkFrequency;
   int _precision;
   bool _autoScale;
};

#endif //__CLabScale_H__

