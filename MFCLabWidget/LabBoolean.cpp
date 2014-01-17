#ifndef __QLABBOOLEAN_H__
#include "QLabBoolean.h"
#endif
#include <qpainter.h>

#include "moc_QLabBoolean.cpp"

QLabBoolean::QLabBoolean(QWidget *parent, const char *name, WFlags f):
QLabBase(parent, name, f),
_type(RoundLED),
_mechAction(switchWhenPressed),
_borderSize(2),
_onBooleanText("On"),
_offBooleanText("Off"),
_value(false),
_showBooleanText(false),
_clicked(false),
_onPixmap(40, 40),
_offPixmap(40, 40),
_onColor(backgroundColor()),
_offColor(backgroundColor())
{
}

QSize QLabBoolean::sizeHint(void)
{
   // get enough space to display 4 characters
   // 0.00
   return QSize(_onPixmap.width() + 2*_borderSize, _onPixmap.height()+ 2*_borderSize);
}

void QLabBoolean::mousePressEvent(QMouseEvent *e)
{
   _clicked = true;
   switch(_mechAction)
   {
   case switchWhenPressed:
      _value = !_value;
      emit valueChanged(_value);
      break;
   case switchWhenReleased:
      break;
   case switchUntilReleased:
      _value = !_value;
      emit valueChanged(_value);
      break;
   case latchWhenPressed:
   case latchWhenReleased:
   case latchUntilReleased:
      break;
   }
   repaint(false);
}


void QLabBoolean::mouseReleaseEvent(QMouseEvent *e)
{
   switch(_mechAction)
   {
   case switchWhenPressed:
      break;
   case switchWhenReleased:
      _value = !_value;
      emit valueChanged(_value);
      break;
   case switchUntilReleased:
      _value = !_value;
      emit valueChanged(_value);
      break;
   case latchWhenPressed:
   case latchWhenReleased:
   case latchUntilReleased:
      break;
   }
   _clicked = false;
   repaint(false);
}


void QLabBoolean::resizeEvent(QResizeEvent *e)
{
   QSize pixmapSize(e->size().width()-_borderSize*2, e->size().height()-_borderSize*2);

   _onPixmap.resize(pixmapSize);
   _onPixmap.fill(backgroundColor());
   _offPixmap.resize(pixmapSize);
   _offPixmap.fill(backgroundColor());

   switch(_type)
   {
   case SliderSwitch:
      LoadSliderSwitch(pixmapSize);
      break;
   case RockerSwitch:
      LoadRockerSwitch(pixmapSize);
      break;
   case ToggleSwitch:
      LoadToggleSwitch(pixmapSize);
      break;
   case RoundLED:
      LoadRoundLED(pixmapSize); 
      break;
   case SquareLED:
      LoadSquareLED(pixmapSize);
      break;
   case Custom:
      break;
   }
   QLabBase::resizeEvent(e);
}


void QLabBoolean::drawControl(QPaintDevice &device)
{
   QPainter painter;
   
   painter.begin(&device);

   painter.setClipRect(rect());


   if(_value)
      painter.drawPixmap(_borderSize, _borderSize, _onPixmap);
   else
      painter.drawPixmap(_borderSize, _borderSize, _offPixmap);
   
   if(_showBooleanText)
   {
      painter.setFont(_font);
      if(_value)
         painter.drawText(width()/2, height() / 2, _onBooleanText);
      else
         painter.drawText(width()/2, height() / 2, _offBooleanText);
   }
   
   painter.end();
}


void QLabBoolean::LoadCustom(QSize controlSize)
{

}


