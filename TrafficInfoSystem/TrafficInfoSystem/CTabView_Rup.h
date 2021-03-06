#pragma once



// CTabView_Rup 视图

class CTabView_Rup : public CTabView
{
	DECLARE_DYNCREATE(CTabView_Rup)

protected:
	CTabView_Rup();           // 动态创建所使用的受保护的构造函数
	virtual ~CTabView_Rup();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	afx_msg LRESULT OnChangeActiveTab(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};


