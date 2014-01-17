#ifndef __QLABKNOB_H__
#define __QLABKNOB_H__

#include "LabBase.h"
#include "LabCircularScale.h"

#define KC_VALCHANGE			1

struct LabKnobNMHDR
{
	NMHDR nmhdr;
	double value;
};

class CLabKnob : public CLabBase
{
public:
   CLabKnob();
   virtual ~CLabKnob(){};

   
   CLabScale *scale()
   {
      return &_scale;
   }

   /*virtual void mousePressEvent(QMouseEvent *);
   virtual void mouseReleaseEvent(QMouseEvent *);
   virtual void mouseMoveEvent(QMouseEvent *);
   virtual void resizeEvent(QResizeEvent *);*/
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);

   double value()
   {
      return _value;
   }

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
   }

   void setBorder(int border)
   {
      _borderSize = border;
   }

   virtual void drawControl(CDC *pDevice, CRect& rect);

protected:
   virtual void Layout(int cx, int cy);
   BOOL RegisterWindowClass();

private:
   void drawPointer(CDC *pDC);
   CPoint getCenter(void);

private:
   int _radius;
   int _borderSize;
   double _value;
   double _oldValue;
   CLabCircularScale _scale;
   bool _showValue;

   bool _clicked;
   CPoint _lastMousePos;
   CSize _size;

   DECLARE_MESSAGE_MAP()
};

#endif // __QLABKNOB_H__

