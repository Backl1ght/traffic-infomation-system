
// MainFrm.cpp: CMainFrame 类的实现
//

#include "stdafx.h"
#include "TrafficInfoSystem.h"

#include "CView_Lup.h"
#include "CEditView_Ldown.h"
#include "CListView_Rdown.h"
#include "CTabView_Rup.h"

#include "afxext.h"


#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));



	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	CRect rc;
	GetClientRect(&rc);
	int w = rc.Width(), h = rc.Height();


	//分割窗口
	if (!m_splitwnd.CreateStatic(this, 2, 2))
		return FALSE;




	if (!m_splitwnd.CreateView(0, 0, RUNTIME_CLASS(CView_Lup), CSize(w * 4 / 5, h * 2 / 5), pContext))
		return FALSE;
	
	if (!m_splitwnd.CreateView(1, 0, RUNTIME_CLASS(CEditView_Ldown), CSize(w * 4 / 5, h * 2 / 5), pContext))
		return FALSE;

	if (!m_splitwnd.CreateView(0, 1, RUNTIME_CLASS(CTabView_Rup), CSize(w / 5, h * 3 / 5), pContext))
		return FALSE;

	if (!m_splitwnd.CreateView(1, 1, RUNTIME_CLASS(CListView_Rdown), CSize(w / 5, h * 3 / 5), pContext))
		return FALSE;
	




	return true;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
void CMainFrame::Editchange()
{
	CEditView_Ldown* m_pCEditView = (CEditView_Ldown*)m_splitwnd.GetPane(1, 0);
	m_pCEditView->Editchange();
}
void CMainFrame::Editchange(string src)
{
	CEditView_Ldown* m_pCEditView = (CEditView_Ldown*)m_splitwnd.GetPane(1, 0);
	m_pCEditView->Editchange(src);
}
void CMainFrame::Editchange(string from, string to)
{
	CEditView_Ldown* m_pCEditView = (CEditView_Ldown*)m_splitwnd.GetPane(1, 0);
	m_pCEditView->Editchange(from,to);
}

void CMainFrame::rePaintLup()
{
	CView_Lup* m_pCView = (CView_Lup*)m_splitwnd.GetPane(0, 0);
	m_pCView->OnRepaint();
}

void CMainFrame::Listchange(int node_id)
{
	CListView_Rdown* m_pClistView = (CListView_Rdown*)m_splitwnd.GetPane(1, 1);
	m_pClistView->Listchange(node_id);
}

void CMainFrame::Listchange(int from, int to)
{
	CListView_Rdown* m_pClistView = (CListView_Rdown*)m_splitwnd.GetPane(1, 1);
	m_pClistView->Listchange(from, to);
}

void CMainFrame::OnPaintSP(int to, int * path)
{
	CView_Lup* m_pCView = (CView_Lup*)m_splitwnd.GetPane(0, 0);
	m_pCView->OnPaintSp(to,path);
}

void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDocument *pDocumet = this->GetActiveDocument();
	if(pDocumet)
	pDocumet->SetModifiedFlag(FALSE);

	CFrameWnd::OnClose();
}

