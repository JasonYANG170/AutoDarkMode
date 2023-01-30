
// wwDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ww.h"
#include "wwDlg.h"
#include "afxdialogex.h"
#include <afxpriv.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
int num;
int num2;
int open;
UINT ThreadFunc(LPVOID lpParam);
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


// CwwDlg 对话框



CwwDlg::CwwDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CwwDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_POWERBOOT, PowerBootButton);
}

BEGIN_MESSAGE_MAP(CwwDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_POWERBOOT, &CwwDlg::OnBnClickedPowerboot)
	ON_MESSAGE(WM_SHOWTASK, &CwwDlg::OnShowtask)
	ON_BN_CLICKED(IDC_BUTTON2, &CwwDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CwwDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CwwDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CwwDlg::OnBnClickedButton4)

	ON_BN_CLICKED(IDC_BUTTON9, &CwwDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON5, &CwwDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CwwDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON10, &CwwDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON7, &CwwDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CwwDlg 消息处理程序

BOOL CwwDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	{HKEY hKey;
	//找到系统的启动项
	CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	//打开启动项
	long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);
	if (lRet != ERROR_SUCCESS)
		MessageBox(_T("打开启动项失败"));
	//找到程序自身路径
	TCHAR pFileName[MAX_PATH] = {};
	GetModuleFileName(NULL, pFileName, MAX_PATH);
	//判断是否已经设置开机启动
	TCHAR PowerBoot[MAX_PATH] = {};
	DWORD nLongth = MAX_PATH;
	long result = RegGetValue(hKey, NULL, _T("PowerBoot"), RRF_RT_REG_SZ, 0, PowerBoot, &nLongth);
	if (result == ERROR_SUCCESS)
	{
		PowerBootButton.SetWindowText(_T("自启状态"));
	}
	else
		PowerBootButton.SetWindowText(_T("未自启状态"));
	//关闭注册表
	RegCloseKey(hKey);
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CwwDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma comment( linker, "/subsystem:/"windows/" /entry:/"mainCRTStartup/"" ) // 设置入口地址  
#include   <windows.h>     
#include   <stdio.h>     

//#define   COMMENDLINE   "REG ADD HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize /v AppsUseLightTheme /t REG_DWORD /d 0 /f&REG ADD HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize /v SystemUsesLightTheme /t REG_DWORD /d 0 /f"

//调用命令行命令而不显示命令行窗口  
BOOL system_hide(char* CommandLine)
{
	SECURITY_ATTRIBUTES   sa;
	HANDLE   hRead, hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return   FALSE;
	}

	STARTUPINFO   si;
	PROCESS_INFORMATION   pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//关键步骤，CreateProcess函数参数意义请查阅MSDN     
	if (!CreateProcess(NULL, CommandLine, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		return   FALSE;
	}
	CloseHandle(hWrite);

	char   buffer[4096] = { 0 };
	DWORD   bytesRead;
	while (true)
	{
		memset(buffer, 0, strlen(buffer));
		if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL)
			break;
		//buffer中就是执行的结果，可以保存到文本，也可以直接输出     
		//printf(buffer);//这行注释掉就可以了     
		Sleep(100);
	}
	return   TRUE;
}

void CwwDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	

	


	AfxBeginThread(ThreadFunc, (LPVOID)this);//启动新的线程

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CwwDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CwwDlg::OnBnClickedPowerboot()
{
	// TODO: 在此添加控件通知处理程序代码
	HKEY hKey;
	//找到系统的启动项
	CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	//打开启动项
	long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);
	if (lRet != ERROR_SUCCESS)
		MessageBox(_T("打开启动项失败"));
	//找到程序自身路径
	TCHAR pFileName[MAX_PATH] = {};
	GetModuleFileName(NULL, pFileName, MAX_PATH);
	//判断是否已经设置开机启动
	TCHAR PowerBoot[MAX_PATH] = {};
	DWORD nLongth = MAX_PATH;
	long result = RegGetValue(hKey, NULL, _T("PowerBoot"), RRF_RT_REG_SZ, 0, PowerBoot, &nLongth);
	if (result == ERROR_SUCCESS)
	{
		//自启状态;
		//取消自动启动
		lRet = RegDeleteValue(hKey, _T("PowerBoot"));
		if (lRet == ERROR_SUCCESS)
		{
			MessageBox(_T("关闭自启成功"));
			PowerBootButton.SetWindowText(_T("未自启状态"));
		}
	}
	else
	{
		//未自启状态
		//设置自启
		lRet = RegSetValueEx(hKey, _T("PowerBoot"), 0, REG_SZ, (LPBYTE)pFileName, (lstrlen(pFileName) + 1) * sizeof(TCHAR));
		if (lRet == ERROR_SUCCESS)
		{
			MessageBox(_T("设置自启成功"));
			PowerBootButton.SetWindowText(_T("自启状态"));
		}
	}
	//关闭注册表
	RegCloseKey(hKey);

}
#define TOOLTIPS_NAME_	"XXXX"
//最小化到托盘函数
void CwwDlg::ToTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;//自定义的消息名称
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy_s(nid.szTip, _T(TOOLTIPS_NAME_)); //信息提示条
	Shell_NotifyIcon(NIM_ADD, &nid); //在托盘区添加图标
	ShowWindow(SW_HIDE); //隐藏主窗口
}

