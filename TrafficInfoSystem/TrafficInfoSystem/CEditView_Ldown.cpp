// CEditView_Ldown.cpp: 实现文件
//

#include "stdafx.h"
#include "TrafficInfoSystem.h"
#include "CEditView_Ldown.h"
#include "MainFrm.h"

#include<stack>
using namespace std;

// CEditView_Ldown

IMPLEMENT_DYNCREATE(CEditView_Ldown, CEditView)

CEditView_Ldown::CEditView_Ldown()
{
}

CEditView_Ldown::~CEditView_Ldown()
{
}

BEGIN_MESSAGE_MAP(CEditView_Ldown, CEditView)
END_MESSAGE_MAP()


// CEditView_Ldown 诊断

#ifdef _DEBUG
void CEditView_Ldown::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CEditView_Ldown::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

void CEditView_Ldown::Editchange()
{
	int d[MAX_NODE*MAX_NODE];
	
	GetEditCtrl().SetSel(0, GetEditCtrl().GetWindowTextLengthA());
	GetEditCtrl().ReplaceSel(_T("任意两个顶点的最短距离\r\n"));

	theApp.G.ShortestPath(d);
	int n = theApp.G.getNode_num();
	int len_star=0,p=0;
	CString write;
	len_star = GetEditCtrl().GetWindowTextLengthA();
	write = _T("距离\t");
	GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
	GetEditCtrl().ReplaceSel(write);
	for (int i = 0; i < n; i++) {
		len_star = GetEditCtrl().GetWindowTextLengthA();
		write = theApp.G.getNode(i).getName().c_str();
		write+=_T("\t");
		GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
		GetEditCtrl().ReplaceSel(write);
	}
	len_star = GetEditCtrl().GetWindowTextLengthA();
	write = _T("\r\n");
	GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
	GetEditCtrl().ReplaceSel(write);
	for (int i = 0; i < n; i++) {
		len_star = GetEditCtrl().GetWindowTextLengthA();
		write = theApp.G.getNode(i).getName().c_str();
		write += _T("\t");
		GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
		GetEditCtrl().ReplaceSel(write);
		for (int j = 0; j < MAX_NODE; j++) {
			if (j < n) {
				len_star = GetEditCtrl().GetWindowTextLengthA();
				if (d[p] == INF)
					write=_T("INF\t");
				else
					write.Format("%d\t", d[p]);
				GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
				GetEditCtrl().ReplaceSel(write);
				++p;
			}
		}
		len_star = GetEditCtrl().GetWindowTextLengthA();
		write = _T("\r\n");
		GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
		GetEditCtrl().ReplaceSel(write);
	}
}
void CEditView_Ldown::Editchange(string src)
{
	int d[MAX_NODE];
	theApp.G.ShortestPath(src, d);

	GetEditCtrl().SetSel(0, GetEditCtrl().GetWindowTextLengthA());
	GetEditCtrl().ReplaceSel(_T("源点为 "));

	theApp.G.ShortestPath(src,d);
	int n = theApp.G.getNode_num();
	int len_star = 0, p = 0;

	CString write;
	len_star = GetEditCtrl().GetWindowTextLengthA();
	write = src.c_str();
	GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
	GetEditCtrl().ReplaceSel(write);

	len_star = GetEditCtrl().GetWindowTextLengthA();
	write = _T(" 的最短距离\r\n");
	GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
	GetEditCtrl().ReplaceSel(write);

	len_star = GetEditCtrl().GetWindowTextLengthA();
	write = _T("距离\t");
	GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
	GetEditCtrl().ReplaceSel(write);
	for (int i = 0; i < n; i++) {
		len_star = GetEditCtrl().GetWindowTextLengthA();
		write = theApp.G.getNode(i).getName().c_str();
		write += _T("\t");
		GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
		GetEditCtrl().ReplaceSel(write);
	}
	len_star = GetEditCtrl().GetWindowTextLengthA();
	write = _T("\r\n");
	GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
	GetEditCtrl().ReplaceSel(write);
	len_star = GetEditCtrl().GetWindowTextLengthA();
	write = _T("\t");
	GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
	GetEditCtrl().ReplaceSel(write);
	for (int i = 0; i < n; i++) {
		len_star = GetEditCtrl().GetWindowTextLengthA();
		if (d[i] == INF)
			write = _T("INF\t");
		else
			write.Format("%d\t", d[i]);
		GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
		GetEditCtrl().ReplaceSel(write);
	}
}
void CEditView_Ldown::Editchange(string from, string to)
{
	int path[MAX_NODE],dis;

	GetEditCtrl().SetSel(0, GetEditCtrl().GetWindowTextLengthA());
	GetEditCtrl().ReplaceSel(_T("\r\n"));

	theApp.G.ShortestPath(from, to, dis, path);
	int n = theApp.G.getNode_num();
	int len_star = 0, p = 0;
	CString write;
	len_star = GetEditCtrl().GetWindowTextLengthA();
	write.Format("距离为%d\r\n",dis);
	GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
	GetEditCtrl().ReplaceSel(write);

	len_star = GetEditCtrl().GetWindowTextLengthA();
	write.Format("路径：\r\n", dis);
	GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
	GetEditCtrl().ReplaceSel(write);

	if (dis == 0)
		return;

	stack<int>s;
	int pos = theApp.G.getNodeid(to),pre=-1;
	while (pos != -1) {
		s.push(pos);
		pos = path[pos];
	}
	pre = s.top();
	s.pop();
	while (!s.empty()) {
		pos = s.top();
		s.pop();
		len_star = GetEditCtrl().GetWindowTextLengthA();
		write = theApp.G.getNode(pre).getName().c_str();
		write += _T("  ->  ");
		GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
		GetEditCtrl().ReplaceSel(write);


		len_star = GetEditCtrl().GetWindowTextLengthA();
		write = theApp.G.getEdge(pre,pos,0).getName().c_str();
		write += _T("  ->  ");
		GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
		GetEditCtrl().ReplaceSel(write); 
	
		pre = pos;
	}

	len_star = GetEditCtrl().GetWindowTextLengthA();
	write = theApp.G.getNode(pos).getName().c_str();
	GetEditCtrl().SetSel(len_star, len_star + write.GetLength());
	GetEditCtrl().ReplaceSel(write);

	CMainFrame* m_pHost = (CMainFrame*)AfxGetMainWnd();
	m_pHost->OnPaintSP(theApp.G.getNodeid(to),path);

}
#endif
#endif //_DEBUG


// CEditView_Ldown 消息处理程序


void CEditView_Ldown::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	GetEditCtrl().SetReadOnly();

}


BOOL CEditView_Ldown::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类

	m_dwDefaultStyle =
		AFX_WS_DEFAULT_VIEW | WS_VSCROLL | ES_AUTOVSCROLL 
		| WS_HSCROLL | ES_AUTOHSCROLL | ES_MULTILINE | ES_NOHIDESEL;

	return CEditView::PreCreateWindow(cs);
}
