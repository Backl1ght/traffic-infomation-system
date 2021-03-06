// CTabView_Rup.cpp: 实现文件
//

#include "stdafx.h"
#include "TrafficInfoSystem.h"
#include "CTabView_Rup.h"

#include "CView_Add.h"
#include "CView_Del.h"
#include "CView_Query.h"


// CTabView_Rup

IMPLEMENT_DYNCREATE(CTabView_Rup, CTabView)

CTabView_Rup::CTabView_Rup()
{

}

CTabView_Rup::~CTabView_Rup()
{
}

BEGIN_MESSAGE_MAP(CTabView_Rup, CTabView)
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGE_ACTIVE_TAB, OnChangeActiveTab)
END_MESSAGE_MAP()


// CTabView_Rup 诊断

#ifdef _DEBUG
void CTabView_Rup::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CTabView_Rup::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTabView_Rup 消息处理程序


LRESULT CTabView_Rup::OnChangeActiveTab(WPARAM wp, LPARAM lp)
{

	return LRESULT();
}

void CTabView_Rup::OnInitialUpdate()
{
	CTabView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	this->GetTabControl().ModifyTabStyle(CMFCTabCtrl::STYLE_3D_VS2005);
	this->GetTabControl().EnableTabSwap(FALSE);
	this->AddView(RUNTIME_CLASS(CView_Add), _T("添加"), 101);
	this->AddView(RUNTIME_CLASS(CView_Del), _T("删除"), 102);
	this->AddView(RUNTIME_CLASS(CView_Query), _T("查询"), 103);


	this->GetTabControl().SetLocation(CMFCTabCtrl::LOCATION_TOP);

}



void CTabView_Rup::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类

}
