// CView_Del.cpp: 实现文件
//

#include "stdafx.h"
#include "TrafficInfoSystem.h"
#include "CView_Del.h"
#include "MainFrm.h"


#include<vector>

#define IDC_D_BTN_Del 10002
#define IDC_D_CBN_DelChoose	10003
#define IDC_D_CBN_DelFrom	12004
#define IDC_D_CBN_DelTo		10005
#define IDC_D_CBN_DelPath	10006
#define IDC_D_CBN_DelName	12007

// CView_Del

IMPLEMENT_DYNCREATE(CView_Del, CView)

CView_Del::CView_Del()
{

}

CView_Del::~CView_Del()
{
}

BEGIN_MESSAGE_MAP(CView_Del, CView)
	ON_CBN_SELCHANGE(IDC_D_CBN_DelChoose, OnCbnSelchange)
	ON_CBN_EDITCHANGE(IDC_D_CBN_DelChoose, OnCbnEditchange)
	ON_BN_CLICKED(IDC_D_BTN_Del, OnButtonClick)
	ON_CBN_DROPDOWN(IDC_D_CBN_DelName,OnDropDown2)
	ON_CBN_DROPDOWN(IDC_D_CBN_DelFrom, OnDropDown)
	ON_CBN_DROPDOWN(IDC_D_CBN_DelTo, OnDropDown1)
	ON_CBN_DROPDOWN(IDC_D_CBN_DelPath, OnDropDown3)
	ON_CBN_SELCHANGE(IDC_D_CBN_DelName,OnCbnSelchangeName)
	ON_CBN_SELCHANGE(IDC_D_CBN_DelPath, OnCbnSelchangePath)
END_MESSAGE_MAP()


// CView_Del 绘图

void CView_Del::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// CView_Del 诊断

#ifdef _DEBUG
void CView_Del::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CView_Del::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CView_Del 消息处理程序


void CView_Del::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_btn_Del.Create(_T("删除"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(90, 350, 190, 380), this, IDC_D_BTN_Del);

	m_Sedit_NorE.Create(ES_LEFT | WS_VISIBLE | ES_READONLY | WS_CHILD, CRect(10, 10, 100, 40), this, 1);
	m_Sedit_NorE.SetWindowText(_T("删除"));


	m_cbbox_NorE.Create(CBS_DROPDOWNLIST | WS_VISIBLE | WS_TABSTOP | CBS_AUTOHSCROLL, CRect(110, 10, 250, 40), this, IDC_D_CBN_DelChoose);
	m_cbbox_NorE.InsertString(0, _T("城市"));
	m_cbbox_NorE.InsertString(1, _T("路径"));
	m_cbbox_NorE.SetCurSel(0);
	CRect rc;
	m_cbbox_NorE.GetDroppedControlRect(&rc);
	m_cbbox_NorE.GetParent()->ScreenToClient(&rc);
	rc.bottom += 2 * m_cbbox_NorE.GetItemHeight(-1);
	m_cbbox_NorE.MoveWindow(&rc);


	m_Sedit_Name.Create(ES_LEFT | WS_VISIBLE | ES_READONLY, CRect(10, 45, 100, 75), this, 1);
	m_Sedit_Name.SetWindowText(_T("名称"));
	m_cbbox_Name.Create(CBS_DROPDOWNLIST | WS_VISIBLE | WS_TABSTOP | CBS_AUTOHSCROLL, CRect(110, 45, 250, 75), this, IDC_D_CBN_DelName);


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


	m_Sedit_From.Create(ES_LEFT | ES_READONLY, CRect(10, 45, 100, 75), this, 1);
	m_Sedit_From.SetWindowText(_T("起点"));
	m_cbbox_From.Create(CBS_DROPDOWNLIST | WS_TABSTOP | CBS_AUTOHSCROLL, CRect(110, 45, 250, 75), this, IDC_D_CBN_DelFrom);


	m_Sedit_To.Create(ES_LEFT | ES_READONLY, CRect(10, 80, 100, 110), this, 1);
	m_Sedit_To.SetWindowText(_T("终点"));
	m_cbbox_To.Create(CBS_DROPDOWNLIST | WS_TABSTOP | CBS_AUTOHSCROLL, CRect(110, 80, 250, 110), this, IDC_D_CBN_DelTo);


	m_Sedit_Path.Create(ES_LEFT | ES_READONLY, CRect(10, 115, 100, 145), this, 1);
	m_Sedit_Path.SetWindowText(_T("路径"));
	m_cbbox_Path.Create(CBS_DROPDOWNLIST | WS_TABSTOP | CBS_AUTOHSCROLL, CRect(110, 115, 250, 145), this, IDC_D_CBN_DelPath);


	m_Sedit_Length.Create(ES_LEFT | ES_READONLY, CRect(10, 150, 100, 180), this, 1);
	m_Sedit_Length.SetWindowText(_T("长度"));
	m_edit_Length.Create(ES_LEFT | WS_BORDER | ES_READONLY, CRect(110, 150, 250, 180), this, 1);
}

