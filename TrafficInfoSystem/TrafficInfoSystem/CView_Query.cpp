// CView_Query.cpp: 实现文件
//

#include "stdafx.h"
#include "TrafficInfoSystem.h"
#include "MainFrm.h"
#include "CView_Query.h"

#define IDC_D_BTN_Qry 10008
#define IDC_D_CBN_QryChoose 10009
#define IDC_D_CBN_QryName 10010
#define IDC_D_CBN_QryFrom 10011
#define IDC_D_CBN_QryTo 10012


// CView_Query

IMPLEMENT_DYNCREATE(CView_Query, CView)

CView_Query::CView_Query()
{

}

CView_Query::~CView_Query()
{
}

BEGIN_MESSAGE_MAP(CView_Query, CView)
	ON_CBN_SELCHANGE(IDC_D_CBN_QryChoose, OnCbnSelchange)
	ON_CBN_SELCHANGE(IDC_D_CBN_QryName, OnCbnSelchange1)
	ON_CBN_EDITCHANGE(IDC_D_CBN_QryChoose, OnCbnEditchange)
	ON_BN_CLICKED(IDC_D_BTN_Qry, OnButtonClick)
	ON_CBN_DROPDOWN(IDC_D_CBN_QryName,OnDropdown)
	ON_CBN_DROPDOWN(IDC_D_CBN_QryFrom, OnDropdown1)
	ON_CBN_DROPDOWN(IDC_D_CBN_QryTo, OnDropdown2)
END_MESSAGE_MAP()


// CView_Query 绘图

void CView_Query::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// CView_Query 诊断

#ifdef _DEBUG
void CView_Query::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CView_Query::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CView_Query 消息处理程序


void CView_Query::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_btn_Qry.Create(_T("查询"), WS_CHILD  | BS_PUSHBUTTON, CRect(90, 350, 190, 380), this, IDC_D_BTN_Qry);

	m_Sedit_Choose.Create(ES_LEFT | WS_VISIBLE | ES_READONLY | WS_CHILD, CRect(10, 10, 100, 40), this, 1);
	m_Sedit_Choose.SetWindowText(_T("功能"));

	m_cbbox_Choose.Create(CBS_DROPDOWNLIST | WS_VISIBLE | WS_TABSTOP | CBS_AUTOHSCROLL, CRect(110, 10, 250, 40), this, IDC_D_CBN_QryChoose);
	m_cbbox_Choose.InsertString(0, _T("城市信息"));
	m_cbbox_Choose.InsertString(1, _T("指定城市最短路"));
	m_cbbox_Choose.InsertString(2, _T("两城市最短路"));
	m_cbbox_Choose.InsertString(3, _T("任意城市最短路"));
	m_cbbox_Choose.SetCurSel(0);
	CRect rc;
	m_cbbox_Choose.GetDroppedControlRect(&rc);
	m_cbbox_Choose.GetParent()->ScreenToClient(&rc);
	rc.bottom += 4 * m_cbbox_Choose.GetItemHeight(-1);
	m_cbbox_Choose.MoveWindow(&rc);

	m_Sedit_Name.Create(ES_LEFT | ES_READONLY |WS_VISIBLE, CRect(10, 45, 100, 75), this, 1);
	m_Sedit_Name.SetWindowText(_T("名称"));
	m_cbbox_Name.Create(CBS_DROPDOWNLIST | WS_TABSTOP | CBS_AUTOHSCROLL| WS_VISIBLE, CRect(110, 45, 250, 75), this, IDC_D_CBN_QryName);

	m_Sedit_From.Create(ES_LEFT | ES_READONLY, CRect(10, 45, 100, 75), this, 1);
	m_Sedit_From.SetWindowText(_T("起点"));
	m_cbbox_From.Create(CBS_DROPDOWNLIST | WS_TABSTOP | CBS_AUTOHSCROLL, CRect(110, 45, 250, 75), this, IDC_D_CBN_QryFrom);


	m_Sedit_To.Create(ES_LEFT | ES_READONLY, CRect(10, 80, 100, 110), this, 1);
	m_Sedit_To.SetWindowText(_T("终点"));
	m_cbbox_To.Create(CBS_DROPDOWNLIST | WS_TABSTOP | CBS_AUTOHSCROLL, CRect(110, 80, 250, 110), this, IDC_D_CBN_QryTo);

	m_Sedit_Code.Create(ES_LEFT | WS_VISIBLE | ES_READONLY, CRect(10, 80, 100, 110), this, 1);
	m_Sedit_Code.SetWindowText(_T("代号"));
	m_edit_Code.Create(ES_LEFT | WS_VISIBLE | WS_BORDER | ES_READONLY, CRect(110, 80, 250, 110), this, 1);



	m_Sedit_Intro.Create(ES_LEFT | WS_VISIBLE | ES_READONLY, CRect(10, 115, 100, 145), this, 1);
	m_Sedit_Intro.SetWindowText(_T("简介"));
	m_edit_Intro.Create(ES_LEFT | WS_VISIBLE | WS_BORDER | ES_READONLY, CRect(110, 115, 250, 145), this, 1);


	m_Sedit_X.Create(ES_LEFT | WS_VISIBLE | ES_READONLY, CRect(10, 150, 100, 180), this, 1);
	m_Sedit_X.SetWindowText(_T("横坐标"));
	m_edit_X.Create(ES_LEFT | WS_VISIBLE | WS_BORDER | ES_READONLY, CRect(110, 150, 250, 180), this, 1);


	m_Sedit_Y.Create(ES_LEFT | WS_VISIBLE | ES_READONLY, CRect(10, 185, 100, 215), this, 1);
	m_Sedit_Y.SetWindowText(_T("纵坐标"));
	m_edit_Y.Create(ES_LEFT | WS_VISIBLE | WS_BORDER | ES_READONLY, CRect(110, 185, 250, 215), this, 1);


}

