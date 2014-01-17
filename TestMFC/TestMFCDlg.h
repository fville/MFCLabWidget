// TestMFCDlg.h : header file
//

#pragma once

#include "TestGraphPage.h"
#include "TestChartPage.h"
#include "afxcmn.h"

// CTestMFCDlg dialog
class CTestMFCDlg : public CDialog
{
// Construction
public:
	CTestMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TESTMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

   CTestGraphPage m_GraphPage;
   CTestChartPage m_ChartPage;

public:
   afx_msg void OnBnClickedTestgraph();
   afx_msg void OnBnClickedTestchart();
};
