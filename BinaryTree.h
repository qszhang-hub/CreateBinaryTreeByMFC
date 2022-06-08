#pragma once
#include<iostream>
using namespace std;
template <class T>
struct BinTNode
{
	T data;
	CPoint point;
	BinTNode<T>* lchild, * rchild, * parent;
	BinTNode() :lchild(NULL), rchild(NULL), parent(NULL) {}
	BinTNode(T x, BinTNode<T>* l = NULL, BinTNode<T>* r = NULL)
		:data(x), lchild(l), rchild(r), parent(NULL) {}
};

template <class T>
class BinaryTree
{
protected:
	BinTNode<T>* root;
public:
	BinaryTree() :root(NULL) {}
	~BinaryTree() { DestroyTree(root); }
	BinTNode<T>* GetRoot() { return root; }//取得根节点的地址
	void DestroyTree(BinTNode<T>* tree);	//删除一颗树
	void CreateBinTree1(BinTNode<T>*& tree1, BinTNode<T>*& tree2, char* pre, char* in, int n, long x, long y);//根据前序+中序建立二叉树
	void CreateBinTree2(BinTNode<T>*& tree1, BinTNode<T>*& tree2, char* in, char* post, int n, long x, long y);//根据中序+后序建立二叉树
	BinTNode<T>* GetParent(BinTNode<T>* tree) { return tree->parent; }
	BinTNode<T>* SearchNode(BinTNode<T>* &tree, T data);
	BinTNode<T>* SearchParentNode(BinTNode<T>*& tree, T data);
	void AdjustTree(BinTNode<T>* tree, int op);
	int Height(BinTNode<T>* tree);//求树高
};

template <class T>
void BinaryTree<T>::DestroyTree(BinTNode<T>* tree)
{
	if (tree != NULL)
	{
		DestroyTree(tree->lchild);
		DestroyTree(tree->rchild);
		delete tree;
	}
}

template <class T>
void BinaryTree<T>::CreateBinTree1(BinTNode<T>*& tree1, BinTNode<T>*& tree2, char* pre, char* in, int n, long x, long y)
{
	if (n <= 0) return;
	T tmp = *pre;
	tree1 = new BinTNode<T>(tmp);
	tree1->parent = tree2;
	tree1->point.x = x;
	tree1->point.y = y;
	int m = 0;
	for (; m < n; m++)
	{
		if (tmp == in[m])
			break;
	}
	CreateBinTree1(tree1->lchild, tree1, pre + 1, in, m, x - 50, y + 100);
	CreateBinTree1(tree1->rchild, tree1, pre + m + 1, in + m + 1, n - m - 1, x + 50, y + 100);
}


template <class T>
void BinaryTree<T>::CreateBinTree2(BinTNode<T>*& tree1, BinTNode<T>*& tree2, char* in, char* post, int n, long x, long y)
{
	if (n <= 0) return;
	T tmp = post[n - 1];
	tree1 = new BinTNode<T>(tmp);
	root = tree1;
	tree1->parent = tree2;
	tree1->point.x = x;
	tree1->point.y = y;
	int m = 0;
	for (; m < n; m++)
	{
		if (tmp == in[m])
			break;
	}
	CreateBinTree2(tree1->lchild, tree1, in, post, m, x - 50, y + 100);
	CreateBinTree2(tree1->rchild, tree1, in + m + 1, post + m, n - m - 1, x + 50, y + 100);
}


template<class T>
BinTNode<T>* BinaryTree<T>::SearchNode(BinTNode<T>* &tree,T data)
{
	if (tree == NULL)return NULL;
	if (tree->data == data)
		return tree;
	BinTNode<T>*p=SearchNode(tree->lchild,data);
	if (p != NULL)
		return p;
	p = SearchNode(tree->rchild, data);
	if (p != NULL)return p;
}

template<class T>
inline BinTNode<T>* BinaryTree<T>::SearchParentNode(BinTNode<T>*& tree, T data)
{
	if (tree == NULL) return NULL;
	if (tree->lchild != NULL)
	{
		if (tree->lchild->data == data)
			return tree;
	}
	if (tree->rchild != NULL)
	{
		if (tree->rchild->data == data)
			return tree;
	}
	BinTNode<T>* p = NULL;
	p = SearchParentNode(tree->lchild, data);
	if (p != NULL)
		return p;
	p = SearchParentNode(tree->rchild, data);
	if (p != NULL) return p;
}

template<class T>
inline void BinaryTree<T>::AdjustTree(BinTNode<T>* tree, int op)
{
	if (tree == NULL) return;
	if (op==0) tree->point.x += 50;
	else tree->point.x -= 50;
	AdjustTree(tree->lchild, op);
	AdjustTree(tree->rchild, op);
}

template<class T>
int BinaryTree<T>::Height(BinTNode<T>* tree)
{
	if (tree == NULL) return 0;
	else
	{
		int i = Height(tree->lchild);
		int j = Height(tree->rchild);
		return (i < j) ? j + 1 : i + 1;
	}
}
