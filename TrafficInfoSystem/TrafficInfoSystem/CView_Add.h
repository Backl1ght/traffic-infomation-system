#pragma once


// CView_Add 视图

class CView_Add : public CView
{
	DECLARE_DYNCREATE(CView_Add)

protected:
	CView_Add();           // 动态创建所使用的受保护的构造函数
	virtual ~CView_Add();

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
	afx_msg void OnDropDown();
	afx_msg void OnDropDown1();
	DECLARE_MESSAGE_MAP()
private:

	CButton m_btn_Add;
	CComboBox m_cbbox_NorE;	//Node or Edge
	CEdit m_Sedit_NorE;

	//Node
	CEdit m_Sedit_Name, m_Sedit_Code, m_Sedit_Intro, m_Sedit_X, m_Sedit_Y;
	CEdit m_edit_Name, m_edit_Code, m_edit_Intro, m_edit_X, m_edit_Y;

	//Edge
	CEdit m_Sedit_Length, m_Sedit_From, m_Sedit_To;
	CEdit m_edit_Length;
	CComboBox m_cbbox_From,m_cbbox_To;

public:
	virtual void OnInitialUpdate();
	void OnUpdate1();
};


