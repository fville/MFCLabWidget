#ifndef __QLABNUMERIC_H__
#define __QLABNUMERIC_H__

#ifndef __QLABBASE_H__
#include "QLabBase.h"
#endif

class QLabNumeric : public QLabBase
{
   Q_OBJECT
public:
   QLabNumeric(QWidget *parent=0, const char *name=0, WFlags f=0);
   virtual ~QLabNumeric(){};

   virtual void drawControl(QPaintDevice &device);
   virtual QSize sizeHint(void);

   int precision()
   {
      return _precision;
   }

   void setPrecision(int precision)
   {
      _precision = precision;
      repaint(false);
   }

   double value()
   {
      return _value;
   }

public slots:
   void setValue(double value)
   {
      _value = value;
      repaint(false);
   }
  
private:
   double _value;
   int    _precision;  
   int    _borderSize;
   int    _spacing;
};

#endif // __QLABNUMERIC_H__

