
// TrafficInfoSystem.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "TrafficInfoSystem.h"
#include "MainFrm.h"

#include "TrafficInfoSystemDoc.h"
#include "TrafficInfoSystemView.h"

#include "CView_Add.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrafficInfoSystemApp

BEGIN_MESSAGE_MAP(CTrafficInfoSystemApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CTrafficInfoSystemApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_OPEN, &CTrafficInfoSystemApp::OnFileOpen)
END_MESSAGE_MAP()


// CTrafficInfoSystemApp 构造

CTrafficInfoSystemApp::CTrafficInfoSystemApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("TrafficInfoSystem.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的 CTrafficInfoSystemApp 对象

CTrafficInfoSystemApp theApp;


// CTrafficInfoSystemApp 初始化

BOOL CTrafficInfoSystemApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTrafficInfoSystemDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CTrafficInfoSystemView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	//TODO:删除
	G.AddNode("长沙", "CS", "长沙的简介", 100, 150);
	G.AddNode("株洲", "ZZ", "株洲的简介", 100, 250);
	G.AddNode("湘潭", "XT", "湘潭的简介", 200, 50);
	G.AddNode("衡阳", "HY", "衡阳的简介", 200, 350);
	G.AddNode("邵阳", "SY", "邵阳的简介", 300, 50);
	G.AddNode("岳阳", "YY", "岳阳的简介", 300, 350);
	G.AddNode("常德", "CD", "常德的简介", 400, 150);
	G.AddNode("张家界", "ZJJ", "张家界的简介", 400, 250);

	G.AddEdge("长沙","株洲",4,"长株");
	G.AddEdge("长沙", "湘潭", 5, "长湘");
	G.AddEdge("长沙", "衡阳", 2, "长衡");
	G.AddEdge("长沙", "岳阳", 8, "长岳");
	G.AddEdge("长沙", "邵阳", 3, "长邵");
	G.AddEdge("长沙", "张家界", 1, "长张");
	G.AddEdge("株洲", "衡阳", 10, "株衡");
	G.AddEdge("邵阳", "常德", 7, "邵常");
	G.AddEdge("张家界", "株洲", 6, "张株");
	G.AddEdge("张家界", "衡阳", 8, "张衡");
	G.AddEdge("张家界", "常德", 8, "张常");

	//画板重绘
	CMainFrame* m_pHost = (CMainFrame*)AfxGetMainWnd();
	m_pHost->rePaintLup();

	return TRUE;
}

int CTrafficInfoSystemApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CTrafficInfoSystemApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CTrafficInfoSystemApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CTrafficInfoSystemApp 消息处理程序






