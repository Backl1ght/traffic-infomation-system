#pragma once


// CView_Lup 视图

class CView_Lup : public CView
{
	DECLARE_DYNCREATE(CView_Lup)

protected:
	CView_Lup();           // 动态创建所使用的受保护的构造函数
	virtual ~CView_Lup();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

private:
	bool m_bLBtnDown;
	bool m_bDragged;

	int node_id;

public:
	void OnRepaint();
	void OnPaintSp(int to,int* path);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
};


