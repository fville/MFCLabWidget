#ifndef __QLABBASE_H__
#define __QLABBASE_H__

#define DARKER(color) RGB(GetRValue(color)/2, \
                          GetGValue(color)/2, \
                          GetBValue(color)/2)
#define LIGHTER(color) RGB((GetRValue(color)*2) < 255 ? GetRValue(color)*2 : 255, \
                           (GetGValue(color)*2) < 255 ? GetGValue(color)*2 : 255, \
                           (GetBValue(color)*2) < 255 ? GetBValue(color)*2 : 255)

class CLabBase : public CWnd
{
public:
   CLabBase();
   virtual ~CLabBase(){};

   virtual int getCharHeight();
   virtual int getCharWidth();

   void SetFont(CString fontName = "Courrier", int fontHeight = 12, 
                BOOL bBold = FALSE, BOOL bItalic = FALSE, BOOL bUnderLined = FALSE);
protected:
   //virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   afx_msg void OnPaint();
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   virtual void drawControl(CDC *pDC, CRect& rect) = 0;
   virtual void Layout(int cx, int cy) = 0;
   
   void drawRecessedFrame(CDC *pDC, CRect frameRect, COLORREF color);
   void drawRaisedFrame(CDC *pDC, CRect frameRect, COLORREF color);
   void GetTextMetric();

   CFont      _font;
   COLORREF   _color;

private:
   int        _charWidth;
   int        _charHeight;
   CSize      _size;

   DECLARE_MESSAGE_MAP()
};




#endif // __QLABBASE_H__