void QLabBoolean::LoadSliderSwitch(QSize controlSize)
{
   QPainter painter;
   
   // draw the on pixmap
   painter.begin(&_onPixmap);

   painter.setPen(black);
   painter.drawLine(0, 0, controlSize.width()-1, 0);
   painter.drawLine(0, 0, 0, controlSize.height()-1);

   painter.fillRect(1, 1, controlSize.width()-1, controlSize.height()-1, _onColor.dark(150));

   painter.setPen(_onColor.light());
   painter.drawLine(1, 1, controlSize.width()-1, 1);
   painter.drawLine(1, 1, 1, controlSize.height()/2);
   painter.setPen(_onColor.dark());
   painter.drawLine(controlSize.width()-1, 2, controlSize.width()-1, controlSize.height()/2);
   painter.drawLine(2, controlSize.height()/2, controlSize.width()-1, controlSize.height()/2);

   painter.fillRect(2, 2, controlSize.width()-3, controlSize.height()/2 - 2, _onColor);

   painter.setPen(_onColor.light());
   painter.drawLine(1, controlSize.height()/4-1, controlSize.width()-2, controlSize.height()/4-1); 
   painter.setPen(_onColor.dark());
   painter.drawLine(1, controlSize.height()/4, controlSize.width()-2, controlSize.height()/4); 
      
   painter.end();

   // draw the off pixmap
   painter.begin(&_offPixmap);

   painter.setPen(black);
   painter.drawLine(0, 0, controlSize.width()-1, 0);
   painter.drawLine(0, 0, 0, controlSize.height()-1);

   painter.fillRect(1, 1, controlSize.width()-1, controlSize.height()-2, _offColor.dark(150));

   painter.setPen(_offColor.light());
   painter.drawLine(1, controlSize.height()/2, controlSize.width()-1, controlSize.height()/2);
   painter.drawLine(1, controlSize.height()/2, 1, controlSize.height()-1);
   painter.setPen(_offColor.dark());
   painter.drawLine(controlSize.width()-1, controlSize.height()/2+1, controlSize.width()-1, controlSize.height()-1);
   painter.drawLine(2, controlSize.height()-1, controlSize.width()-1, controlSize.height()-1);

   painter.fillRect(2, controlSize.height()/2+1, controlSize.width()-3, controlSize.height()/2 - 2, _offColor);

   painter.setPen(_offColor.light());
   painter.drawLine(1, 3*controlSize.height()/4-1, controlSize.width()-2, 3*controlSize.height()/4-1); 
   painter.setPen(_offColor.dark());
   painter.drawLine(1, 3*controlSize.height()/4, controlSize.width()-2, 3*controlSize.height()/4); 

   painter.end();

}


void QLabBoolean::LoadRockerSwitch(QSize controlSize)
{
}


void QLabBoolean::LoadToggleSwitch(QSize controlSize)
{
   QPainter painter;
   int radius = controlSize.width()/4;
   int edge = controlSize.width()/8;
   QPointArray a(4);
   
   // draw the on pixmap
   painter.begin(&_onPixmap);

   painter.setPen(/*_onColor.light()*/white);
   painter.drawArc(radius, controlSize.height()/2 - radius, radius*2, radius*2, 45 * 16, 180 * 16);
   
   painter.setPen(_onColor.dark());
   painter.drawArc(radius, controlSize.height()/2 - radius, radius*2, radius*2, 225 * 16, 180 * 16);

   painter.setBrush(_onColor);
   painter.setPen(_onColor);
   painter.drawEllipse(radius+1, controlSize.height()/2 - radius + 1, (radius-1)*2, (radius-1)*2); 
   
   painter.setPen(_onColor.dark());
   painter.setBrush(_onColor);

   a[0] = QPoint(edge,0);
   a[1] = QPoint(controlSize.width()-1-edge, 0);
   a[2] = QPoint(controlSize.width()-1, edge);
   a[3] = QPoint(0, edge);
   painter.drawPolygon(a);

   painter.setPen(_onColor.dark());
   painter.setBrush(_onColor.dark());

   a[0] = QPoint(0,edge+1);
   a[1] = QPoint(controlSize.width()-1, edge+1);
   a[2] = QPoint(controlSize.width()-1-(edge*3), controlSize.height()/2);
   a[3] = QPoint(edge * 3, controlSize.height()/2);
   painter.drawPolygon(a);

   painter.end();

   // draw the off pixmap
   painter.begin(&_offPixmap);

   painter.setPen(/*_offColor.light()*/white);
   painter.drawArc(radius, controlSize.height()/2 - radius, radius*2, radius*2, 45 * 16, 180 * 16);
   
   painter.setPen(_offColor.dark());
   painter.drawArc(radius, controlSize.height()/2 - radius, radius*2, radius*2, 225 * 16, 180 * 16);

   painter.setBrush(_offColor);
   painter.setPen(_offColor);
   painter.drawEllipse(radius+1, controlSize.height()/2 - radius + 1, (radius-1)*2, (radius-1)*2);

   painter.setPen(_offColor.dark());
   painter.setBrush(_offColor);

   a[0] = QPoint(edge * 3, controlSize.height()/2);
   a[1] = QPoint(controlSize.width()-1-(edge*3), controlSize.height()/2);
   a[2] = QPoint(controlSize.width()-1, controlSize.height() - edge - 1);
   a[3] = QPoint(0,controlSize.height() - edge - 1);
   painter.drawPolygon(a);

   painter.setPen(_offColor.dark());
   painter.setBrush(_offColor.dark());

   a[0] = QPoint(0, controlSize.height() - edge);
   a[1] = QPoint(controlSize.width()-1, controlSize.height() - edge);
   a[2] = QPoint(controlSize.width()-1-edge, controlSize.height() - 1);
   a[3] = QPoint(edge, controlSize.height() - 1);
   painter.drawPolygon(a);


   painter.end();

}


