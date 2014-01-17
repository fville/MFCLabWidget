#ifndef __QLABBOOLEAN_H__
#define __QLABBOOLEAN_H__

#ifndef __QLABBASE_H__
#include "QLabBase.h"
#endif

class QLabBoolean : public QLabBase
{
   Q_OBJECT
public:
   QLabBoolean(QWidget *parent=0, const char *name=0, WFlags f=0);
   virtual ~QLabBoolean(){};

   typedef enum _controlType
   {
      SliderSwitch,
      RockerSwitch,
      ToggleSwitch,
      RoundLED,
      SquareLED,
      Custom,
   } tControlType;

   typedef enum _MechanicalAction
   {
      switchWhenPressed,
      switchWhenReleased,
      switchUntilReleased,
      latchWhenPressed,
      latchWhenReleased,
      latchUntilReleased
   } tMechanicalAction;
   
   virtual void mousePressEvent(QMouseEvent *);
   virtual void mouseReleaseEvent(QMouseEvent *);
   virtual void resizeEvent(QResizeEvent *);

   QColor onColor()
   {
      return _onColor;
   }

   void setOnColor(QColor newColor)
   {
      _onColor = newColor;
   }

   QColor offColor()
   {
      return _offColor;
   }

   void setOffColor(QColor newColor)
   {
      _offColor = newColor;
   }

   QString onBooleanText()
   {
      return _onBooleanText;
   }

   void setOnBooleanText(QString newText)
   {
      _onBooleanText = newText;
   }

   void showBooleanText()
   {
      _showBooleanText = true;
   }

   void hideBooleanText()
   {
      _showBooleanText = false;
   }

   QString offBooleanText()
   {
      return _offBooleanText;
   }

   void setOffBooleanText(QString newText)
   {
      _offBooleanText = newText;
   }

   void setValue(bool value)
   {
      _value = value;
   }

   bool value()
   {
      return _value;
   }

   void setOnPixmap(QPixmap pixmap)
   {
      setControlType(Custom);
      _onPixmap = pixmap;
   }

   QPixmap onPixmap()
   {
      return _onPixmap;
   }

   void setOffPixmap(QPixmap pixmap)
   {
      setControlType(Custom);
      _offPixmap = pixmap;
   }

   QPixmap offPixmap()
   {
      return _offPixmap;
   }

   void setControlType(tControlType newType)
   {
      _type = newType;
      resize(size());
   }

   tControlType controlType()
   {
      return _type;
   }

   void setMechanicalAction(tMechanicalAction newAction)
   {
      _mechAction = newAction;
   }

   tMechanicalAction mechanicalAction()
   {
      return _mechAction;
   }

   int getBorder()
   {
      return _borderSize;
   }

   void setBorder(int border)
   {
      _borderSize = border;
   }

   virtual void drawControl(QPaintDevice &device);
   virtual QSize sizeHint(void);

private:
   void LoadCustom(QSize controlSize);
   void LoadSliderSwitch(QSize controlSize);
   void LoadRockerSwitch(QSize controlSize);
   void LoadToggleSwitch(QSize controlSize);
   void LoadRoundLED(QSize controlSize);
   void LoadSquareLED(QSize controlSize);

signals:
   void valueChanged(bool value);

private:
   tControlType _type;
   tMechanicalAction _mechAction;
   int _borderSize;
   QString _onBooleanText;
   QString _offBooleanText;
   bool _value;
   bool _showBooleanText;

   bool _clicked;
   QPixmap _onPixmap;
   QPixmap _offPixmap;
   QColor _onColor;
   QColor _offColor;
};

#endif // __QLABBOOLEAN_H__

