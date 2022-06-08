
// CreateBinaryTreeByMFCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CreateBinaryTreeByMFC.h"
#include "CreateBinaryTreeByMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CCreateBinaryTreeByMFCDlg 对话框



CCreateBinaryTreeByMFCDlg::CCreateBinaryTreeByMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CREATEBINARYTREEBYMFC_DIALOG, pParent)
	, m_csseq1(_T(""))
	, m_csseq2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreateBinaryTreeByMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ctrlseq1);
	DDX_Control(pDX, IDC_EDIT2, m_ctrlseq2);
	DDX_Control(pDX, IDC_EDIT3, m_ctrlseq3);
	DDX_Control(pDX, IDC_EDIT4, m_ctrlseq4);
	DDX_Control(pDX, IDC_EDIT5, m_ctrlseq5);
}

BEGIN_MESSAGE_MAP(CCreateBinaryTreeByMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCreateBinaryTreeByMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CCreateBinaryTreeByMFCDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CCreateBinaryTreeByMFCDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON2, &CCreateBinaryTreeByMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCreateBinaryTreeByMFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCreateBinaryTreeByMFCDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CCreateBinaryTreeByMFCDlg 消息处理程序

BOOL CCreateBinaryTreeByMFCDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCreateBinaryTreeByMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCreateBinaryTreeByMFCDlg::OnPaint()
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
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCreateBinaryTreeByMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCreateBinaryTreeByMFCDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//在消息队列中发送WM_PAINT，使得函数自动调用ondraw（）函数绘图
	//它是在该语句处就被调用了，已经发送了WM_PAINT，但是该消息优先级不高，在消息队列末尾
	//从而若只用该语句会发生函数已经执行完了才刷新，因为执行完了才轮到WM_PAINT，很突兀
	Invalidate();
	//该语句的作用是立即使WM_PAINT消息执行，跳过消息队列。配合上一语句从而达到立即刷新
	UpdateWindow();
	//删除原来的树，达到重新建树，重新绘图的目的。
	Bin.DestroyTree(pRoot);
	m_ctrlseq1.GetWindowTextW(m_csseq1);
	m_ctrlseq2.GetWindowTextW(m_csseq2);
	//声明标识
	USES_CONVERSION;
	//函数T2A和W2A均支持ATL和MFC中的字符
	char* list1 = T2A(m_csseq1);
	char* list2 = T2A(m_csseq2);
	//char * pFileName = W2A(cstr); //也可实现转换
	//注意：有时候可能还需要添加引用#include <afxpriv.h>
	BinTNode<char>* p2 = NULL;
	int n = strlen(list1);
	CRect rect;
	CWnd* pWin = GetDlgItem(IDC_STATIC);
	pWin->GetClientRect(rect);
	int x = rect.Width();			
	int y = rect.Height();	
	CDC* pDC = pWin->GetDC();
	CPen pen(PS_SOLID, 3, RGB(255, 0, 0));
	pDC->SelectObject(&pen);
	switch (m_type)
	{
	case 1:	Bin.CreateBinTree1(pRoot, p2, list1, list2, n, x / 2, 25); break;
	case 2: Bin.CreateBinTree2(pRoot, p2, list1, list2, n, x / 2, 25); break;
	default:AfxMessageBox(_T("请先选择构造方式！")); return;
	}
	Height = Bin.Height(pRoot);//如果按照节省空间的节点位置调整算法，可以不用求树高
	//以下两种算法都可以使用！打星号不代表它是没用的！
	//AdjustBinaryTree(pRoot);//按照满二叉树的节点位置调整算法
	AdjustBinaryTree();//按照节省空间的二叉树节点位置调整算法
	PrintBinaryTree(pDC, pRoot);
}


