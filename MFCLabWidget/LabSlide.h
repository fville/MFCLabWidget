#ifndef __QLABSLIDE_H__
#define __QLABSLIDE_H__

#ifndef __QLABBASE_H__
#include "QLabBase.h"
#endif

class QLabScale;

class QLabSlide : public QLabBase
{
   Q_OBJECT

public:
   typedef enum _orientationTag
   {
      horizontal,
      vertical
   } tOrientation;

   typedef enum _scaleSideTag
   {
      leftOrBottom,
      rightOrTop
   } tScaleSide;

   typedef enum _sliderTypeTag
   {
      SimpleSlider,
      RectangleSlider,
      TriangleSlider,
      CustomSlider
   } tSliderType;

   QLabSlide(QWidget *parent=0, const char *name=0, WFlags f=0);
   virtual ~QLabSlide(){};

   
   virtual void mousePressEvent(QMouseEvent *);
   virtual void mouseReleaseEvent(QMouseEvent *);
   virtual void mouseMoveEvent(QMouseEvent *);
   virtual void resizeEvent(QResizeEvent *);

   double value()
   {
      return _value;
   }

   QLabScale* scale()
   {
      return _scale;
   }

   int getBorder()
   {
      return _borderSize;
   }

   void setBorder(int border)
   {
      _borderSize = border;
   }

   tOrientation orientation()
   {
      return _orientation;
   }

   void setOrientation(tOrientation newOrientation)
   {
      _orientation = newOrientation;
      setScale();
      repaint(false);
   }

   tSliderType type()
   {
      return _sliderType;
   }

   void setType(tSliderType newType)
   {
      _sliderType = newType;
      repaint(false);
   }

   virtual void drawControl(QPaintDevice &device);
   virtual QSize sizeHint(void);

public slots:
   void setValue(double newValue);

private:
   void drawSlider(QPainter *p);
   void setScale();
   QPoint getSliderPos();
   void loadSimpleSlider(QSize sliderSize);
   void loadRectangleSlider(QSize sliderSize);
   void loadTriangleSlider(QSize sliderSize);
   void loadCustomSlider(QSize sliderSize);

signals:
   void valueChanged(double value);

private:
   int _scaleBorderSize; 
   int _borderSize;
   double _value;
   double _oldValue;
   QLabScale *_scale;
   bool _showValue;

   bool _clicked;
   QPoint _lastMousePos;
   QRect _fillArea;
   tOrientation _orientation;
   tScaleSide _scaleSide;
   QPixmap _slider;
   QPoint _sliderPos;
   tSliderType _sliderType;
   QColor _fillColor;
   QColor _sliderColor;
};

#endif // __QLABSLIDE_H__

