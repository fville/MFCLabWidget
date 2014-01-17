#include "stdafx.h"
#include <math.h>
#include "LabKnob.h"

BEGIN_MESSAGE_MAP(CLabKnob, CLabBase)
	//{{AFX_MSG_MAP(CLabKnob)
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CLabKnob::CLabKnob():
CLabBase(),
_scale(this)
{
   RegisterWindowClass();

   _color = ::GetSysColor(COLOR_BTNFACE);

   _radius = 70;
   _borderSize = 20;

   _value = _scale.minimum();
   _oldValue = 0.0;

   _showValue = false;

   _scale.setStartAngle(240);
   _scale.setArcAngle(300);

   _clicked = false;
}

BOOL CLabKnob::RegisterWindowClass()
{
   WNDCLASS wndcls;
   HINSTANCE hInst = AfxGetInstanceHandle();
   HBRUSH background;
   background = ::GetSysColorBrush(COLOR_BTNFACE);

   if (!(::GetClassInfo(hInst, "MFCLabKnob", &wndcls)))
   {
      // otherwise we need to register a new class
      wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
      wndcls.lpfnWndProc      = ::DefWindowProc;
      wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
      wndcls.hInstance        = hInst;
      wndcls.hIcon            = NULL;
      wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
      wndcls.hbrBackground    = background;
      wndcls.lpszMenuName     = NULL;
      wndcls.lpszClassName    = "MFCLabKnob";

      if (!AfxRegisterClass(&wndcls))
      {
         AfxThrowResourceException();
         return FALSE;
      }
   }

   return TRUE;
}

void CLabKnob::OnLButtonDown(UINT nFlags, CPoint point)
{
   // check that the cursor is in the knob by verifying
   // that the following expression is true:
   // (x-xCenter)^2 + (y-yCenter)^2 <= radius^2
   double disc = (point.x - getCenter().x) * (point.x - getCenter().x) +
                 (point.y - getCenter().y) * (point.y - getCenter().y);

   if(disc <= (_radius * _radius))
   {
      _clicked = true;
      _lastMousePos= point;
   }

   CLabBase::OnLButtonDown(nFlags, point);
}


void CLabKnob::OnLButtonUp(UINT nFlags, CPoint point)
{
   _clicked = false;
   CLabBase::OnLButtonUp(nFlags, point);
}


void CLabKnob::OnMouseMove(UINT nFlags, CPoint point)
{
   if(_clicked)
   {
      double angle = -atan2((float)(point.y - getCenter().y), 
                      (float)(point.x - getCenter().x)) * 180.0 / PI;
      double cursorAngle;

      if(_scale.startAngle() >= angle)
         cursorAngle = _scale.startAngle() - angle;
      else
         cursorAngle = 360 + _scale.startAngle() - angle;

      if(cursorAngle >  360.0)
         cursorAngle = cursorAngle - 360.0;

      // compute new value
      _value = (cursorAngle / _scale.arcAngle()) *
              (_scale.maximum() - _scale.minimum()) + _scale.minimum();

      if(_value < _scale.minimum())
         _value = _scale.minimum();
      else if(_value > _scale.maximum())
         _value = _scale.maximum();
      
      // fire the event to all listeners
      LabKnobNMHDR nmhdr;
			
		nmhdr.nmhdr.code = KC_VALCHANGE;
		nmhdr.nmhdr.hwndFrom = GetSafeHwnd();
		nmhdr.nmhdr.idFrom = GetDlgCtrlID();
      nmhdr.value = _value;
		GetParent()->SendMessage(WM_NOTIFY, nmhdr.nmhdr.idFrom, (DWORD)(&nmhdr));
		
      Invalidate();
   }

   CLabBase::OnMouseMove(nFlags, point);
}

void CLabKnob::Layout(int cx, int cy)
{
   _radius = (cx/2) - _borderSize;
}

   
CPoint CLabKnob::getCenter()
{
   return(CPoint(_borderSize + _radius, _borderSize + _radius));
}


void CLabKnob::drawControl(CDC *pDC, CRect& rect)
{
   CString  valueString;

   // draw control background
   CBrush brush1;
   brush1.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));      
   pDC->FillRect(rect, &brush1); 

   CPen p(PS_SOLID, 1, _color);
   CPen pw(PS_SOLID, 1, RGB(255,255,255));
   CPen pb(PS_SOLID, 1, RGB(0,0,0));
      
   CRect krect(_borderSize, _borderSize, _borderSize + _radius*2, _borderSize + _radius*2);
   CBrush brush2;
   brush2.CreateSolidBrush(_color);
   CBrush *pOldBrush = pDC->SelectObject(&brush2);
   CPen *pOldPen = pDC->SelectObject(&p);
   pDC->Ellipse(krect);

   //krect.InflateRect(1,1,1,1);
   pDC->SelectObject(&pb);
   pDC->Arc(krect, CPoint(krect.left, krect.bottom),
            CPoint(krect.right, krect.top));
   
   pDC->SelectObject(&pw);
   pDC->Arc(krect, CPoint(krect.right, krect.top),
            CPoint(krect.left, krect.bottom));

   drawPointer(pDC);

   _scale.setBounds(CRect(0, 0, (_borderSize + _radius) * 2, (_borderSize + _radius) * 2));
   _scale.drawScale(pDC);

   pDC->SelectObject(pOldPen);
   pDC->SelectObject(pOldBrush);
}  


void CLabKnob::drawPointer(CDC *pDC)
{
   double pointerAngle;
   int pointerLength = 20;
   double xPointerVec;
   double yPointerVec;

   CPen p(PS_SOLID, 1, RGB(0,0,0));
   CPen *pOldPen = pDC->SelectObject(&p);

   pointerAngle = _scale.translateCoordinate(_value)/100.0;
   xPointerVec = cos(pointerAngle);
   yPointerVec = sin(pointerAngle);

   pDC->MoveTo(getCenter().x + (int)((_radius - pointerLength) * xPointerVec),
               getCenter().y - (int)((_radius - pointerLength) * yPointerVec));
   pDC->LineTo(getCenter().x + (int)(_radius * xPointerVec),
               getCenter().y - (int)(_radius * yPointerVec));

   pDC->SelectObject(pOldPen);
}

