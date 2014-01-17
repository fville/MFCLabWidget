#include <qpainter.h>

#ifndef __QLABNUMERIC_H__
#include "QLabNumeric.h"
#endif

#include "moc_QLabNumeric.cpp"

QLabNumeric::QLabNumeric(QWidget *parent, const char *name, WFlags f):
QLabBase(parent, name, f),
_value(0.0),
_precision(2),
_borderSize(2),
_spacing(2)
{
}

QSize QLabNumeric::sizeHint(void)
{
   // get enough space to display 4 characters
   // 0.00
   return QSize(4 * getCharWidth(), getCharHeight());
}

void QLabNumeric::drawControl(QPaintDevice &device)
{
   QString  valueString("");
   QPainter painter;
   
   painter.begin(&device);
   painter.setPen(white);
   painter.drawLine(0, 0, width()-1, 0);
   painter.drawLine(0, 0, 0, height()-1);
   painter.drawLine(width()-1 - _borderSize, _borderSize, width()-1 - _borderSize, height()-1 - _borderSize);
   painter.drawLine(_borderSize, height()-1 - _borderSize, width()-1 - _borderSize, height()-1 - _borderSize);

   painter.setPen(black);
   painter.drawLine(width()-1, 0, width()-1, height()-1);
   painter.drawLine(0, height()-1, width()-1, height()-1);
   painter.drawLine(_borderSize, _borderSize, width()-2 - _borderSize, _borderSize);
   painter.drawLine(_borderSize, _borderSize, _borderSize, height()-2 - _borderSize);

   painter.setFont(_font);
   painter.setClipRect(_borderSize + _spacing, _borderSize + _spacing,
                       width() - 2 * (_borderSize + _spacing), 
                       width() - 2 * (_borderSize + _spacing));
   valueString.sprintf("%.*f", _precision, _value);
   painter.drawText(_borderSize + _spacing, height() - _borderSize - _spacing, valueString);

   painter.end();
}  
