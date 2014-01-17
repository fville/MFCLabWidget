#include <qpainter.h>
#include <qbitmap.h>
#include <math.h>

#ifndef __QLABSLIDE_H__
#include "QLabSlide.h"
#endif

#ifndef __QLABVERTSCALE_H__
#include "QLabVertScale.h"
#endif

#ifndef __QLABHORIZSCALE_H__
#include "QLabHorizScale.h"
#endif
#include "moc_QLabSlide.cpp"

QLabSlide::QLabSlide(QWidget *parent, const char *name, WFlags f):
QLabBase(parent, name, f),
_scaleBorderSize(30),
_borderSize(8),
_scale(NULL),
_fillArea(_borderSize + _scaleBorderSize, _borderSize, 30, 200),
_orientation(vertical),
_scaleSide(leftOrBottom),
_slider(40, 40),
_sliderType(TriangleSlider),
_fillColor(black),
_sliderColor(blue)
{
   setScale();
   _value = _scale->minimum();
   _oldValue = 0.0;
  
   _sliderPos = getSliderPos();

   _showValue = false;
}

QSize QLabSlide::sizeHint(void)
{
   if (_orientation == vertical)
      return QSize(2 * _borderSize + _scaleBorderSize + _fillArea.width(), 
                   2 * _borderSize + _fillArea.height());
   else
      return QSize(2 * _borderSize + _fillArea.width(), 
                   2 * _borderSize + _scaleBorderSize + _fillArea.height());
}

void QLabSlide::setScale()
{
   QLabVertScale *pVertScale = NULL;
   QLabHorizScale *pHorizScale = NULL;
   double min = 0.0, max = 10.0;

   if (_scale != NULL)
   {
      min = _scale->minimum();
      max = _scale->maximum();
      delete _scale;
   }

   if(_orientation == vertical)
   {
      pVertScale = new QLabVertScale(this, min, max);
      _scale = static_cast<QLabScale *>(pVertScale);
   }
   else
   {
      pHorizScale = new QLabHorizScale(this, min, max);
      _scale = static_cast<QLabScale *>(pHorizScale);
   }
}

QPoint QLabSlide::getSliderPos()
{
   QPoint pos; 

   if(_orientation == vertical && _scaleSide == leftOrBottom)
      pos = QPoint(_borderSize+ _scaleBorderSize + _fillArea.width()/2-_slider.width()/2,
                    _scale->translateCoordinate(_value)-_slider.height()/2);
   
   if(_orientation == vertical && _scaleSide == rightOrTop)
      pos = QPoint(_borderSize+_fillArea.width()/2-_slider.width()/2,
                    _scale->translateCoordinate(_value)-_slider.height()/2);

   if(_orientation == horizontal && _scaleSide == rightOrTop)
      pos = QPoint(_scale->translateCoordinate(_value)-_slider.width()/2,
                    _borderSize+ _scaleBorderSize + _fillArea.height()/2-_slider.height()/2);
   
   if(_orientation == horizontal && _scaleSide == leftOrBottom)
      pos = QPoint(_scale->translateCoordinate(_value)-_slider.width()/2,
                    _borderSize+ _fillArea.height()/2-_slider.height()/2);

   return pos;
}


void QLabSlide::setValue(double newValue)
{
   if(newValue < _scale->minimum())
      _value = _scale->minimum();
   else if(newValue > _scale->maximum())
      _value = _scale->maximum();
   else
      _value = newValue;

   repaint(false);
}


void QLabSlide::mousePressEvent(QMouseEvent *e)
{
   // check that the cursor is in the fill area or
   // the slider area
   QPoint pos = e->pos();
   
   if(_fillArea.contains(pos) || _slider.rect().contains(pos))
   {
      _clicked = true;
      _lastMousePos= pos;
   }
}


void QLabSlide::mouseReleaseEvent(QMouseEvent *e)
{
   _clicked = false;
}


void QLabSlide::mouseMoveEvent(QMouseEvent *e)
{
   int distance;
   double deltaVal;
   
   if(_clicked)
   {
      QPoint pos = e->pos();   
            
      // Compute distance since last move
      if(_orientation == vertical)
         distance = pos.y();// - _lastMousePos.y();
      else
         distance = pos.x();// - _lastMousePos.x();

      deltaVal = _scale->translateScreenCoordinate(distance);
      setValue(/*_value + */deltaVal);

      // fire the event to all listeners
      emit valueChanged(_value);
   }
}

