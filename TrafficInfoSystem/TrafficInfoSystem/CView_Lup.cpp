// CView_Lup.cpp: 实现文件
//

#include "stdafx.h"
#include "TrafficInfoSystem.h"
#include "CView_Lup.h"
#include "MainFrm.h"
#include <cmath>
#include<stack>


// CView_Lup

IMPLEMENT_DYNCREATE(CView_Lup, CView)

CView_Lup::CView_Lup()
{

}

CView_Lup::~CView_Lup()
{
}

BEGIN_MESSAGE_MAP(CView_Lup, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CView_Lup 绘图

void CView_Lup::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// CView_Lup 诊断

#ifdef _DEBUG
void CView_Lup::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CView_Lup::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif
#endif //_DEBUG


// CView_Lup 消息处理程序

//重绘视图
void CView_Lup::OnRepaint()
{
	//清空视图
	CDC* pDC = GetDC();
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, RGB(255, 255, 255));

	Node *List = theApp.G.getNodeList();
	int n = theApp.G.getNode_num();
	int x, y;

	CPen MyPen, *OldPen;
	MyPen.CreatePen(PS_DASH, 3, RGB(0, 0, 0));
	OldPen = pDC->SelectObject(&MyPen);

	CBrush MyBrush, *OldBrush;
	MyBrush.CreateSolidBrush(RGB(0, 255, 0));
	OldBrush = pDC->SelectObject(&MyBrush);

	//画边
	int x1, y1, x2, y2;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			vector<Edge>v = theApp.G.getEdgeList(i, j);
			if (v.size() > 0) {
				x1 = List[i].getX();
				y1 = List[i].getY();
				x2 = List[j].getX();
				y2 = List[j].getY();

				pDC->MoveTo(x1, y1);
				pDC->LineTo(x2, y2);

			}
		}
	}
	pDC->SelectObject(OldPen);
	MyPen.DeleteObject();

	MyPen.CreatePen(PS_DASH, 3, RGB(0, 0, 0));
	OldPen = pDC->SelectObject(&MyPen);

	//画点
	for (int i = 0; i < n; i++) {
		x = List[i].getX();
		y = List[i].getY();

		CPoint point1(x - R, y + R);
		CPoint point2(x + R, y - R);

		pDC->Ellipse(point1.x, point1.y, point2.x, point2.y);

	}
	pDC->SelectObject(OldPen);
	MyPen.DeleteObject();

	//显示城市名
	MyPen.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
	OldPen = pDC->SelectObject(&MyPen);

	CString name;
	for (int i = 0; i < n; i++) {
		x = List[i].getX();
		y = List[i].getY();
		name = List[i].getName().c_str();

		pDC->TextOut(x, y + 2*R - 5,name);

	}

	pDC->SelectObject(OldBrush);
	MyBrush.DeleteObject();
}

void CView_Lup::OnPaintSp(int to,int* path)
{
	CDC* pDC = GetDC();
	CRect rc;
	GetClientRect(rc);

	Node *List = theApp.G.getNodeList();
	int n = theApp.G.getNode_num();

	CPen MyPen, *OldPen;
	MyPen.CreatePen(PS_DASH, 3, RGB(255, 0, 0));
	OldPen = pDC->SelectObject(&MyPen);

	stack<int>s;
	int pos=to, pre;
	int x1, y1, x2, y2;

	while (pos != -1) {
		s.push(pos);
		pos = path[pos];
	}
	pre = s.top();
	s.pop();

	while (!s.empty()) {
		pos = s.top();
		s.pop();

		x1 = List[pos].getX();
		y1 = List[pos].getY();
		x2 = List[pre].getX();
		y2 = List[pre].getY();

		pDC->MoveTo(x1, y1);
		pDC->LineTo(x2, y2);


		pre = pos;
	}

	pDC->SelectObject(OldPen);
	MyPen.DeleteObject();

	MyPen.CreatePen(PS_DASH, 3, RGB(0, 0, 0));
	OldPen = pDC->SelectObject(&MyPen);

	CBrush MyBrush, *OldBrush;
	MyBrush.CreateSolidBrush(RGB(0, 255, 0));
	OldBrush = pDC->SelectObject(&MyBrush);

	int x, y;
	for (int i = 0; i < n; i++) {
		x = List[i].getX();
		y = List[i].getY();

		CPoint point1(x - R, y + R);
		CPoint point2(x + R, y - R);

		pDC->Ellipse(point1.x, point1.y, point2.x, point2.y);

	}
	pDC->SelectObject(OldPen);
	MyPen.DeleteObject();

	pDC->SelectObject(OldBrush);
	MyBrush.DeleteObject();
}


