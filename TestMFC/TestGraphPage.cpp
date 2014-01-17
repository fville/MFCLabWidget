// TestGraphPage.cpp : implementation file
//

#include "stdafx.h"
#include "TestMFC.h"
#include "TestGraphPage.h"

double wave[10000];
unsigned short digpattern[10000];

// CTestGraphPage dialog

IMPLEMENT_DYNAMIC(CTestGraphPage, CDialog)
CTestGraphPage::CTestGraphPage()
	: CDialog(CTestGraphPage::IDD)
{
}

CTestGraphPage::~CTestGraphPage()
{
}

void CTestGraphPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_GRAPH, m_Graph);
   DDX_Control(pDX, IDC_DIGGRAPH, m_DigGraph);
   DDX_Control(pDX, IDC_LOG, m_Log);
   DDX_Control(pDX, IDC_KNOB, m_Knob);
   DDX_Control(pDX, IDC_FREQUENCY, m_Frequency);
}


BEGIN_MESSAGE_MAP(CTestGraphPage, CDialog)
   ON_WM_HSCROLL()
   ON_NOTIFY(KC_VALCHANGE, IDC_KNOB, OnNotifyValueChangeKnob)
	//}}AFX_MSG_MAP
   ON_BN_CLICKED(IDC_GO, OnBnClickedGo)
   ON_BN_CLICKED(IDC_DIG, OnBnClickedDig)
END_MESSAGE_MAP()

BOOL CTestGraphPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Log.SetWindowText("Welcome");

   for(int i=0; i<10000; i++)
      wave[i] = 10.0*sin(2 * 3.1415 * 10 * i / 10000.0);  

   for(int j=0; j<10000; j++)
   {
      int bit_shift = (int)floor((sin(j * 6.28 * 10/ 10000)+1) / 2 * 15 + 0.5);
      digpattern[j] = 1 << bit_shift;
   }

   m_Graph.xAxis()->setMinimum(-5.0);
   m_Graph.xAxis()->setMaximum(5.0);
   m_Graph.yAxis()->setMinimum(-10.0);
   m_Graph.yAxis()->setMaximum(10.0);
   m_Graph.addPlot(RGB(255,255,0), "");
   
   m_DigGraph.xAxis()->setMinimum(-5.0);
   m_DigGraph.xAxis()->setMaximum(5.0);
   m_DigGraph.yAxis()->setMinimum(-10.0);
   m_DigGraph.yAxis()->setMaximum(10.0);
   m_DigGraph.setType(Digital);
   m_DigGraph.addPlot(RGB(255,255,0), "");
   
   m_Graph.yplot(0, wave, 1000, -5.0, 0.01, true);
   m_DigGraph.yplot(0, digpattern, 1000, -5, 0.01, true);

   m_Frequency.SetRangeMin(0);
   m_Frequency.SetRangeMax(1000);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// CTestGraphPage message handlers
void CTestGraphPage::OnBnClickedGo()
{
   AfxBeginThread(CTestGraphPage::MyThread, this, 0, 0, 0, NULL); 
   //MyThread(this);
}

UINT CTestGraphPage::MyThread(void* param)
{
   CTestGraphPage* pThis = (CTestGraphPage*)(param);
   if(pThis != NULL)
   {
      DWORD t1 = ::GetTickCount();
      for(int i=0; i<1000; i++)
      {
         pThis->m_Graph.yplot(0, &wave[(10*i)%9000], 1000, -5.0, 0.01, true);
      }
      DWORD t2 = ::GetTickCount();

      CString str;
      str.Format("Frame rate = %f fps", 1000.0/((double)(t2-t1)/1000.0));
         
      pThis->m_Log.SetWindowText(str);
   }

   return 0;
}

UINT CTestGraphPage::MyDigThread(void* param)
{
   CTestGraphPage* pThis = (CTestGraphPage*)(param);
   if(pThis != NULL)
   {
      DWORD t1 = ::GetTickCount();
      for(int i=0; i<1000; i++)
      {
         pThis->m_DigGraph.yplot(0, &digpattern[(10*i)%9000], 1000, -5.0, 0.01, true);
      }
      DWORD t2 = ::GetTickCount();

      CString str;
      str.Format("Frame rate = %f fps", 1000.0/((double)(t2-t1)/1000.0));
         
      pThis->m_Log.SetWindowText(str);
   }

   return 0;
}

void CTestGraphPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
   if (pScrollBar && (pScrollBar->GetDlgCtrlID() == IDC_FREQUENCY))
   {
      switch (nSBCode)
      {
      case TB_LINEUP:
      case TB_LINEDOWN:
      case TB_PAGEUP:
      case TB_PAGEDOWN:
         nPos = m_Frequency.GetPos();
      case TB_THUMBTRACK:
         {
            double sinWave[2000];   
      
            for(int i=0; i<500; i++)
            {
               sinWave[i] = 10.0*sin(2 * 3.1415 * nPos * i / 1000.0); 
               sinWave[i+1000] = 5.0*cos(2 * 3.1415 * nPos * i / 1000.0);
            }

            m_Graph.yplotmultiple(2, sinWave, 1000, -5.0, 0.02, PlotDataLine, true);

            unsigned short sinPattern[2000];   
      
            for(int i=0; i<500; i++)
            {
               int bit_shift = (int)floor((sin(6.28 * nPos * i / 1000)+1) / 2 * 15 + 0.5);
               sinPattern[i] = 1 << bit_shift;
            }
            
            m_DigGraph.yplotmultiple(1, sinPattern, 500, -5.0, 0.02, PlotDataLine, true);
         }
         break;
      default:
         break;
      }
   }
}

void CTestGraphPage::OnNotifyValueChangeKnob(NMHDR * pNotifyStruct, LRESULT *result)
{
	LabKnobNMHDR* pKnobNotifyStruct = (LabKnobNMHDR*)pNotifyStruct;

   CString str;
   str.Format("Knob val=%f", pKnobNotifyStruct->value);
   m_Log.SetWindowText(str);
}
	

void CTestGraphPage::OnBnClickedDig()
{
   AfxBeginThread(CTestGraphPage::MyDigThread, this, 0, 0, 0, NULL); 
}
