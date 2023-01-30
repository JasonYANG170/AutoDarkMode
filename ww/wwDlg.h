
// wwDlg.h: 头文件
//

#pragma once
#define WM_SHOWTASK  WM_USER+100  

// CwwDlg 对话框
class CwwDlg : public CDialogEx
{
// 构造
public:
	CwwDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton PowerBootButton;
	afx_msg void OnBnClickedPowerboot();
	void ToTray();
protected:
	afx_msg
		void DeleteTray();
	LRESULT OnShowtask(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton10();
	void KMeansSegment();
	afx_msg void OnBnClickedButton7();
};