void QLabSlide::resizeEvent(QResizeEvent *e)
{
   int minHWidth, minVWidth;
   QSize pixmapSize;

   if(_orientation == vertical)
   {
      minHWidth = 2 * _borderSize + _scaleBorderSize;
      minVWidth = 2 * _borderSize;
   }
   else
   {
      minHWidth = 2 * _borderSize;
      minVWidth = 2 * _borderSize + _scaleBorderSize;
   }

   if(e->size().width() > minHWidth)
      _fillArea.setWidth(e->size().width() - minHWidth);
   else
      _fillArea.setWidth(0);

   if(e->size().height() > minVWidth)
      _fillArea.setHeight(e->size().height() - minVWidth);
   else
      _fillArea.setHeight(0);

   
   if(_orientation == vertical)
   {
      pixmapSize.setWidth(_fillArea.width() + 10);
      pixmapSize.setHeight(_fillArea.width() + 10);
   }
   else
   {
      pixmapSize.setWidth(_fillArea.height() + 10);
      pixmapSize.setHeight(_fillArea.height() + 10);
   }

   _slider.resize(pixmapSize);
   _slider.fill(backgroundColor());
   
   switch(_sliderType)
   {
   case SimpleSlider:
      loadSimpleSlider(pixmapSize);
      break;
   case RectangleSlider:
      loadRectangleSlider(pixmapSize);
      break;
   case TriangleSlider:
      loadTriangleSlider(pixmapSize);
      break;
   case CustomSlider:
      break;
   }

   QLabBase::resizeEvent(e);
}

   
void QLabSlide::drawControl(QPaintDevice &device)
{
   QString  valueString;
   QPainter painter;
   QRect tempRect;
   
   painter.begin(&device);
   
   if(_orientation == vertical)
   {
      tempRect = QRect(_borderSize + _scaleBorderSize, _borderSize, _fillArea.width(),_fillArea.height());
      _scale->setBounds(QRect(_borderSize, _borderSize, _scaleBorderSize, _fillArea.height()));
   }
   else
   {
      tempRect = QRect(_borderSize, _borderSize, _fillArea.width(),_fillArea.height());
      _scale->setBounds(QRect(_borderSize, _borderSize + _fillArea.height(), _fillArea.width(), _scaleBorderSize));
   }

   painter.fillRect(tempRect, _fillColor);
   drawRecessedFrame(&painter, tempRect, _fillColor);

   _scale->drawScale(&painter);

   painter.setClipRect(rect());
   painter.drawPixmap(getSliderPos(), _slider);

   painter.end();
}  


void QLabSlide::loadSimpleSlider(QSize sliderSize)
{
}


void QLabSlide::loadRectangleSlider(QSize sliderSize)
{

}


void QLabSlide::loadTriangleSlider(QSize sliderSize)
{
   QPainter painter;
   QPointArray a(3);

   // draw the slider pixmap
   painter.begin(&_slider);

   painter.setPen(_sliderColor);
   painter.setBrush(_sliderColor);

   if(_orientation == vertical)
   {
      a[0] = QPoint(0, sliderSize.height() / 2);
      a[1] = QPoint(sliderSize.width() - 1, 0);
      a[2] = QPoint(sliderSize.width() - 1, sliderSize.height() - 1);
   }
   else
   {
      a[0] = QPoint(1, 0);
      a[1] = QPoint(sliderSize.width() - 2, 0);
      a[2] = QPoint(sliderSize.width() / 2, sliderSize.height() - 1);
   }
      
   painter.drawPolygon(a);

   painter.setPen(_sliderColor.dark());
   painter.drawLine(a[1], a[2]);
   painter.drawLine(a[2], a[0]);

   painter.setPen(_sliderColor.light());
   painter.drawLine(a[0], a[1]);

   painter.end();

   _slider.setMask(_slider.createHeuristicMask());
}


void QLabSlide::loadCustomSlider(QSize sliderSize)
{
}