void CView_Del::OnCbnEditchange()
{
	if (m_cbbox_NorE.GetCurSel() == 0) {
		m_cbbox_Name.ShowWindow(SW_SHOW);
		m_Sedit_Name.ShowWindow(SW_SHOW);
		m_Sedit_Code.ShowWindow(SW_SHOW);
		m_Sedit_Intro.ShowWindow(SW_SHOW);
		m_Sedit_X.ShowWindow(SW_SHOW);
		m_Sedit_Y.ShowWindow(SW_SHOW);
		m_edit_Code.ShowWindow(SW_SHOW);
		m_edit_Intro.ShowWindow(SW_SHOW);
		m_edit_X.ShowWindow(SW_SHOW);
		m_edit_Y.ShowWindow(SW_SHOW);


		m_Sedit_Length.ShowWindow(SW_HIDE);
		m_Sedit_From.ShowWindow(SW_HIDE);
		m_Sedit_To.ShowWindow(SW_HIDE);
		m_Sedit_Path.ShowWindow(SW_HIDE);
		m_edit_Length.ShowWindow(SW_HIDE);
		m_cbbox_From.ShowWindow(SW_HIDE);
		m_cbbox_To.ShowWindow(SW_HIDE);
		m_cbbox_Path.ShowWindow(SW_HIDE);
	}
	else {
		m_cbbox_Name.ShowWindow(SW_HIDE);
		m_Sedit_Name.ShowWindow(SW_HIDE);
		m_Sedit_Code.ShowWindow(SW_HIDE);
		m_Sedit_Intro.ShowWindow(SW_HIDE);
		m_Sedit_X.ShowWindow(SW_HIDE);
		m_Sedit_Y.ShowWindow(SW_HIDE);
		m_edit_Code.ShowWindow(SW_HIDE);
		m_edit_Intro.ShowWindow(SW_HIDE);
		m_edit_X.ShowWindow(SW_HIDE);
		m_edit_Y.ShowWindow(SW_HIDE);


		m_Sedit_Length.ShowWindow(SW_SHOW);
		m_Sedit_From.ShowWindow(SW_SHOW);
		m_Sedit_To.ShowWindow(SW_SHOW);
		m_Sedit_Path.ShowWindow(SW_SHOW);
		m_edit_Length.ShowWindow(SW_SHOW);
		m_cbbox_To.ShowWindow(SW_SHOW);
		m_cbbox_From.ShowWindow(SW_SHOW);
		m_cbbox_Path.ShowWindow(SW_SHOW);

	}
}

void CView_Del::OnDropDown()
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
	rc.bottom += num * m_cbbox_NorE.GetItemHeight(-1);
	m_cbbox_From.MoveWindow(&rc);
}

void CView_Del::OnDropDown1()
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
	rc.bottom += num * m_cbbox_NorE.GetItemHeight(-1);
	m_cbbox_To.MoveWindow(&rc);

}

void CView_Del::OnDropDown2()
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
	rc.bottom += num * m_cbbox_NorE.GetItemHeight(-1);
	m_cbbox_Name.MoveWindow(&rc);
}

void CView_Del::OnDropDown3()
{
	m_cbbox_Path.ResetContent();

	CString from, to;
	m_cbbox_From.GetWindowText(from);
	m_cbbox_To.GetWindowText(to);
	if (from != _T("") && to != _T("")) {
		CRect rc;
		string From, To;
		From = CT2A(from.GetBuffer());
		To = CT2A(to.GetBuffer());
		vector<Edge> EdgeList = theApp.G.getEdgeList(From, To);
		int num = EdgeList.size();
		for (int i = 0; i < num; i++) {
			m_cbbox_Path.AddString(LPCTSTR(EdgeList[i].getName().c_str()));
		}
		m_cbbox_Path.GetDroppedControlRect(&rc);
		m_cbbox_Path.GetParent()->ScreenToClient(&rc);
		rc.bottom += num * m_cbbox_NorE.GetItemHeight(-1);
		m_cbbox_Path.MoveWindow(&rc);
	}
}

void CView_Del::OnCbnSelchangeName()
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

