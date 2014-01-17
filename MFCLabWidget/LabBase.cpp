#include "stdafx.h"
#include "LabBase.h"

BEGIN_MESSAGE_MAP(CLabBase, CWnd)
	//{{AFX_MSG_MAP(CLabBase)
	ON_WM_PAINT()
   ON_WM_SIZE()
   ON_WM_SHOWWINDOW()
   ON_WM_CREATE()
   ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CLabBase::CLabBase():
_size(0,0)
{
   SetFont("Arial", 14);
}

int CLabBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// Call the base class to create the window
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


void CLabBase::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
   CDC  memDC;
   CBitmap  bitmap;

   // We will do all the drawing in a memory DC to avoid flickering
   CRect clientRect;
   GetClientRect(&clientRect);
   if(_size != clientRect.Size())
   {
      _size = clientRect.Size();
      GetTextMetric();
      Layout(_size.cx, _size.cy);
   }

   // Create a compatible DC.
   memDC.CreateCompatibleDC(&dc);

   // Create a bitmap big enough for our client rectangle.
   bitmap.CreateCompatibleBitmap(&dc, clientRect.right-clientRect.left,
                                 clientRect.bottom-clientRect.top);

   // Select the bitmap into the off-screen DC.
   CBitmap* oldBitmap = memDC.SelectObject(&bitmap);

   
   CFont* oldFont = memDC.SelectObject(&_font);

   memDC.SetBkMode(TRANSPARENT);

   drawControl(&memDC, clientRect);
   
   if(oldFont)
      memDC.SelectObject(oldFont);

   dc.BitBlt(clientRect.left, clientRect.top, clientRect.right-clientRect.left, 
               clientRect.bottom-clientRect.top, &memDC, 0, 0, SRCCOPY);

   if(oldBitmap)
      memDC.SelectObject(oldBitmap);

   bitmap.DeleteObject();
   memDC.DeleteDC();
}


void CLabBase::GetTextMetric()
{
   if(IsWindow(m_hWnd))
   {
      CDC *dc = GetDC();

      CFont* def_font = dc->SelectObject(&_font);
      TEXTMETRIC textMetric;

      dc->GetOutputTextMetrics(&textMetric);

      _charWidth = textMetric.tmAveCharWidth;
      _charHeight = textMetric.tmHeight;
     
      dc->SelectObject(def_font);
      ReleaseDC(dc);
   }
}  


void CLabBase::OnSize(UINT nType, int cx, int cy)
{
   CWnd::OnSize(nType, cx, cy);

   Layout(cx, cy);
}

void CLabBase::OnShowWindow(BOOL bShow, UINT nStatus)
{
   if(bShow)
   {
      GetTextMetric();
      CRect rect;
      GetClientRect(&rect);
      Layout(rect.Width(), rect.Height());
   }
}


int CLabBase::getCharHeight()
{
   return _charHeight;
}


int CLabBase::getCharWidth()
{
   return _charWidth;
}

void CLabBase::SetFont(CString fontName, int fontHeight, BOOL bBold, BOOL bItalic, BOOL bUnderLined)
{
   _font.DeleteObject();

   _font.CreateFont(
   fontHeight,                // nHeight
   0,                         // nWidth
   0,                         // nEscapement
   0,                         // nOrientation
   FW_NORMAL,                 // nWeight
   FALSE,                     // bItalic
   FALSE,                     // bUnderline
   0,                         // cStrikeOut
   ANSI_CHARSET,              // nCharSet
   OUT_DEFAULT_PRECIS,        // nOutPrecision
   CLIP_DEFAULT_PRECIS,       // nClipPrecision
   DEFAULT_QUALITY,           // nQuality
   DEFAULT_PITCH | FF_MODERN, // nPitchAndFamily
   fontName);                 // lpszFacename

   GetTextMetric();

   if(IsWindow(m_hWnd))
      Invalidate();
}

void CLabBase::drawRecessedFrame(CDC *pDC, CRect frameRect, COLORREF color)
{
   CPen pen1(PS_SOLID, 1, DARKER(color));
   CPen* pOldPen = pDC->SelectObject(&pen1);
   pDC->MoveTo(frameRect.TopLeft());
   pDC->LineTo(frameRect.left + frameRect.Width()-1, frameRect.top);
   pDC->MoveTo(frameRect.TopLeft());
   pDC->LineTo(frameRect.left, frameRect.top + frameRect.Height()-1);

   CPen pen2(PS_SOLID, 1, LIGHTER(color));
   pDC->SelectObject(&pen2);
   pDC->MoveTo(frameRect.left + frameRect.Width()-1, frameRect.top);
   pDC->LineTo(frameRect.left + frameRect.Width()-1, frameRect.top + frameRect.Height()-1);
   pDC->MoveTo(frameRect.left, frameRect.top + frameRect.Height()-1);
   pDC->LineTo(frameRect.left + frameRect.Width()-1, frameRect.top + frameRect.Height()-1);

   pDC->SelectObject(pOldPen);
}


void CLabBase::drawRaisedFrame(CDC *pDC, CRect frameRect, COLORREF color)
{
   CPen pen1(PS_SOLID, 1, LIGHTER(color));
   CPen* pOldPen = pDC->SelectObject(&pen1);
   pDC->MoveTo(frameRect.TopLeft());
   pDC->LineTo(frameRect.left + frameRect.Width()-1, frameRect.top);
   pDC->MoveTo(frameRect.TopLeft());
   pDC->LineTo(frameRect.left, frameRect.top + frameRect.Height()-1);

   CPen pen2(PS_SOLID, 1, DARKER(color));
   pDC->SelectObject(&pen2);
   pDC->MoveTo(frameRect.left + frameRect.Width()-1, frameRect.top);
   pDC->LineTo(frameRect.left + frameRect.Width()-1, frameRect.top + frameRect.Height()-1);
   pDC->MoveTo(frameRect.left, frameRect.top + frameRect.Height()-1);
   pDC->LineTo(frameRect.left + frameRect.Width()-1, frameRect.top + frameRect.Height()-1);

   pDC->SelectObject(pOldPen);
}

BOOL CLabBase::OnEraseBkgnd(CDC* pDC) 
{
   return TRUE;
}

