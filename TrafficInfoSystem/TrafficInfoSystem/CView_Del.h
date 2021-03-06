#pragma once


// CView_Del 视图

class CView_Del : public CView
{
	DECLARE_DYNCREATE(CView_Del)

protected:
	CView_Del();           // 动态创建所使用的受保护的构造函数
	virtual ~CView_Del();

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
	afx_msg void OnDropDown2();
	afx_msg void OnDropDown3();
	afx_msg void OnCbnSelchangeName();
	afx_msg void OnCbnSelchangePath();
	DECLARE_MESSAGE_MAP()
private:
	CButton m_btn_Del;
	CComboBox m_cbbox_NorE;	//Node or Edge
	CEdit m_Sedit_NorE;

	//Node
	CEdit m_Sedit_Name, m_Sedit_Code, m_Sedit_Intro, m_Sedit_X, m_Sedit_Y;
	CEdit m_edit_Code, m_edit_Intro, m_edit_X, m_edit_Y;
	CComboBox m_cbbox_Name;

	//Edge
	CEdit m_Sedit_Length, m_Sedit_From, m_Sedit_To, m_Sedit_Path;
	CEdit m_edit_Length;
	CComboBox m_cbbox_From, m_cbbox_To,m_cbbox_Path;
public:
	virtual void OnInitialUpdate();
};


