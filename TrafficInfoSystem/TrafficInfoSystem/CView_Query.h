#pragma once


// CView_Query 视图

class CView_Query : public CView
{
	DECLARE_DYNCREATE(CView_Query)

protected:
	CView_Query();           // 动态创建所使用的受保护的构造函数
	virtual ~CView_Query();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	afx_msg void OnButtonClick();
	afx_msg void OnCbnSelchange();
	afx_msg void OnCbnEditchange();
	afx_msg void OnCbnSelchange1();
	afx_msg void OnDropdown();
	afx_msg void OnDropdown1();
	afx_msg void OnDropdown2();
	DECLARE_MESSAGE_MAP()

private:
	CButton m_btn_Qry;
	CComboBox m_cbbox_Choose;
	CEdit m_Sedit_Choose;


	//Node
	CEdit m_Sedit_Name, m_Sedit_Code, m_Sedit_Intro, m_Sedit_X, m_Sedit_Y;
	CEdit m_edit_Code, m_edit_Intro, m_edit_X, m_edit_Y;
	CComboBox m_cbbox_Name;

	//SP
	CEdit m_Sedit_From, m_Sedit_To;
	CComboBox m_cbbox_From, m_cbbox_To;
public:
	virtual void OnInitialUpdate();
	void ChangeView(int i);
};