void CCreateBinaryTreeByMFCDlg::PrintBinaryTree(CDC* pDC, BinTNode<char>* tree)
{	// TODO: 在此处添加实现代码.
	if (tree == NULL) return;
	pDC->Ellipse(tree->point.x - 25, tree->point.y - 25, tree->point.x + 25, tree->point.y + 25);
	Sleep(200);
	CString str;
	str.Format(_T("%c"), tree->data);
	pDC->TextOutW(tree->point.x, tree->point.y, str);
	Sleep(200);
	if (tree->lchild != NULL)
	{
		PrintBinaryTree(pDC, tree->lchild);
		Sleep(200);
		pDC->MoveTo(tree->point.x, tree->point.y);
		pDC->LineTo(tree->lchild->point.x, tree->lchild->point.y);
	}
	if (tree->rchild != NULL)
	{
		PrintBinaryTree(pDC, tree->rchild);
		Sleep(200);
		pDC->MoveTo(tree->point.x, tree->point.y);
		pDC->LineTo(tree->rchild->point.x, tree->rchild->point.y);
	}
}


void CCreateBinaryTreeByMFCDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_type = 1;
}


void CCreateBinaryTreeByMFCDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_type = 2;
}


void CCreateBinaryTreeByMFCDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrlseq1.GetWindowTextW(m_csseq1);
	m_ctrlseq2.GetWindowTextW(m_csseq2);
	//比较两个字符串长度
	if (m_csseq1.GetLength() != m_csseq2.GetLength())
	{
		AfxMessageBox(_T("序列输入错误！"));
		return;
	}
	//CString转char*
	USES_CONVERSION;
	//函数T2A和W2A均支持ATL和MFC中的字符
	char* p1 = T2A(m_csseq1);
	char* p2 = T2A(m_csseq2);
	int i = 0;
	switch (m_type)
	{
	case 1:i = CompareSeq1(p1, p2, strlen(p1)); break;
	case 2:i = CompareSeq2(p1, p2, strlen(p1)); break;
	default:AfxMessageBox(_T("请先选择构造方式！"));
	}
	if (i) AfxMessageBox(_T("输入序列无误"));
}

bool CCreateBinaryTreeByMFCDlg::Compare(char* p1, char* p2,int n)
{
	char ch,ch1;
	for (int i = 0; i < n; i++)
	{
		ch = p1[i];
		ch1 = p2[n];
		p2[n] = '\0';
		if (strchr(p2, ch) == NULL)
		{
			AfxMessageBox(_T("序列输入错误！"));
			return 0;	//出错返回0
		}
		p2[n] = ch1;
	}
	for (int i = 0; i < n; i++)
	{
		ch = p2[i];
		ch1 = p1[n];
		p1[n] = '\0';
		if (strchr(p1, ch) == NULL)
		{
			AfxMessageBox(_T("序列输入错误！"));
			return 0;	//出错返回0
		}
		p1[n] = ch1;
	}
	return 1;	//无误就返回1
}

bool CCreateBinaryTreeByMFCDlg::CompareSeq1(char* p1, char* p2, int n)
{
	if (n <= 0) return 1;
	int i = 0;
	char tmp = p1[0];//根节点
	if (Compare(p1, p2,n))
	{
		int m = 0;
		for (; m < n; m++)
		{
			if (tmp == p2[m])
				break;
		}
		i = CompareSeq1(p1 + 1, p2, m);
		if (i)
		{
			i = CompareSeq1(p1 + m + 1, p2 + m + 1, n - m - 1);
			if (i) return 1;
			else return 0;
		}
		else return 0;
	}
	else return 0;
}

bool CCreateBinaryTreeByMFCDlg::CompareSeq2(char* p1, char* p2, int n)
{
	if (n <= 0) return 1;
	int i = 0;
	char tmp = p2[n - 1];//根节点
	if (Compare(p1, p2, n))
	{
		int m = 0;
		for (; m < n; m++)
		{
			if (tmp == p1[m])
				break;
		}
		i = CompareSeq2(p1, p2, m);
		if (i)
		{
			i = CompareSeq2(p1 + m + 1, p2 + m, n - m - 1);
			if (i) return 1;
			else return 0;
		}
		else return 0;
	}
	else return 0;
}


void CCreateBinaryTreeByMFCDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrlseq3.GetWindowTextW(m_csseq3);
	//m_ctrlseq4.GetWindowTextW(m_csseq4);
	//CString转char*
	USES_CONVERSION;
	//函数T2A和W2A均支持ATL和MFC中的字符
	char* p3 = T2A(m_csseq3);
	char ch = *p3;
	if (ch == pRoot->data)
	{
		AfxMessageBox(_T("根节点无父节点！"));
		return;
	}
	BinTNode<char>* pParent = NULL;
	pParent = Bin.SearchParentNode(pRoot, ch);
	if (pParent == NULL)
	{
		AfxMessageBox(_T("不存在该节点！"));
		return;
	}
	char parentdata = pParent->data;
	m_csseq4.Format(_T("%c"), parentdata);
	m_ctrlseq4.SetWindowTextW(m_csseq4);
}

void CCreateBinaryTreeByMFCDlg::AdjustBinaryTree()//节省空间的调整位置法
{
	queue<BinTNode<char>*> q;
	vector<vector<BinTNode<char>*>> vec;//储存所有节点的vector容器，其中每个vector指向一层的节点
	vector<BinTNode<char>*> tmp;//用来临时存储每一层节点的vector容器
	//p1、p2用来存储两个发生冲突的节点的父节点
	BinTNode<char>* p = pRoot, * p1 = NULL, * p2 = NULL;
	int CurVec = 0;			//当前vector容器的层数
	int IsAdjusted = 0;		//节点位置是否有冲突的标识，初始值为0，表示还未发现节点位置有冲突
	q.push(p);	//根节点入队
	while (!q.empty())
	{
		p = q.front();
		q.pop();
		if (vec.size() == 0)//针对根节点
		{
			tmp.push_back(p);//根节点入临时容器
			vec.push_back(tmp);//根节点层入总容器
		}
		else
		{
			if (p->point.y == tmp.front()->point.y) tmp.push_back(p);
			else
			{
				if (CurVec == 0)//针对根节点
				{
					CurVec++;//进入下一层
					tmp.clear();//临时容器清空
					tmp.push_back(p);//下一层首元素进入临时容器
				}
				else//当一层元素已经全部入队
				{
					//i不从CurVec开始的原因：由于我们是先填满一层再将这一层加入vector中
					//因此每次判断时，我们判断的是CurVec-1层的冲突情况
					//所以，i从CurVec-1开始
					for (int i = CurVec-1 ; i >= 0; i--)//i为层数
					{
						do		//无论有无冲突，先检测一次
						{
							IsAdjusted = 0;	//每次检测前，冲突标识都为0
							for (int j = 0; j < vec[i].size() - 1; j++)//j代表第i层第j个节点
							{
								//如果发生冲突
								while (vec[i][j]->point.x + 25 >= vec[i][j + 1]->point.x - 25)
								{
									IsAdjusted = 1;		//一旦发现冲突就修改标识为1
									p1 = vec[i][j]->parent;
									p2 = vec[i][j + 1]->parent;
									while (p1 != p2)//找到两个冲突节点的共同父节点
									{
										p1 = p1->parent;
										p2 = p2->parent;
									}
									//从共同父节点的左右子树开始调整
									Bin.AdjustTree(p1->lchild, 1);
									Bin.AdjustTree(p1->rchild, 0);
								}
							}
						} while (IsAdjusted == 1);	//只有一层中不再出现冲突，才跳出循环
					}//保证从该层往上都没冲突后开始下一层元素入队
					CurVec++;//层数+1
					vec.push_back(tmp);//这一层无误，将其元素放入vec中
					tmp.clear();//临时的层vector容器清空
					tmp.push_back(p);//放入下一层首元素
				}
			}
		}
		if (p->lchild != NULL) q.push(p->lchild);
		if (p->rchild != NULL) q.push(p->rchild);
	}
	//全部遍历过了，还剩最后一层没处理，如果最后一层只有一个元素就不用处理
	vec.push_back(tmp);//最后一层入vector
	//注意这里，本来还应该是从CurVec-1，但是由于我们是先填满一层，才把这一层装进去
	//导致了，最后一层进入时，其前一层还未进行冲突判断，因此CurVec-1是指前一层
	//而CurVec指的是最后一层，因为不会再有CurVec+1层了，所以CurVec这一层以后无法判断
	//因此i从CurVec开始，让它顺带直接判断最后一层
	for (int i = CurVec ; i >= 0; i--)//i为层数
	{
		do		//无论有无冲突，先检测一次
		{
			IsAdjusted = 0;	//每次检测前，冲突标识都为0
			for (int j = 0; j < vec[i].size() - 1; j++)//j代表第i层第j个节点
			{
				//如果发生冲突
				while (vec[i][j]->point.x + 25 >= vec[i][j + 1]->point.x - 25)
				{
					IsAdjusted = 1;		//一旦发现冲突就修改标识为1
					p1 = vec[i][j]->parent;
					p2 = vec[i][j + 1]->parent;
					while (p1 != p2)//找到两个冲突节点的共同父节点
					{
						p1 = p1->parent;
						p2 = p2->parent;
					}
					//从共同父节点的左右子树开始调整
					Bin.AdjustTree(p1->lchild, 1);
					Bin.AdjustTree(p1->rchild, 0);				}
			}
		} while (IsAdjusted == 1);	//只有一层中不再出现冲突，才跳出循环
	}
}


