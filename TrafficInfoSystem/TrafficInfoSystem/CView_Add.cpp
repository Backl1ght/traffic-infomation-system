// CView_AddNode.cpp: 实现文件
//

#include "stdafx.h"
#include "TrafficInfoSystem.h"
#include "CView_Add.h"
#include "MainFrm.h"



#define IDC_D_BTN_Add 10000
#define IDC_D_CBN_Choose	10001
#define IDC_D_CBN_From 11000
#define IDC_D_CBN_To 11001


// CView_AddNode

IMPLEMENT_DYNCREATE(CView_Add, CView)

CView_Add::CView_Add()
{

}

CView_Add::~CView_Add()
{
}

//消息映射
BEGIN_MESSAGE_MAP(CView_Add, CView)
	ON_CBN_SELCHANGE(IDC_D_CBN_Choose, OnCbnSelchange)
	ON_CBN_EDITCHANGE(IDC_D_CBN_Choose, OnCbnEditchange)
	ON_BN_CLICKED(IDC_D_BTN_Add, OnButtonClick)
	ON_CBN_DROPDOWN(IDC_D_CBN_From,OnDropDown)
	ON_CBN_DROPDOWN(IDC_D_CBN_To,OnDropDown1)
END_MESSAGE_MAP()


// CView_AddNode 绘图

void CView_Add::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// CView_AddNode 诊断

#ifdef _DEBUG
void CView_Add::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CView_Add::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CView_AddNode 消息处理程序

int Str2Int(string s) {
	int l = s.length();
	int res = 0;
	for (int i = 0; i < l; i++) {
		if (s[i] > '9' || s[i] < '0')
			return -1;
		res *= 10;
		res += s[i] - '0';
	}
	return res;
}

void CView_Add::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	m_btn_Add.Create(_T("添加"),WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,CRect(90,350,190,380),this,IDC_D_BTN_Add);
	
	m_Sedit_NorE.Create(ES_LEFT | WS_VISIBLE | ES_READONLY| WS_CHILD, CRect(10, 10, 100, 40), this, 1);
	m_Sedit_NorE.SetWindowText(_T("功能"));


	m_cbbox_NorE.Create(CBS_DROPDOWNLIST | WS_VISIBLE | WS_TABSTOP | CBS_AUTOHSCROLL,CRect(110,10,250,40),this, IDC_D_CBN_Choose);
	m_cbbox_NorE.InsertString(0,_T("城市"));
	m_cbbox_NorE.InsertString(1, _T("路径"));
	m_cbbox_NorE.SetCurSel(0);
	CRect rc;
	m_cbbox_NorE.GetDroppedControlRect(&rc);
	m_cbbox_NorE.GetParent()->ScreenToClient(&rc);
	rc.bottom += 2 * m_cbbox_NorE.GetItemHeight(-1);
	m_cbbox_NorE.MoveWindow(&rc);



	m_Sedit_Name.Create(ES_LEFT | WS_VISIBLE | ES_READONLY, CRect(10, 45, 100, 75), this, 1);
	m_Sedit_Name.SetWindowText(_T("名称"));
	m_edit_Name.Create(ES_LEFT | WS_VISIBLE | WS_BORDER, CRect(110, 45, 250, 75), this, 1);

	
	m_Sedit_Code.Create(ES_LEFT | WS_VISIBLE | ES_READONLY, CRect(10, 80, 100, 110), this, 1);
	m_Sedit_Code.SetWindowText(_T("代号"));
	m_edit_Code.Create(ES_LEFT | WS_VISIBLE | WS_BORDER, CRect(110, 80, 250, 110), this, 1);

	
	
	m_Sedit_Intro.Create(ES_LEFT | WS_VISIBLE | ES_READONLY, CRect(10, 115, 100, 145), this, 1);
	m_Sedit_Intro.SetWindowText(_T("简介"));
	m_edit_Intro.Create(ES_LEFT | WS_VISIBLE | WS_BORDER, CRect(110, 115, 250, 145), this, 1);


	m_Sedit_X.Create(ES_LEFT | WS_VISIBLE | ES_READONLY, CRect(10, 150, 100, 180), this, 1);
	m_Sedit_X.SetWindowText(_T("横坐标"));
	m_edit_X.Create(ES_LEFT | WS_VISIBLE | WS_BORDER, CRect(110, 150, 250, 180), this, 1);


	m_Sedit_Y.Create(ES_LEFT | WS_VISIBLE | ES_READONLY, CRect(10, 185, 100, 215), this, 1);
	m_Sedit_Y.SetWindowText(_T("纵坐标"));
	m_edit_Y.Create(ES_LEFT | WS_VISIBLE | WS_BORDER, CRect(110, 185, 250, 215), this, 1);


	m_Sedit_Length.Create(ES_LEFT | ES_READONLY, CRect(10, 80, 100, 110), this, 1);
	m_Sedit_Length.SetWindowText(_T("长度"));
	m_edit_Length.Create(ES_LEFT | WS_BORDER, CRect(110, 80, 250, 110), this, 1);


	m_Sedit_From.Create(ES_LEFT | ES_READONLY, CRect(10, 115, 100, 145), this, 1);
	m_Sedit_From.SetWindowText(_T("起点"));
	m_cbbox_From.Create(CBS_DROPDOWNLIST, CRect(110, 115, 250, 145), this, IDC_D_CBN_From);


	m_Sedit_To.Create(ES_LEFT | ES_READONLY, CRect(10, 150, 100, 180), this, 1);
	m_Sedit_To.SetWindowText(_T("终点"));
	m_cbbox_To.Create(CBS_DROPDOWNLIST, CRect(110, 150, 250, 180), this, IDC_D_CBN_To);


}

