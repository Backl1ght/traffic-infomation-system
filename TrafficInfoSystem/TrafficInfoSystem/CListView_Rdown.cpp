// CListView_Rdown.cpp: 实现文件
//

#include "stdafx.h"
#include "TrafficInfoSystem.h"
#include "CListView_Rdown.h"
#include "MainFrm.h"


#define IDC_D_ED 23333
// CListView_Rdown

IMPLEMENT_DYNCREATE(CListView_Rdown, CListView)

CListView_Rdown::CListView_Rdown()
{

}

CListView_Rdown::~CListView_Rdown()
{
}

BEGIN_MESSAGE_MAP(CListView_Rdown, CListView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CListView_Rdown::OnNMDblclk)
	ON_EN_KILLFOCUS(IDC_D_ED,OnEditKillFocus)
END_MESSAGE_MAP()


// CListView_Rdown 诊断

#ifdef _DEBUG
void CListView_Rdown::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CListView_Rdown::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CListView_Rdown 消息处理程序


void CListView_Rdown::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	GetListCtrl().ModifyStyle(0, LVS_REPORT | LVS_EDITLABELS);            //List-View Window Styles

	GetListCtrl().SetExtendedStyle(GetListCtrl().GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	////在视图中插入列
	int col = 2;
	int row = 0;

	////插入列
	GetListCtrl().InsertColumn(0, _T("项"), LVCFMT_LEFT, 115, -1);
	GetListCtrl().InsertColumn(1, _T("值"), LVCFMT_LEFT, 160, -1);


}

void CListView_Rdown::Listchange(int node_id)
{
	Node tmp = theApp.G.getNode(node_id);

	GetListCtrl().DeleteAllItems();

	GetListCtrl().InsertItem(0, _T("类型"));
	GetListCtrl().InsertItem(1, _T("编号"));
	GetListCtrl().InsertItem(2,  _T("名称"));
	GetListCtrl().InsertItem(3,  _T("代号"));
	GetListCtrl().InsertItem(4,  _T("简介"));
	GetListCtrl().InsertItem(5,  _T("X"));
	GetListCtrl().InsertItem(6,  _T("Y"));

	GetListCtrl().SetItemText(0, 1, _T("城市"));
	CString cstr;
	cstr.Format("%d", tmp.getID());
	GetListCtrl().SetItemText(1, 1, cstr);
	cstr = tmp.getName().c_str();
	GetListCtrl().SetItemText(2, 1, cstr);
	cstr = tmp.getCode().c_str();
	GetListCtrl().SetItemText(3, 1, cstr);
	cstr = tmp.getIntro().c_str();
	GetListCtrl().SetItemText(4, 1, cstr);
	cstr.Format("%d", tmp.getX());
	GetListCtrl().SetItemText(5, 1, cstr);
	cstr.Format("%d", tmp.getY());
	GetListCtrl().SetItemText(6, 1, cstr);
}

void CListView_Rdown::Listchange(int from, int to)
{
	Edge tmp;
	vector<Edge>v = theApp.G.getEdgeList(from,to);
	if (v.empty())
		return;
	else
		tmp = v[0];
	GetListCtrl().DeleteAllItems();

	GetListCtrl().InsertItem(0, _T("类型"));
	GetListCtrl().InsertItem(1, _T("起点"));
	GetListCtrl().InsertItem(2, _T("终点"));
	GetListCtrl().InsertItem(3, _T("名称"));
	GetListCtrl().InsertItem(4, _T("长度"));

	GetListCtrl().SetItemText(0, 1, _T("路径"));
	CString cstr;
	cstr = theApp.G.getNode(from).getName().c_str();
	GetListCtrl().SetItemText(1, 1, cstr);
	cstr = theApp.G.getNode(to).getName().c_str();
	GetListCtrl().SetItemText(2, 1, cstr);
	cstr = tmp.getName().c_str();
	GetListCtrl().SetItemText(3, 1, cstr);
	cstr.Format("%d", tmp.getLength());
	GetListCtrl().SetItemText(4, 1, cstr);

}


void CListView_Rdown::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	m_pEdit =new CEdit();

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rect;
	iRow = pNMListView->iItem;
	iCol = pNMListView->iSubItem;

	CString cstr = GetListCtrl().GetItemText(iRow, iCol);
	if (cstr == _T("")) {
		delete m_pEdit;
		return;
	}

	GetListCtrl().GetSubItemRect(iRow, iCol, LVIR_LABEL, rect);
	m_pEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT,rect,&GetListCtrl(),IDC_D_ED);
	m_pEdit->SetWindowTextA(GetListCtrl().GetItemText(iRow, iCol));
	m_pEdit->ShowWindow(SW_SHOW);
	m_pEdit->SetFocus();
	m_pEdit->ShowCaret();
	m_pEdit->SetSel(-1);


}
void CListView_Rdown::OnEditKillFocus()
{
	CString cstr = GetListCtrl().GetItemText(0, 1),t;
	if (cstr == _T("城市")) {
		if(iRow==1){
			AfxMessageBox(_T("城市编号不能修改"));
		}
		else {
			int id;
			t = GetListCtrl().GetItemText(1, 1);
			id = _ttoi(t);
			m_pEdit->GetWindowTextA(cstr);
			if (theApp.G.MdfC(id, iRow, cstr)) {
				GetListCtrl().SetItemText(iRow, iCol, cstr);
			}
			else {
				AfxMessageBox(_T("错误"));
			}

		}
	}
	else if (cstr == _T("路径")) {
		t = GetListCtrl().GetItemText(1, 1);
		string from = CT2A(t);
		t = GetListCtrl().GetItemText(2, 1);
		string to = CT2A(t);
		int f = theApp.G.getNodeid(from), t = theApp.G.getNodeid(to);
		m_pEdit->GetWindowTextA(cstr);
		if (iRow == 3 || iRow == 4) {
			theApp.G.MdfE(from, to, iRow, cstr);
			GetListCtrl().SetItemText(iRow, iCol, cstr);

		}
		else {
			AfxMessageBox(_T("起点和终点不能修改"));
		}
	}


	CMainFrame* m_pHost = (CMainFrame*)AfxGetMainWnd();
	m_pHost->rePaintLup();



	m_pEdit->DestroyWindow();
	delete m_pEdit;

}
