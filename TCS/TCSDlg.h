
// TCSDlg.h: 头文件
//

#pragma once
#include "Snake.h"


// CTCSDlg 对话框
class CTCSDlg : public CDialogEx
{
// 构造
public:
	CTCSDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TCS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
private:
	CPoint m_ptFood;
	Snake m_snake;
	int m_score;

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void CreateFood();
	void DrawFood();
	void StartGame();
	void DrawSnake();
	void SnakeMove();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
