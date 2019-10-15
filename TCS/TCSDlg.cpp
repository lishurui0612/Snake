
// TCSDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TCS.h"
#include "TCSDlg.h"
#include "afxdialogex.h"
#include "time.h"
//#include "Snake.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define LENGTH 20
#define SIZE_H 30
#define SIZE_V 30
double SPEED = 300;
int run = 1;

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


// CTCSDlg 对话框



CTCSDlg::CTCSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TCS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTCSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTCSDlg 消息处理程序

BOOL CTCSDlg::OnInitDialog()
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

	CRect window;
	CRect client;
	GetWindowRect(window);
	GetClientRect(client);
	int width = window.Width() - client.Width() + LENGTH * SIZE_H+LENGTH*10;
	int height = window.Height() - client.Height() + LENGTH * SIZE_V;
	MoveWindow(0, 0, width, height);
	StartGame();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTCSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTCSDlg::OnPaint()
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
		CClientDC dc(this);
		dc.Rectangle(0, 0, LENGTH * SIZE_H, LENGTH * SIZE_V);
		DrawSnake();
		DrawFood();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTCSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//生成食物
void CTCSDlg::CreateFood()
{
	srand(time(0));
	m_ptFood.x = rand() % (SIZE_H - 1) + 1;
	m_ptFood.y = rand() % (SIZE_V - 1) + 1;
	while (m_snake.IsInBody(m_ptFood))
	{
		m_ptFood.x = rand() % (SIZE_H - 1) + 1;
		m_ptFood.y = rand() % (SIZE_V - 1) + 1;
	}
}

void CTCSDlg::DrawFood()
{
	CClientDC dc(this);
	CBrush blue(RGB(0, 0, 255));
	dc.SelectObject(blue);
	dc.Rectangle(m_ptFood.x * LENGTH, m_ptFood.y * LENGTH, (m_ptFood.x + 1) * LENGTH, (m_ptFood.y + 1) * LENGTH);
}

void CTCSDlg::StartGame()
{
	CreateFood();
	SetTimer(1, SPEED, NULL);
}

void CTCSDlg::DrawSnake()
{
	CClientDC dc(this);
	CBrush black(RGB(0, 0, 0));
	CBrush red(RGB(255, 0, 0));
	dc.SelectObject(&black);
	CList<CPoint>* pBody = m_snake.GetBody();
	POSITION p = pBody->GetHeadPosition();
	CPoint point = pBody->GetNext(p);
	dc.Rectangle(point.x * LENGTH, point.y * LENGTH, (point.x + 1) * LENGTH, (point.y + 1) * LENGTH);
	dc.SelectObject(&red);
	while (p)
	{
		CPoint point = pBody->GetNext(p);
		dc.Rectangle(point.x * LENGTH, point.y * LENGTH, (point.x + 1) * LENGTH, (point.y + 1) * LENGTH);
	}
}

void CTCSDlg::SnakeMove()
{
	CClientDC dc(this);
	CPoint tail = m_snake.GetBody()->GetTail();
	CPoint head = m_snake.GetBody()->GetHead();
	CBrush red(RGB(255, 0, 0));
	CBrush black(RGB(0, 0, 0));
	dc.SelectObject(red);
	dc.Rectangle(head.x * LENGTH, head.y * LENGTH, (head.x + 1) * LENGTH, (head.y + 1) * LENGTH);
	if (m_snake.Move(m_ptFood))
	{
		head = m_snake.GetBody()->GetHead();
		CBrush* old = dc.SelectObject(&black);
		dc.Rectangle(head.x * LENGTH, head.y * LENGTH, (head.x + 1) * LENGTH, (head.y + 1) * LENGTH);
		dc.SelectObject(old);
		if (head == m_ptFood)
		{
			m_score += 10;
			CreateFood();
			DrawFood();
		}
		else
		{
			CBrush white1(RGB(255, 255, 255));
			CPen white(PS_SOLID, 1, RGB(255, 255, 255));
			dc.SelectObject(white);
			dc.Rectangle(tail.x * LENGTH, tail.y * LENGTH, (tail.x + 1) * LENGTH, (tail.y + 1) * LENGTH);
			dc.SelectObject(white1);
			dc.Rectangle(tail.x * LENGTH, tail.y * LENGTH, (tail.x + 1) * LENGTH, (tail.y + 1) * LENGTH);
		}
	}
	else
	{
		KillTimer(1);
		MessageBox(_T("游戏结束！"));
	}
}

void CTCSDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SnakeMove();
	CDialogEx::OnTimer(nIDEvent);
}

BOOL CTCSDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_UP:
			SetTimer(1, SPEED, NULL);
			m_snake.DirectionChange(CPoint(0, -1));
			break;
		case VK_DOWN:
			SetTimer(1, SPEED, NULL);
			m_snake.DirectionChange(CPoint(0, 1));
			break;
		case VK_LEFT:
			SetTimer(1, SPEED, NULL);
			m_snake.DirectionChange(CPoint(-1, 0));
			break;
		case VK_RIGHT:
			SetTimer(1, SPEED, NULL);
			m_snake.DirectionChange(CPoint(1, 0));
			break;
		case VK_F2:
			SPEED = SPEED * 0.8;
			SetTimer(1, SPEED, NULL);
			break;
		case VK_F3:
			SPEED = SPEED * 1.25;
			SetTimer(1, SPEED, NULL);
			break;
		case VK_SPACE:
			run = run ^ 1;
			if (run == 1)
				SetTimer(1, SPEED, NULL);
			else 
				KillTimer(1);
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
