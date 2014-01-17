// TestChartPage.cpp : implementation file
//

#include "stdafx.h"
#include "TestMFC.h"
#include "TestChartPage.h"
#include ".\testchartpage.h"


// CTestChartPage dialog

IMPLEMENT_DYNAMIC(CTestChartPage, CDialog)
CTestChartPage::CTestChartPage(CWnd* pParent /*=NULL*/)
	: CDialog(CTestChartPage::IDD, pParent)
{
}

CTestChartPage::~CTestChartPage()
{
}

void CTestChartPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_CHART, m_Chart);
   DDX_Control(pDX, IDC_LOG, m_Log);
   DDX_Control(pDX, IDC_AMPLITUDE, m_Amplitude);
}


BEGIN_MESSAGE_MAP(CTestChartPage, CDialog)
   ON_BN_CLICKED(IDC_GO, OnBnClickedGo)
   ON_WM_VSCROLL()
END_MESSAGE_MAP()

BOOL CTestChartPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Log.SetWindowText("Welcome");

   m_Chart.xAxis()->setMinimum(0.0);
   m_Chart.xAxis()->setMaximum(10.0);
   m_Chart.yAxis()->setMinimum(-10.0);
   m_Chart.yAxis()->setMaximum(10.0);
   m_Chart.setType(StripChart);
   m_Chart.addPlot(RGB(255,255,0), "");
   
	m_Amplitude.SetRangeMin(0);
   m_Amplitude.SetRangeMax(1000);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CTestChartPage message handlers

void CTestChartPage::OnBnClickedGo()
{
   AfxBeginThread(MyThread, this, 0, 0, 0, 0);
}

UINT CTestChartPage::MyThread(void* param)
{
   CTestChartPage* pThis = (CTestChartPage*)(param);
   if(pThis != NULL)
   {
      double val[2];

      srand(GetTickCount());
      DWORD t1 = ::GetTickCount();
      for(int i=0; i<1000; i++)
      {
         val[0] = 10.0 * sin(6.28 * 5 * i / 1000.0) + 2*((double)(16384-rand()) / RAND_MAX);
         val[1] = 5.0 * cos(6.28 * 5 * i / 1000.0) + 2*((double)(16384-rand()) / RAND_MAX);
         pThis->m_Chart.plotappend(0, val, 2, 0.0, 0.01, true);
      }
      DWORD t2 = ::GetTickCount();

      CString str;
      str.Format("Frame rate = %f fps", 1000.0/((double)(t2-t1)/1000.0));
         
      pThis->m_Log.SetWindowText(str);
   }

   return 0;
}

void CTestChartPage::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
   if (pScrollBar && (pScrollBar->GetDlgCtrlID() == IDC_AMPLITUDE))
   {
      switch (nSBCode)
      {
      case TB_LINEUP:
      case TB_LINEDOWN:
      case TB_PAGEUP:
      case TB_PAGEDOWN:
         nPos = m_Amplitude.GetPos();
      case TB_THUMBTRACK:
         {
            double val[2];
            val[0] = nPos/100.0;
            val[1] = nPos/-100.0;
            m_Chart.plotappend(0, val, 2, 0.0, 0.1, true);
         }
         break;
      default:
         break;
      }
   }
}