//鼠标左键点击
void CView_Lup::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//SetCapture();

	m_bLBtnDown = true;

	//TODO:更改右下视图

	//TODO:是结点
	int n = theApp.G.getNode_num();
	int x, y;
	for (int i = 0; i < n; i++) {
		x = theApp.G.getNode(i).getX();
		y = theApp.G.getNode(i).getY();
		if ((x - point.x)*(x - point.x) + (y - point.y)*(y - point.y) <= R*R) {//在结点范围内
			node_id = i;
			//更改列表信息
			CMainFrame* m_pHost = (CMainFrame*)AfxGetMainWnd();
			m_pHost->Listchange(i);

			OnRepaint();

			return;
		}
	}
	node_id = -1;
	//TODO:是边
	int x1, y1, x2, y2;
	x = point.x; y = point.y;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			x1 = theApp.G.getNode(i).getX();
			y1 = theApp.G.getNode(i).getY();
			x2 = theApp.G.getNode(j).getX();
			y2 = theApp.G.getNode(j).getY();
			if (x > min(x1, x2) && x<max(x1, x2) && y>min(y1, y2) && y < max(y1, y2)
				&& fabs(atan(1.0*(y - y1) / (x - x1)) - atan(1.0*(y2 - y1) / (x2 - x1))) < 0.17)
			{
				//更改列表信息
				CMainFrame* m_pHost = (CMainFrame*)AfxGetMainWnd();
				m_pHost->Listchange(i,j);
				return;
			}
		}
	}


	CView::OnLButtonDown(nFlags, point);
}

void CView_Lup::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bLBtnDown == false)
		return;

	if (node_id == -1)
		return;

	if (m_bDragged == true)
		return;
	/*
	if (m_bDragged == true)
		return;
	*/

	m_bDragged = true;

	//TODO:擦除点
	CDC* pDC = GetDC();
	CPen MyPen, *OldPen;
	MyPen.CreatePen(PS_DASH, 3, RGB(255, 255, 255)); 
	OldPen = pDC->SelectObject(&MyPen);

	CBrush MyBrush, *OldBrush;
	MyBrush.CreateSolidBrush(RGB(255, 255, 255));
	OldBrush = pDC->SelectObject(&MyBrush);

	CPoint point1(theApp.G.getNode(node_id).getX() - R, theApp.G.getNode(node_id).getY() + R);
	CPoint point2(theApp.G.getNode(node_id).getX() + R, theApp.G.getNode(node_id).getY() - R);

	pDC->Ellipse(point1.x, point1.y, point2.x, point2.y);


	pDC->SelectObject(OldPen);
	MyPen.DeleteObject();
	pDC->SelectObject(OldBrush);
	MyBrush.DeleteObject();

	//TODO:擦除边和字


	CView::OnMouseMove(nFlags, point);
}


void CView_Lup::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	//ReleaseCapture();


	if (node_id == -1) {
		node_id = -1;
		m_bLBtnDown = false;
		m_bDragged = false;
		return;
	}
	if (m_bDragged == false) {
		node_id = -1;
		m_bLBtnDown = false;
		m_bDragged = false;
		return;
	}
	
	if (m_bLBtnDown == true) {

		theApp.G.MPos(node_id, point.x, point.y);

		CMainFrame* m_pHost = (CMainFrame*)AfxGetMainWnd();
		m_pHost->Listchange(node_id);

		OnRepaint();

	}

	CView::OnLButtonUp(nFlags, point);
}





BOOL CView_Lup::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CView::OnChildNotify(message, wParam, lParam, pLResult);
}
