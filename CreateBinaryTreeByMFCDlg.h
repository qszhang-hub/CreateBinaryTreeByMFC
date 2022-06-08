
// CreateBinaryTreeByMFCDlg.h: 头文件
//

#pragma once
#include "BinaryTree.h"
#include <queue>

// CCreateBinaryTreeByMFCDlg 对话框
class CCreateBinaryTreeByMFCDlg : public CDialogEx
{
// 构造
public:
	CCreateBinaryTreeByMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATEBINARYTREEBYMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	BinaryTree<char> Bin;
	BinTNode<char>* pRoot = Bin.GetRoot();
	int Height = 0;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_ctrlseq1;
	CEdit m_ctrlseq2;
	CEdit m_ctrlseq3;
	CEdit m_ctrlseq4;
	CString m_csseq1;
	CString m_csseq2;
	CString m_csseq3;
	CString m_csseq4;
	int m_type = 0;
	void PrintBinaryTree(CDC* pDC, BinTNode<char>* tree);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedButton2();
	bool Compare(char* p1, char* p2,int n);//比较两个字符串中的元素，如果它们里面的元素不相同就弹窗。
	bool CompareSeq1(char* p1, char* p2,int n);
	bool CompareSeq2(char* p1, char* p2, int n);
	afx_msg void OnBnClickedButton3();
	void AdjustBinaryTree();//节省空间的二叉树节点调整算法
	void AdjustBinaryTree(BinTNode<char>* p);//按照满二叉树的格式的节点调整算法
	afx_msg void OnBnClickedButton4();
	CEdit m_ctrlseq5;
	CString m_csseq5;
};
