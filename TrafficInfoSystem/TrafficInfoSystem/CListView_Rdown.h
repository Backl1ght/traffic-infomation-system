#pragma once


// CListView_Rdown 视图

class CListView_Rdown : public CListView
{
	DECLARE_DYNCREATE(CListView_Rdown)

protected:
	CListView_Rdown();           // 动态创建所使用的受保护的构造函数
	virtual ~CListView_Rdown();

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
	virtual void OnInitialUpdate();

	void Listchange(int node_id);
	void Listchange(int from, int to);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEditKillFocus();

private:
	int iCol, iRow;
	CEdit* m_pEdit;
};


