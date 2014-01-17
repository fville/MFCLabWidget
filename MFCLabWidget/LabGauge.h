#ifndef __QLABGAUGE_H__ 
#define __QLABGAUGE_H__  
#ifndef __QLABBASE_H__ 
#include "QLabBase.h" 
#endif   

class QLabGauge : public QLabNumeric 
{   
   Q_OBJECT 
public:    
QLabGauge(QWidget *parent=0, const char *name=0, WFlags f=0);    
virtual ~QLabGauge(){};         

virtual void mousePressEvent(QMouseEvent *);    
virtual void mouseReleaseEvent(QMouseEvent *);    
virtual void mouseMoveEvent(QMouseEvent *);    
virtual void resizeEvent(QResizeEvent *);     
int radius()    
{       
return _radius;   
 }     
void setRadius(int radius)    
{       
_radius = radius;    
}     

int getBorder()    
{       
return _borderSize;    
}     void setBorder(int border)    {       _borderSize = border;    }     virtual void drawControl(QPaintDevice &device);    virtual QSize sizeHint(void);  private:    void drawPointer(QPainter *p);    QPoint getCenter(void);  signals:    void valueChanged(double value);  private:    int _scaleBorderSize;    int _borderSize;    double _value;    double _oldValue;    QLabCircularScale _scale;    bool _showValue;     bool _clicked;    QPoint _lastMousePos; };  #endif // __QLABKNOB_H__  