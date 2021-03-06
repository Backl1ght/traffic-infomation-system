#pragma once


// CEditView_Ldown 视图

class CEditView_Ldown : public CEditView
{
	DECLARE_DYNCREATE(CEditView_Ldown)

protected:
	CEditView_Ldown();           // 动态创建所使用的受保护的构造函数
	virtual ~CEditView_Ldown();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	void Editchange();
	void Editchange(string src);
	void Editchange(string from, string to);
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


