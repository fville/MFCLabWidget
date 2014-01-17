#pragma once

#include "LabGraph.h"
#include "LabKnob.h"

// CTestGraphPage dialog

class CTestGraphPage : public CDialog
{
	DECLARE_DYNAMIC(CTestGraphPage)

public:
	CTestGraphPage();
	virtual ~CTestGraphPage();

// Dialog Data
	enum { IDD = IDD_TESTGRAPH_PAGE };

protected:
   virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   static UINT MyThread(void* param);
   static UINT MyDigThread(void* param);

   CLabGraph m_Graph;
   CLabGraph m_DigGraph;
   CLabKnob m_Knob;
   CEdit m_Log;
   CSliderCtrl m_Frequency;
public:
   afx_msg void OnBnClickedGo();
   afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg void OnBnClickedDig();
   afx_msg void OnNotifyValueChangeKnob(NMHDR *pNotifyStruct, LRESULT *result);
	DECLARE_MESSAGE_MAP()
};