void CView_Query::ChangeView(int i)
{
	if (i == 0) {
		m_Sedit_Name.ShowWindow(SW_SHOW);
		m_Sedit_Code.ShowWindow(SW_SHOW);
		m_Sedit_Intro.ShowWindow(SW_SHOW);
		m_Sedit_X.ShowWindow(SW_SHOW);
		m_Sedit_Y.ShowWindow(SW_SHOW);
		m_edit_Code.ShowWindow(SW_SHOW);
		m_edit_Intro.ShowWindow(SW_SHOW);
		m_edit_X.ShowWindow(SW_SHOW);
		m_edit_Y.ShowWindow(SW_SHOW);
		m_cbbox_Name.ShowWindow(SW_SHOW);

		m_Sedit_From.ShowWindow(SW_HIDE);
		m_Sedit_To.ShowWindow(SW_HIDE);
		m_cbbox_From.ShowWindow(SW_HIDE);
		m_cbbox_To.ShowWindow(SW_HIDE);

		m_btn_Qry.ShowWindow(SW_HIDE);
	}
	else if (i == 1) {
		m_Sedit_Name.ShowWindow(SW_HIDE);
		m_Sedit_Code.ShowWindow(SW_HIDE);
		m_Sedit_Intro.ShowWindow(SW_HIDE);
		m_Sedit_X.ShowWindow(SW_HIDE);
		m_Sedit_Y.ShowWindow(SW_HIDE);
		m_edit_Code.ShowWindow(SW_HIDE);
		m_edit_Intro.ShowWindow(SW_HIDE);
		m_edit_X.ShowWindow(SW_HIDE);
		m_edit_Y.ShowWindow(SW_HIDE);
		m_cbbox_Name.ShowWindow(SW_HIDE);

		m_Sedit_From.ShowWindow(SW_SHOW);
		m_Sedit_To.ShowWindow(SW_HIDE);
		m_cbbox_From.ShowWindow(SW_SHOW);
		m_cbbox_To.ShowWindow(SW_HIDE);

		m_btn_Qry.ShowWindow(SW_SHOW);
	}
	else if (i == 2) {
		m_Sedit_Name.ShowWindow(SW_HIDE);
		m_Sedit_Code.ShowWindow(SW_HIDE);
		m_Sedit_Intro.ShowWindow(SW_HIDE);
		m_Sedit_X.ShowWindow(SW_HIDE);
		m_Sedit_Y.ShowWindow(SW_HIDE);
		m_edit_Code.ShowWindow(SW_HIDE);
		m_edit_Intro.ShowWindow(SW_HIDE);
		m_edit_X.ShowWindow(SW_HIDE);
		m_edit_Y.ShowWindow(SW_HIDE);
		m_cbbox_Name.ShowWindow(SW_HIDE);

		m_btn_Qry.ShowWindow(SW_SHOW);

		m_Sedit_From.ShowWindow(SW_SHOW);
		m_Sedit_To.ShowWindow(SW_SHOW);
		m_cbbox_From.ShowWindow(SW_SHOW);
		m_cbbox_To.ShowWindow(SW_SHOW);
	}
	else if (i == 3) {
		m_Sedit_Name.ShowWindow(SW_HIDE);
		m_Sedit_Code.ShowWindow(SW_HIDE);
		m_Sedit_Intro.ShowWindow(SW_HIDE);
		m_Sedit_X.ShowWindow(SW_HIDE);
		m_Sedit_Y.ShowWindow(SW_HIDE);
		m_edit_Code.ShowWindow(SW_HIDE);
		m_edit_Intro.ShowWindow(SW_HIDE);
		m_edit_X.ShowWindow(SW_HIDE);
		m_edit_Y.ShowWindow(SW_HIDE);
		m_cbbox_Name.ShowWindow(SW_HIDE);

		m_Sedit_From.ShowWindow(SW_HIDE);
		m_Sedit_To.ShowWindow(SW_HIDE);
		m_cbbox_From.ShowWindow(SW_HIDE);
		m_cbbox_To.ShowWindow(SW_HIDE);

		m_btn_Qry.ShowWindow(SW_SHOW);
	}
}