//删除托盘图标函数
void CwwDlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK; //自定义的消息名称
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy_s(nid.szTip, _T(TOOLTIPS_NAME_)); //信息提示条为“计划任务提醒”
	Shell_NotifyIcon(NIM_DELETE, &nid); //在托盘区删除图标
}

afx_msg LRESULT CwwDlg::OnShowtask(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”
	{
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);//得到鼠标位置
		CMenu menu;
		menu.CreatePopupMenu();//声明一个弹出式菜单
		menu.AppendMenu(MF_STRING, WM_DESTROY, "YANG Auto Dark Mode");
		menu.AppendMenu(MF_STRING, WM_DESTROY, "程序正在后台运行中<双击图标打开>");
		menu.AppendMenu(MF_STRING, WM_DESTROY, _T("退出程序"));
		//增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已隐藏），将程序结束。
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this); //确定弹出式菜单的位置
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu(); //资源回收
		delete lpoint;
	} break;
	case WM_LBUTTONDBLCLK: //双击左键的处理
	{
		this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿
		DeleteTray();
	} break;
	default: break;
	}

	return 0;
}


void CwwDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	ToTray();
	MessageBox("程序已在系统托盘中后台运行，双击托盘中的程序打开，右键则退出", NULL, MB_OK);
}


void CwwDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tonken1 = "";
	GetDlgItem(IDC_EDIT1)->GetWindowTextA(tonken1);
	num = _ttoi(tonken1);
	CString tonken2 = "";
	GetDlgItem(IDC_EDIT2)->GetWindowTextA(tonken2);
	num2 = _ttoi(tonken2);
	MessageBox("设定成功，请在程序设置中<开启定时>即可定时切换。", NULL, MB_OK);
	//HMODULE module = GetModuleHandle(0);
	//char pFileName[MAX_PATH] = { 0 };
	//GetModuleFileName(module, pFileName, MAX_PATH);
	//CString csFullName(pFileName);
//	CString cstrStr = csFullName + "\\data";
	

	//char* chStr;

	//chStr = (char*)cstrStr.GetBuffer(0);
	//char * pFileName = W2A(cstr); //也可实现转换

	//注意：有时候可能还需要添加引用#include <afxpriv.h>
	//char* pszFileName = chStr;
	char* pszFileName = "D:\\data";
	CStdioFile myFile;

	CFileException fileException;

	if (myFile.Open(pszFileName, CFile::typeText | CFile::modeCreate | CFile::modeReadWrite), &fileException)

	{

		//myFile.WriteString(tonken1);

	//	myFile.WriteString(tonken2);

	}

	else

	{

		TRACE("Can't open file %s,error=%u\n", pszFileName, fileException.m_cause);

	}
	
}


void CwwDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	system_hide("REG ADD HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize /v AppsUseLightTheme /t REG_DWORD /d 1 /f");

	system_hide("REG ADD HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize /v SystemUsesLightTheme /t REG_DWORD /d 1 /f");
	MessageBox("已变更浅色模式", NULL, MB_OK);
}


void CwwDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	system_hide("REG ADD HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize /v AppsUseLightTheme /t REG_DWORD /d 0 /f");

	system_hide("REG ADD HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize /v SystemUsesLightTheme /t REG_DWORD /d 0 /f");
	MessageBox("已变更深色模式", NULL, MB_OK);
}


void CwwDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	open = 1;
	MessageBox("已开启", NULL, MB_OK);
}


void CwwDlg::OnBnClickedButton9()
{


	char* pszFileName = "C:\\Users\\qw200\\Documents\\data";

	CStdioFile myFile;

	CFileException fileException;

	if (myFile.Open(pszFileName, CFile::typeText | CFile::modeCreate | CFile::modeReadWrite), &fileException)

	{

		myFile.WriteString("第1行\n");

		CString strOrder;

		strOrder.Format("%d,%.3f", 66, 88.88);

		myFile.WriteString(strOrder);

	}

	else

	{

		TRACE("Can't open file %s,error=%u\n", pszFileName, fileException.m_cause);

	}
}


void CwwDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CwwDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox("点击确定跳转更新，请在网站<Releases>区域下载更新", NULL, MB_OK);
	system("start https://github.com/JasonYANG170/Auto-Dark-Mode");
	
}


void CwwDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	open = 1;
	MessageBox("已开启", NULL, MB_OK);

//	AfxBeginThread(ThreadFunc, (LPVOID)this);//启动新的线程
}
UINT  ThreadFunc(LPVOID  lParam)
{
	while (true) {
		for (open; open == 1; open + 0)
		{
			CTime tm; tm = CTime::GetCurrentTime();
			int hour = tm.GetHour();
			CString tempPort;
			tempPort.Format(_T("%d"), hour);
			if (hour == num) {
					system_hide("REG ADD HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize /v AppsUseLightTheme /t REG_DWORD /d 0 /f");

	system_hide("REG ADD HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize /v SystemUsesLightTheme /t REG_DWORD /d 0 /f");
		
			}
			else if (hour == num2)
			{
					system_hide("REG ADD HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize /v AppsUseLightTheme /t REG_DWORD /d 1 /f");

	system_hide("REG ADD HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize /v SystemUsesLightTheme /t REG_DWORD /d 1 /f");
	
			}

		}
		Sleep(1000);
	}
}


void CwwDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	open = 0;
	MessageBox("已关闭", NULL, MB_OK);
}