void CView_Del::OnCbnSelchangePath()
{
	CString from, to;
	string From, To;
	m_cbbox_From.GetWindowTextA(from);
	m_cbbox_To.GetWindowTextA(to);
	From = CT2A(from);
	To = CT2A(to);
	Edge tmp = theApp.G.getEdge(From,To,m_cbbox_Path.GetCurSel());
	CString temp;
	temp.Format("%d", tmp.getLength());
	m_edit_Length.SetWindowTextA(LPCTSTR(temp));
}

void CView_Del::OnCbnSelchange()
{
	if (m_cbbox_NorE.GetCurSel() == 0) {
		m_cbbox_Name.ShowWindow(SW_SHOW);
		m_Sedit_Name.ShowWindow(SW_SHOW);
		m_Sedit_Code.ShowWindow(SW_SHOW);
		m_Sedit_Intro.ShowWindow(SW_SHOW);
		m_Sedit_X.ShowWindow(SW_SHOW);
		m_Sedit_Y.ShowWindow(SW_SHOW);
		m_edit_Code.ShowWindow(SW_SHOW);
		m_edit_Intro.ShowWindow(SW_SHOW);
		m_edit_X.ShowWindow(SW_SHOW);
		m_edit_Y.ShowWindow(SW_SHOW);


		m_Sedit_Length.ShowWindow(SW_HIDE);
		m_Sedit_From.ShowWindow(SW_HIDE);
		m_Sedit_To.ShowWindow(SW_HIDE);
		m_Sedit_Path.ShowWindow(SW_HIDE);
		m_edit_Length.ShowWindow(SW_HIDE);
		m_cbbox_From.ShowWindow(SW_HIDE);
		m_cbbox_To.ShowWindow(SW_HIDE);
		m_cbbox_Path.ShowWindow(SW_HIDE);
	}
	else {
		m_cbbox_Name.ShowWindow(SW_HIDE);
		m_Sedit_Name.ShowWindow(SW_HIDE);
		m_Sedit_Code.ShowWindow(SW_HIDE);
		m_Sedit_Intro.ShowWindow(SW_HIDE);
		m_Sedit_X.ShowWindow(SW_HIDE);
		m_Sedit_Y.ShowWindow(SW_HIDE);
		m_edit_Code.ShowWindow(SW_HIDE);
		m_edit_Intro.ShowWindow(SW_HIDE);
		m_edit_X.ShowWindow(SW_HIDE);
		m_edit_Y.ShowWindow(SW_HIDE);


		m_Sedit_Length.ShowWindow(SW_SHOW);
		m_Sedit_From.ShowWindow(SW_SHOW);
		m_Sedit_To.ShowWindow(SW_SHOW);
		m_Sedit_Path.ShowWindow(SW_SHOW);
		m_edit_Length.ShowWindow(SW_SHOW);
		m_cbbox_To.ShowWindow(SW_SHOW);
		m_cbbox_From.ShowWindow(SW_SHOW);
		m_cbbox_Path.ShowWindow(SW_SHOW);

	}
}

void CView_Del::OnButtonClick()
{
	//TODO

	if (m_cbbox_NorE.GetCurSel() == 0) {

		if (m_cbbox_Name.GetCurSel() == CB_ERR)
		{
			AfxMessageBox(_T("输入错误"));
			return;
		}

		theApp.G.DelNode(m_cbbox_Name.GetCurSel());

		m_cbbox_Name.SetCurSel(-1);
		m_edit_Code.SetWindowTextA(_T(""));
		m_edit_Intro.SetWindowTextA(_T(""));
		m_edit_X.SetWindowTextA(_T(""));
		m_edit_Y.SetWindowTextA(_T(""));

		AfxMessageBox(_T("删除成功"));
	}
	else if (m_cbbox_NorE.GetCurSel() == 1) {
		CString from, to, name;
		string From, To, Name;

		if (m_cbbox_From.GetCurSel() == CB_ERR
			|| m_cbbox_To.GetCurSel() == CB_ERR
			|| m_cbbox_Path.GetCurSel() == CB_ERR)
		{
			AfxMessageBox(_T("输入错误"));
			return;
		}

		m_cbbox_From.GetWindowTextA(from);
		m_cbbox_To.GetWindowTextA(to);
		m_cbbox_Path.GetWindowTextA(name);
		From = CT2A(from);
		To = CT2A(to);
		Name = CT2A(name);
		theApp.G.DelEdge(From, To, Name);

		m_cbbox_From.SetCurSel(-1);
		m_cbbox_To.SetCurSel(-1);
		m_cbbox_Path.SetCurSel(-1);
		m_edit_Length.SetWindowTextA(_T(""));

		AfxMessageBox(_T("删除成功"));
	}

	CMainFrame* m_pHost = (CMainFrame*)AfxGetMainWnd();
	m_pHost->rePaintLup();
}