void CView_Query::OnButtonClick()
{
	//TODO
	if (m_cbbox_Choose.GetCurSel() == 1) {
		CMainFrame *m_host = (CMainFrame*)AfxGetMainWnd();
		CString From;

		if (m_cbbox_From.GetCurSel() == CB_ERR)
		{
			AfxMessageBox(_T("输入错误"));
			return;
		}

		m_cbbox_From.GetWindowTextA(From);
		string src = CT2A(From);
		m_host->Editchange(src);

		//画板重绘
		CMainFrame* m_pHost = (CMainFrame*)AfxGetMainWnd();
		m_pHost->rePaintLup();
	}
	else if (m_cbbox_Choose.GetCurSel() == 2) {
		CMainFrame *m_host = (CMainFrame*)AfxGetMainWnd();
		CString From,To;

		if (m_cbbox_From.GetCurSel() == CB_ERR || m_cbbox_To.GetCurSel() == CB_ERR)
		{
			AfxMessageBox(_T("输入错误"));
			return;
		}
		CMainFrame* m_pHost = (CMainFrame*)AfxGetMainWnd();
		m_pHost->rePaintLup();

		m_cbbox_From.GetWindowTextA(From);
		m_cbbox_To.GetWindowTextA(To);
		string from = CT2A(From), to = CT2A(To);
		m_host->Editchange(from,to);
	}
	else if (m_cbbox_Choose.GetCurSel() == 3) {
		CMainFrame *m_host = (CMainFrame*)AfxGetMainWnd();
		m_host->Editchange();

		//画板重绘
		CMainFrame* m_pHost = (CMainFrame*)AfxGetMainWnd();
		m_pHost->rePaintLup();
	}

}

void CView_Query::OnCbnSelchange()
{
	ChangeView(m_cbbox_Choose.GetCurSel());
}

void CView_Query::OnCbnEditchange()
{
}

void CView_Query::OnCbnSelchange1()
{
	Node tmp = theApp.G.getNode(m_cbbox_Name.GetCurSel());
	CString temp;
	m_edit_Code.SetWindowTextA(LPCTSTR(tmp.getCode().c_str()));
	m_edit_Intro.SetWindowTextA(LPCTSTR(tmp.getIntro().c_str()));
	temp.Format("%d", tmp.getX());
	m_edit_X.SetWindowTextA(LPCTSTR(temp));
	temp.Format("%d", tmp.getY());
	m_edit_Y.SetWindowTextA(LPCTSTR(temp));
}

void CView_Query::OnDropdown()
{
	m_cbbox_Name.ResetContent();
	Node *list = theApp.G.getNodeList();
	int num = theApp.G.getNode_num();
	for (int i = 0; i < num; i++) {
		m_cbbox_Name.AddString(LPCTSTR(list[i].getName().c_str()));
	}
	CRect rc;
	m_cbbox_Name.GetDroppedControlRect(&rc);
	m_cbbox_Name.GetParent()->ScreenToClient(&rc);
	rc.bottom += num * m_cbbox_Name.GetItemHeight(-1);
	m_cbbox_Name.MoveWindow(&rc);
}

void CView_Query::OnDropdown1()
{
	m_cbbox_From.ResetContent();
	Node *list = theApp.G.getNodeList();
	int num = theApp.G.getNode_num();
	for (int i = 0; i < num; i++) {
		m_cbbox_From.AddString(LPCTSTR(list[i].getName().c_str()));
	}
	CRect rc;
	m_cbbox_From.GetDroppedControlRect(&rc);
	m_cbbox_From.GetParent()->ScreenToClient(&rc);
	rc.bottom += num * m_cbbox_From.GetItemHeight(-1);
	m_cbbox_From.MoveWindow(&rc);
}

void CView_Query::OnDropdown2()
{
	m_cbbox_To.ResetContent();
	Node *list = theApp.G.getNodeList();
	int num = theApp.G.getNode_num();
	for (int i = 0; i < num; i++) {
		m_cbbox_To.AddString(LPCTSTR(list[i].getName().c_str()));
	}
	CRect rc;
	m_cbbox_To.GetDroppedControlRect(&rc);
	m_cbbox_To.GetParent()->ScreenToClient(&rc);
	rc.bottom += num * m_cbbox_From.GetItemHeight(-1);
	m_cbbox_To.MoveWindow(&rc);
}