void CView_Add::OnButtonClick()
{
	//TODO
	if (m_cbbox_NorE.GetCurSel() == CB_ERR)
		return;

	if (m_cbbox_NorE.GetCurSel() == 0) {
		string Name, Code, Intro, X, Y;
		CString str;
		m_edit_Name.GetWindowText(str);
		Name = CT2A(str.GetBuffer());

		m_edit_Code.GetWindowText(str);
		Code = CT2A(str.GetBuffer());

		m_edit_Intro.GetWindowText(str);
		Intro = CT2A(str.GetBuffer());

		m_edit_X.GetWindowText(str);
		X = CT2A(str.GetBuffer());

		m_edit_Y.GetWindowText(str);
		Y = CT2A(str.GetBuffer());

		int x = Str2Int(X), y = Str2Int(Y);
		if (x>0 && y>0 && x<=1050 && y<=450) {
			theApp.G.AddNode(Name, Code, Intro, x, y);

			m_edit_Name.SetWindowText(_T(""));
			m_edit_Code.SetWindowText(_T(""));
			m_edit_Intro.SetWindowText(_T(""));
			m_edit_X.SetWindowText(_T(""));
			m_edit_Y.SetWindowText(_T(""));

			AfxMessageBox(_T("添加成功"));
		}
		else {
			AfxMessageBox(_T("输入错误"));
		}
	}
	else if (m_cbbox_NorE.GetCurSel() == 1) {
		string Name, Length, From, To;
		CString str;

		m_edit_Name.GetWindowText(str);
		Name = CT2A(str.GetBuffer());

		m_edit_Length.GetWindowText(str);
		Length = CT2A(str.GetBuffer());

		m_cbbox_From.GetWindowText(str);
		From = CT2A(str.GetBuffer());

		m_cbbox_To.GetWindowText(str);
		To = CT2A(str.GetBuffer());

		int length = Str2Int(Length);

		if (length > 0) {
			theApp.G.AddEdge(From, To, length, Name);

			m_edit_Name.SetWindowText(_T(""));
			m_edit_Length.SetWindowText(_T(""));
			m_cbbox_From.SetCurSel(-1);
			m_cbbox_To.SetCurSel(-1);

			AfxMessageBox(_T("添加成功"));
		}
		else {
			AfxMessageBox(_T("输入错误"));
		}
	}
	
	//画板重绘
	CMainFrame* m_pHost = (CMainFrame*)AfxGetMainWnd();
	m_pHost->rePaintLup();
}

void CView_Add::OnCbnSelchange()
{
	if (m_cbbox_NorE.GetCurSel() == 0) {
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
		m_edit_Length.ShowWindow(SW_HIDE);
		m_cbbox_From.ShowWindow(SW_HIDE);
		m_cbbox_To.ShowWindow(SW_HIDE);
	}
	else {
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
		m_edit_Length.ShowWindow(SW_SHOW);
		m_cbbox_From.ShowWindow(SW_SHOW);
		m_cbbox_To.ShowWindow(SW_SHOW);
	}
}

void CView_Add::OnCbnEditchange()
{
	if (m_cbbox_NorE.GetCurSel() == 0) {
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
		m_edit_Length.ShowWindow(SW_HIDE);
		m_cbbox_From.ShowWindow(SW_HIDE);
		m_cbbox_To.ShowWindow(SW_HIDE);
	}
	else {
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
		m_edit_Length.ShowWindow(SW_SHOW);
		m_cbbox_From.ShowWindow(SW_SHOW);
		m_cbbox_To.ShowWindow(SW_SHOW);
	}
}

void CView_Add::OnDropDown()
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

void CView_Add::OnDropDown1()
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