void QLabBoolean::LoadRoundLED(QSize controlSize)
{
   QPainter painter;

   if(_onColor==_offColor)
      _onColor = _offColor.dark();

   // draw the on pixmap
   painter.begin(&_onPixmap);

   painter.setPen(white);
   painter.drawArc(0, 0, controlSize.width()-1, controlSize.height()-1, 45 * 16, 180 * 16);
   painter.drawArc(2, 2, controlSize.width()-5, controlSize.height()-5, 45 * 16, 180 * 16);

   painter.setPen(darkGray);
   painter.drawArc(0, 0, controlSize.width()-1, controlSize.height()-1, 225 * 16, 180 * 16);
   painter.drawArc(2, 2, controlSize.width()-5, controlSize.height()-5, 225 * 16, 180 * 16);

   painter.setPen(_onColor);
   painter.setBrush(_onColor);
   painter.drawEllipse(3, 3, controlSize.width()-7, controlSize.height()-7);

   painter.end();

   // draw the on pixmap
   painter.begin(&_offPixmap);

   painter.setPen(white);
   painter.drawArc(0, 0, controlSize.width()-1, controlSize.height()-1, 45 * 16, 180 * 16);
   painter.drawArc(2, 2, controlSize.width()-5, controlSize.height()-5, 45 * 16, 180 * 16);

   painter.setPen(darkGray);
   painter.drawArc(0, 0, controlSize.width()-1, controlSize.height()-1, 225 * 16, 180 * 16);
   painter.drawArc(2, 2, controlSize.width()-5, controlSize.height()-5, 225 * 16, 180 * 16);

   painter.setPen(_offColor);
   painter.setBrush(_offColor);
   painter.drawEllipse(3, 3, controlSize.width()-7, controlSize.height()-7);

   painter.end();

}


void QLabBoolean::LoadSquareLED(QSize controlSize)
{
   QPainter painter;

   if(_onColor==_offColor)
      _onColor = _offColor.dark();
   
   // draw the on pixmap
   painter.begin(&_onPixmap);

   // draw rectangle around the control
   painter.setPen(white);
   painter.drawLine(0, 0, controlSize.width()-1, 0);
   painter.drawLine(0, 0, 0, controlSize.height()-1);

   painter.drawLine(2, 2, controlSize.width()-3, 2);
   painter.drawLine(2, 2, 2, controlSize.height()-3);

   painter.setPen(darkGray);
   painter.drawLine(controlSize.width()-1, 0, controlSize.width()-1, controlSize.height()-1);
   painter.drawLine(0, controlSize.height()-1, controlSize.width()-1, controlSize.height()-1);

   painter.drawLine(controlSize.width()-3, 2, controlSize.width()-3, controlSize.height()-3);
   painter.drawLine(2, controlSize.height()-3, controlSize.width()-3, controlSize.height()-3);

   painter.fillRect(3, 3, controlSize.width()-6, controlSize.height()-6, QBrush(_onColor));

   painter.end();

   // draw the on pixmap
   painter.begin(&_offPixmap);

   // draw rectangle around the control
   painter.setPen(white);
   painter.drawLine(0, 0, controlSize.width()-1, 0);
   painter.drawLine(0, 0, 0, controlSize.height()-1);

   painter.drawLine(2, 2, controlSize.width()-3, 2);
   painter.drawLine(2, 2, 2, controlSize.height()-3);

   painter.setPen(darkGray);
   painter.drawLine(controlSize.width()-1, 0, controlSize.width()-1, controlSize.height()-1);
   painter.drawLine(0, controlSize.height()-1, controlSize.width()-1, controlSize.height()-1);

   painter.drawLine(controlSize.width()-3, 2, controlSize.width()-3, controlSize.height()-3);
   painter.drawLine(2, controlSize.height()-3, controlSize.width()-3, controlSize.height()-3);

   painter.fillRect(3, 3, controlSize.width()-6, controlSize.height()-6, QBrush(_offColor));

   painter.end();
}