void CCreateBinaryTreeByMFCDlg::AdjustBinaryTree(BinTNode<char>* p)//按照满二叉树的调整位置法
{
	int layer = p->point.y / 100 + 1;   //当前层数就是纵坐标/100+1
	if (p->lchild != NULL)
	{
		p->lchild->point.x = p->point.x - (int)pow(2, Height - layer) * 25;
		AdjustBinaryTree(p->lchild);
	}
	if (p->rchild != NULL)
	{
		p->rchild->point.x = p->point.x + (int)pow(2, Height - layer) * 25;
		AdjustBinaryTree(p->rchild);
	}
}


void CCreateBinaryTreeByMFCDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrlseq3.GetWindowTextW(m_csseq3);
	m_ctrlseq5.GetWindowTextW(m_csseq5);
	//CString转char*
	USES_CONVERSION;
	//函数T2A和W2A均支持ATL和MFC中的字符
	char* p3 = T2A(m_csseq3);
	char* p5 = T2A(m_csseq5);
	//两个子节点的值
	char ch3 = *p3, ch5 = *p5;
	if (ch3 == pRoot->data || ch5 == pRoot->data)
	{
		AfxMessageBox(_T("含有根节点！"));
		return;
	}
	BinTNode<char>* pParent3 = NULL, * pParent5 = NULL;
	pParent3 = Bin.SearchParentNode(pRoot, ch3);
	pParent5 = Bin.SearchParentNode(pRoot, ch5);
	if (pParent3 == NULL || pParent5 == NULL)
	{
		AfxMessageBox(_T("含有不存在的节点！"));
		return;
	}
	while (pParent3->point.y != pParent5->point.y)
	{
		if (pParent3->point.y < pParent5->point.y)
		{
			pParent5 = Bin.SearchParentNode(pRoot, pParent5->data);
		}
		if (pParent3->point.y > pParent5->point.y)
		{
			pParent3 = Bin.SearchParentNode(pRoot, pParent3->data);
		}
	}
	while (pParent3->data != pParent5->data)
	{
		pParent3 = Bin.SearchParentNode(pRoot, pParent3->data);
		pParent5 = Bin.SearchParentNode(pRoot, pParent5->data);
	}
	char parentdata = pParent3->data;
	m_csseq4.Format(_T("%c"), parentdata);
	m_ctrlseq4.SetWindowTextW(m_csseq4);
}
