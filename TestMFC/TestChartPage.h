#pragma once


#include "LabGraph.h"

// CTestChartPage dialog

class CTestChartPage : public CDialog
{
	DECLARE_DYNAMIC(CTestChartPage)

public:
	CTestChartPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTestChartPage();

// Dialog Data
	enum { IDD = IDD_TESTCHART_PAGE };

   static UINT MyThread(void* param);

protected:
   virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   CLabGraph m_Chart;
   CEdit m_Log;
   CSliderCtrl m_Amplitude;

	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedGo();
   afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
