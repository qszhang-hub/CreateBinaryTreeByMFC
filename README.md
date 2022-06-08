# MFC-CreateBinaryTreeByMFC
CUG数据结构某次作业
# 根据前序+中序或中序+后序在MFC中实现动态建立二叉树。

</font>

<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

# 前言

在上一篇博客中，我分享了如何根据前序、后序、前序+中序、中序+后序建立二叉树。今天来分享一下如何在MFC中动态建立二叉树，并且具有序列检错机制和查询父节点功能。
功能展示:
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201031130400152.gif#pic_center)

</font>

<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

# 一、动态建立二叉树
## 1.题目要求
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201030204243835.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L20wXzQ2Mjg2MzUx,size_16,color_FFFFFF,t_70#pic_center)
## 2.具体实现
### 1.对话框布局
上面的控件是PictureControl控件
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201030205446966.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L20wXzQ2Mjg2MzUx,size_16,color_FFFFFF,t_70#pic_center)
### 2.二叉树节点和二叉树类的定义
#### 1.二叉树结点
```javascript
// 定义在BinaryTree.h头文件中
#pragma once
#include<iostream>
using namespace std;
template <class T>
struct BinTNode
{
	T data;				//节点数据
	CPoint point;		//每个节点的位置
	BinTNode<T>* lchild, * rchild, * parent;
	BinTNode() :lchild(NULL), rchild(NULL), parent(NULL) {}
	BinTNode(T x, BinTNode<T>* l = NULL, BinTNode<T>* r = NULL)
		:data(x), lchild(l), rchild(r), parent(NULL) {}
};
```
#### 2.二叉树类
```javascript
// 定义在BinaryTree.h头文件中
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
	BinTNode<T>* SearchParentNode(BinTNode<T>*& tree, T data);//从结点tree开始搜索值为data的节点，返回该节点的父节点
	void AdjustTree(BinTNode<T>* tree, int op);//调整树中结点位置
	int Height(BinTNode<T>* tree);//求树高
};
```
### 3.打印二叉树
思路：
首先，根据前序+中序（或中序+后序）建立一颗二叉树。然后打印这棵树。难点在于如何打印这棵树，以及打印时的布局。接下来我会详细讲如何打印，以及节点如何布局。
关于打印二叉树：我选择了在一个PictureControl控件中打印。首先获得该控件的画布，以及控件大小。
```javascript
// 获取控件画布以及控件大小，设置画笔
	CRect rect;
	CWnd* pWin = GetDlgItem(IDC_STATIC);
	pWin->GetClientRect(rect);//获取控件大小
	int x = rect.Width();//x即控件宽度			
	int y = rect.Height();//y即控件高度	
	CDC* pDC = pWin->GetDC();//获取控件画布
	CPen pen(PS_SOLID, 3, RGB(255, 0, 0));//创建画笔
	pDC->SelectObject(&pen);//选择画笔
```
我使用了递归画树的方法。函数参数有两个，一个是画家CDC*pDC，另一个是开始节点tree。
打印节点的操作非常简单，只需要以节点位置为圆心画圆，再在该位置打印节点元素值即可。接下来就是递归，画这个节点的左子树和右子树，然后每画一个节点，就将对应根节点与之相连。
而要实现动态建立，只需要添加Sleep（time）函数即可。Sleep（time）函数就是让程序暂停time毫秒。
```javascript
// 二叉树打印函数
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
		//连接根节点和该节点
		pDC->MoveTo(tree->point.x, tree->point.y);
		pDC->LineTo(tree->lchild->point.x, tree->lchild->point.y);
	}
	if (tree->rchild != NULL)
	{
		PrintBinaryTree(pDC, tree->rchild);
		Sleep(200);
		//连接根节点和该节点
		pDC->MoveTo(tree->point.x, tree->point.y);
		pDC->LineTo(tree->rchild->point.x, tree->rchild->point.y);
	}
}
```
是不是觉得很简单？是的，打印二叉树很简单，但是难在如何获得对应节点的位置。关于节点位置的获取，我的方法是，在建立二叉树时，每建立一个节点，就设置一个初始的位置。对于根节点，肯定是第一排中间，横坐标就是x/2，纵坐标取绝于你的圆半径，以我的为例，圆半径是25，那么根节点的纵坐标就是25.即根节点位置（x/2，25）.其左子树就将横坐标-50，右子树就将横坐标+50，纵坐标都+100.
```javascript
// 根据前序+中序建立二叉树
template <class T>
//参数意义：tree1是要建立的节点，tree2是其父节点，pre是前序序列，in是中序序列，n是序列长度，x、y是横纵坐标位置
void BinaryTree<T>::CreateBinTree1(BinTNode<T>*& tree1, BinTNode<T>*& tree2, char* pre, char* in, int n, long x, long y)
{
	if (n <= 0) return;
	T tmp = *pre;
	tree1 = new BinTNode<T>(tmp);//前序序列第一个必为根节点
	tree1->parent = tree2;//设置节点的父节点
	//注意：一定要分开设置x和y，切不可直接一步tree1->point=(x,y)；具体为何，你可以调试的时候试试，最后建立的point值和x、y不一样
	tree1->point.x = x;
	tree1->point.y = y;
	int m = 0;
	for (; m < n; m++)
	{
		if (tmp == in[m])
			break;
	}//得到根节点在中序序列中的下标m
	//根据得到的下标m来划分左右子树，递归建立
	CreateBinTree1(tree1->lchild, tree1, pre + 1, in, m, x - 50, y + 100);
	CreateBinTree1(tree1->rchild, tree1, pre + m + 1, in + m + 1, n - m - 1, x + 50, y + 100);
}
```
这样就在建立二叉树时获得了节点位置的初始值。
接下来，要调整节点位置，解决节点位置冲突问题，即有些节点位置重合或左子树节点位置在右子树节点右边、右子树节点位置在左子树节点左边。
解决思路：
①按照满二叉树的格式调整节点位置
②节约空间的节点位置调整算法
第一种较为简单，第二种比较复杂，一个一个来说，先讲第一种。
#### ①按照满二叉树的格式调整节点位置
此算法需要知道树高。根节点一定打印在中间，不需要调整。其左右子树开始，左孩子.x=根节点.x-2^(h-l)*r； 右孩子.x=根节点.x+2^(h-l)*r（h是树高；l是当前节点所处层数，从0开始；r是绘制节点圆的半径）这个可以自己绘图推导，很容易看出来的。由此就可以递归调整位置。
具体实现借鉴了该博客：[如何用Qt绘制一颗好看的二叉树](https://blog.csdn.net/Apple_Coco/article/details/83501851?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522160492541019725255536363%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=160492541019725255536363&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_v2~rank_v28-1-83501851.first_rank_ecpm_v3_pc_rank_v2&utm_term=qt%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E5%9B%BE%E5%BD%A2%E6%98%BE%E7%A4%BA&spm=1018.2118.3001.4449)
求树高函数：
```javascript
// 定义在BinaryTree.h文件中
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
```
调整算法：
```javascript
// 定义在对话框.cpp文件中
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
```
这种算法打印的二叉树很美观，但是缺点是因为层数的增多导致树特别庞大，从第五层开始会超出对话框。同时，对于哪些每一层并不是满节点的树而言，这种算法会占据大量空间，导致不能如我们所愿的打印一些高度比较高但是节点数目较少的树。
于是就有了接下来的节省空间的节点位置调整算法。
#### ②节省空间的节点位置调整算法
采用层次遍历的方法遍历二叉树，在同一层中，如果有两节点横坐标冲突，就从这两个节点的共同父节点下的左右孩子开始调整，以左孩子为根节点的左子树整体向左移动，以右孩子为根节点的右子树整体向右移动。由于左子树向左移动，右子树向右移动，不免会因为靠右边节点的调整导致左边已经调整好的节点又产生问题，因此我们要重复判断该层节点，直到该层节点不再出现问题。又因为移动会对上层节点造成影响，所以我们要向上逐层进行冲突判断。
思路借鉴了该博客：[二叉树的图形显示](https://blog.csdn.net/copica/article/details/39291141?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522160492540619724842950415%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=160492540619724842950415&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_click~default-1-39291141.first_rank_ecpm_v3_pc_rank_v2&utm_term=%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E5%9B%BE%E5%BD%A2%E6%98%BE%E7%A4%BA&spm=1018.2118.3001.4449)
代码如下：（其中的AdjustTree函数是定义在BinaryTree.h中的节点位置递归调整函数）
先看AdjustTree函数：
```javascript
// 参数说明：tree是开始递归的节点；op是运算符，op为0时x坐标增加，
//其他情况下减少。
//此函数从节点tree开始往下递归，调整以tree为根节点的子树的x坐标
template<class T>
inline void BinaryTree<T>::AdjustTree(BinTNode<T>* tree, int op)
{
	if (tree == NULL) return;
	if (op==0) tree->point.x += 50;
	else tree->point.x -= 50;
	AdjustTree(tree->lchild, op);
	AdjustTree(tree->rchild, op);
}
```
再看调整函数：
```javascript
//在对话框.h文件中创建树Bin
	BinaryTree<char> Bin;
// 定义在对话框.cpp文件中
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
```
该算法只有在节点位置冲突时才会调整位置，因此对于树高很高，节点数目少的树来说，会打印的更加美观紧凑。

大功告成，动态建立二叉树至此结束。
<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

# 二、检错机制
## 1.错误列举
常见错误：
1.两个序列长度不同
2.两个序列的元素不同，或者有一个序列其中的元素有重复
非常见错误：
更换左右子树中的节点。
例如：
前序序列：ABDECFG
中序序列：FCGADBE
其中，我把中序序列左右子树做了调换，仅仅依靠前两种检错是查不出来的，但是这两个序列就是建不成树，因此，需要添加更加健壮的检错手段。
## 2.检错方法
### 1.一个判断两个序列前n个元素是否相同的函数
```javascript
// 定义在对话框.cpp文件中
//参数：前两个分别为两个序列，第三个参数是要检错的长度
bool CCreateBinaryTreeByMFCDlg::Compare(char* p1, char* p2, int n)
{
	char ch,ch1;
	//先在第2个序列里一一查找第一个序列的元素
	for (int i = 0; i < n; i++)
	{
		//因为strchr函数是根据'\0'来判断结尾的，所以我们可以采用将要检错第n个元素后一个元素值改为'\0'，的办法来仅查找前n个元素
		ch = p1[i];
		ch1 = p2[n];//先记录下改变前的元素
		p2[n] = '\0';
		if (strchr(p2, ch) == NULL)//找不到说明两个序列中的元素不同
		{
			AfxMessageBox(_T("序列输入错误！"));
			return 0;	//出错返回0
		}
		p2[n] = ch1;//查找后再将该值改回去
	}
	//再在第1个序列里一一查找第二个序列的元素
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
```
### 2.一段判断两个序列长度是否相等的代码
m_ctrlseq1对应第一个序列的编辑框的CEdit类型，m_csseq1对应第一个序列的CString类型
```
	m_ctrlseq1.GetWindowTextW(m_csseq1);
	m_ctrlseq2.GetWindowTextW(m_csseq2);
	//比较两个字符串长度
	if (m_csseq1.GetLength() != m_csseq2.GetLength())
	{
		AfxMessageBox(_T("序列输入错误！"));
		return;
	}
```
### 3.对于非简单差错的检错
思路：我们在中序中得到根节点后，获得左右两个子树的中序序列，同时也能在前序序列中找到左右子树的前序序列。然后分别对比左右子树前序序列和中序序列中元素是否相同。如果不相同，肯定说明左右子树元素有改变。如果无误，接着递归，直到子树序列长度<=0。
#### 1.按前序+中序递归方式比较两个序列
```javascript
// 前序+中序的情形
bool CCreateBinaryTreeByMFCDlg::CompareSeq1(char* p1, char* p2, int n)
{
	//子树序列长度<=0，说明到最后都无误，结束递归，返回1
	if (n <= 0) return 1;
	int i = 0;
	char tmp = p1[0];//根节点
	if (Compare(p1, p2,n))//如果两个序列元素一致，就对比其左右子树
	{
		int m = 0;
		for (; m < n; m++)
		{
			if (tmp == p2[m])
				break;
		}
		//对比左子树两个序列元素
		i = CompareSeq1(p1 + 1, p2, m);
		//如果左子树两个序列元素一致，继续比较右子树
		if (i)
		{
			i = CompareSeq1(p1 + m + 1, p2 + m + 1, n - m - 1);
			if (i) return 1;//右子树也一致，返回1
			else return 0;//右子树两个序列不同，返回0
		}
		else return 0;//左子树两个序列元素不同，返回0
	}
	else return 0;//两个序列元素不同，返回0
}
```
#### 2.按中序+后序递归方式对比两个序列
```javascript
// 中序+后序的情形
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

```
## 3.完整检错函数（其中调用了前面的检错函数）
```javascript
// 检错函数 定义在对话框.cpp文件中
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
	//根据用户选择的是前序+中序还是中序+后序来决定调用哪个函数
	switch (m_type)
	{
	case 1:i = CompareSeq1(p1, p2, strlen(p1)); break;
	case 2:i = CompareSeq2(p1, p2, strlen(p1)); break;
	default:AfxMessageBox(_T("请先选择构造方式！"));
	}
	if (i) AfxMessageBox(_T("输入序列无误"));
}
```
<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

# 三、查询父节点
要求是不可以用三叉链表自带的parent指针找。
## 1.二叉树类中的查询父节点函数
```javascript
// 定义在BinaryTree.h文件中
template<class T>
inline BinTNode<T>* BinaryTree<T>::SearchParentNode(BinTNode<T>*& tree, T data)
{
	if (tree == NULL) return NULL;
	//由于要判断其孩子节点的值，因此先判断孩子节点是否存在
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

```
## 2.查询父节点
```javascript
//点击查询父节点按钮时调用
//定义在对话框.cpp文件中
void CCreateBinaryTreeByMFCDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrlseq3.GetWindowTextW(m_csseq3);//从节点1编辑框中获得CString类型的元素值
	//CString转char*
	USES_CONVERSION;
	//函数T2A和W2A均支持ATL和MFC中的字符
	char* p3 = T2A(m_csseq3);
	char ch = *p3;//获得元素值
	BinTNode<char>* pParent = Bin.SearchParentNode(pRoot, ch);
	char Parentdata = pParent->data;
	m_csseq4.Format(_T("%c"), p4);
	m_ctrlseq4.SetWindowTextW(m_csseq4);//显示在父节点编辑框中
}
```
## 3.查询两个子节点共同的父节点
这种情况要考虑两个节点不在同一层的情景，例如下图的E和H：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201031160415329.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L20wXzQ2Mjg2MzUx,size_16,color_FFFFFF,t_70#pic_center)
这种情况下EH共同父节点肯定是A。我们在处理时就要考虑到节点不同层的问题。这时我们要把处在下层的节点的父节点继续向上找，直到其父节点与另一个节点的父节点同层。
```javascript
//当用户点击了查询共同父节点按钮时调用该函数
//定义在对话框.cpp文件中
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
	BinTNode<char>* pParent3 = Bin.SearchParentNode(pRoot, ch3);
	BinTNode<char>* pParent5 = Bin.SearchParentNode(pRoot, ch5);
	//先对比两个节点的父节点是否同层，不同层就调整下面的节点，再找它的父节点，直到两个节点父节点同层。
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
	//如果两个父节点元素值不同，就说明还没找到共同的父节点，继续找。
	while (pParent3->data != pParent5->data)
	{
		pParent3 = Bin.SearchParentNode(pRoot, pParent3->data);
		pParent5 = Bin.SearchParentNode(pRoot, pParent5->data);
	}
	char parentdata = Bin.GetData(pParent3);
	m_csseq4.Format(_T("%c"), parentdata);
	m_ctrlseq4.SetWindowTextW(m_csseq4);
}
```
# 总结
以上就是今天要讲的内容，本文仅为本人数据结构上机作业所实现功能，水平有限，希望能对大家有所帮助。具体程序已上传，大家可以免费下载。
[蓝奏云链接](https://wws.lanzous.com/iSOS7i8cmdi)
