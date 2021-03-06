
// TrafficInfoSystem.h: TrafficInfoSystem 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

#include "Graph.h"
#include<string>
#define R theApp.node_r
using namespace std;


// CTrafficInfoSystemApp:
// 有关此类的实现，请参阅 TrafficInfoSystem.cpp
//

class CTrafficInfoSystemApp : public CWinApp
{
public:
	CTrafficInfoSystemApp();
	Graph G;
	static const int node_r = 15;

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTrafficInfoSystemApp theApp;
