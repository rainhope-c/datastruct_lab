// 【问题描述】
// 从标准输入中读入一个整数算术运算表达式，如 (3+4)*(8-2)+9/3=，构建表达式树，输出表达式树的前序、中序、后序以及层次遍历结果，并根据表达式树计算表达式的值。
// 【要求】
// 1. 表达式运算符只有+、-、*、/，表达式末尾的=字符表示表达式输入结束，表达式中可能会出现空格；
// 2. 表达式中会出现圆括号，括号可能嵌套，不会出现错误的表达式；
// 3. 出现除号/时，以整数相除进行运算，结果仍为整数，例如：5/3结果应为1。
// 4. 要求采用表达式树来实现表达式计算。
// 例如表达：(3+4)*(8-2)+9/3：   
// 【输入形式】
// 从键盘输入一个以=结尾的整数算术运算表达式。操作符和操作数之间可以有空格分隔。
// 【输出形式】
// 在屏幕上输出四种遍历结果（运算数后面加上#结束）以及计算结果（为整数，即在计算过程中除法为整除）。
// 【样例输入】
// (3-9)/3+5-7*4=
// 【样例输出】
// -+/-3#9#3#5#*7#4#
// 3#-9#/3#+5#-7#*4#
// 3#9#-3#/5#+7#4#*-
// -+*/5#7#4#-3#3#9#
// -25

//我觉得这题好有难度...

//ppt上给的思路是先转化为后续表达式然后根据后续表达式建立二叉树
//好像转化为后续表达式之后还挺简单，有点建立哈夫曼树的感觉
//把树建立好了之后输出就好说了，最终的求值有一点问题，应该是从叶子结点开始计算，完成一层的计算后把叶子结点的根节点转化为叶子结点然后递归

//第一part可以直接照搬第一次实验的代码吗
//但这个要换用树


#include <stack>
#include <iostream>
#include <string> 
#include <vector>
#include <queue>

using namespace std;


struct BTNode  //二叉链结点类
{
	string data;  //数据元素
	BTNode* lchild;  //左孩子结点
	BTNode* rchild;  //右孩子结点
	BTNode():lchild(NULL), rchild(NULL){}  //构造函数
	BTNode(string d)
	{
		data = d;
		lchild = rchild = NULL;
	}
};

class BTree
{
public:
	BTNode* r;  //二叉树的根节点r
	BTree()  //构造函数，创建一个空树
	{
		r = NULL;
	}

	//销毁二叉树
	void DestoryBTrer(BTNode* b)
	{
		if (b != NULL)
		{
			DestoryBTrer(b->lchild);
			DestoryBTrer(b->rchild);
			delete b;
		}
	}
	~BTree()
	{
		DestoryBTrer(r);
		r = NULL;
	}
    
};
//二叉树的层次遍历
void LevelOrder(BTree& bt)  //二叉树的层次遍历
{
BTNode* p;
queue<BTNode*> qu;  //定义一个队列
qu.push(bt.r);  //根节点入队

while(!qu.empty())  //当队不空就一直循环
{
p=qu.front();  qu.pop();  //去除队列最前面的结点p
cout<<p->data;  //访问结点p
if(p->lchild!=NULL)  //当有左孩子时将其进队
 qu.push(p->lchild);
if(p->rchild!=NULL)  //当有右孩子时将其进队
 qu.push(p->rchild);
}
}

//先序遍历算法
void PerOrder1(BTNode *b)
{
if(b!=NULL)
{
cout <<b->data;  //访问根节点
PerOrder1(b->lchild);  //先序遍历左节点
PerOrder1(b->rchild);  //先序遍历右节点
}
}
void PerOrder(BTree& bt)  //先序遍历的递归算法
{
PerOrder1(bt.r);
}

//中序遍历算法
void InOrder1(BTNode *b)  //被InOrder1函数调用
{
if(b!=NULL)
{
InOrder1(b->lchild);  //先遍历左子树
cout<<b->data;  //访问根节点
InOrder1(b->rchild);  //再遍历左子树
}
}
void InOrder(BTree &bt)  //中序递归的遍历算法
{
InOrder1(bt.r);
}

//后序遍历的算法
void PostOrder1(BTNode* b)
{
if(b!=NULL)
{
PostOrder1(b->lchild);  //先对左子树遍历
PostOrder1(b->rchild);  //再对右子树遍历
cout<<b->data;  //再访问当前根节点
}
}
void PostOrder(BTree &bt)   //后序遍历算法
{
PostOrder1(bt.r);
}


class Express
{

public:
	string exp;  //中缀表达式
	string postexp;  //后缀表达式
	Express(string str)
	{
		exp = str;
		postexp = " ";
	}
	string getpostexp()
	{
		return postexp;
	}

	void Trans()   //把中缀表达式转化成后缀表达式
	{
		stack<char> opor;
		int i = 0;
		char ch, e;
		while (i < exp.length())  //i对中缀表达式进行遍历
		{
			ch = exp[i];
			if (ch == '(')  //如果是')'直接入栈
			{
				opor.push(ch);
			}
			else if (ch == ')')  //如果是')'就把栈中'('后的所有运算符放入后续表达式，然后'('出栈
			{
				while (!opor.empty() && opor.top() != '(')
				{
					e = opor.top();
					opor.pop();
					postexp += e;
				}
				opor.pop();
			}
			else if (ch == '+' || ch == '-')  //加减的运算优先级最低，所以直接把栈上的全部出栈，然后这个入栈就行
			{
				while (!opor.empty() && opor.top() != '(')  
				{
					e = opor.top();
					opor.pop();
					postexp += e;
				}
				opor.push(ch);
			}
			else if (ch == '*' || ch == '/')  //乘除的优先级最高，一般情况下可以直接进栈，但同时还要考虑一下优先级相等的情况
			{
				while (!opor.empty() && opor.top() != '(' && (opor.top() == '*' || opor.top() == '/'))  //如果栈顶是乘或者除就出栈再进栈
				{
					e = opor.top();
					opor.pop();
					postexp += e;
				}
				opor.push(ch);
			}
			else if (ch == ' ')  //考虑输入空格的情况就直接跳过
			{
				;//什么操作都不进行
			}
			else  //如果输入是数字
			{ 
				string d;
				while (ch >= '0' && ch <= '9')  //如果输入的一直是数字字符
				{
					d += ch;  //提取全部连续的数字字符
					i++;
					if (i < exp.length())
						ch = exp[i];
					else
						break;
				}
				i--;  //注意这个需要退一个字符
				postexp += d;  //数字串存入后缀表达式
				postexp += "#";  //然后加一个#进行分隔
			}
			i++;
		}
		while (!opor.empty())  //如果遍历完了符号栈里还有符号的话
		{
			e = opor.top();
			opor.pop();
			postexp += e;
		}
	}

    BTNode* GreateTree()
	{
        BTree goaltree;
		queue<BTNode*>opand;
		BTNode* a,* b, *c, *d;
		string ch;
		int i = 1;
        BTNode*node=new BTNode;
        vector<BTNode*>newBTNode(1000,node);
		while (i < postexp.length())  //对后缀表达式进行遍历
		{
            int j=0;
			ch = postexp;
			switch (ch[i])
			{
			case '+':
				a = opand.front(); opand.pop();
				b = opand.front(); opand.pop();
                newBTNode[j]->data="+";
				newBTNode[j]->lchild=a;
                newBTNode[j]->rchild=b;
                opand.push(newBTNode[j]);
                j++;
                break;
			case '-':
				a = opand.front(); opand.pop();
				b = opand.front(); opand.pop();
                newBTNode[j]->data="-";
				newBTNode[j]->lchild=a;
                newBTNode[j]->rchild=b;
                opand.push(newBTNode[j]);
                j++;
                break;
			case '*':
				a = opand.front(); opand.pop();
				b = opand.front(); opand.pop();
                newBTNode[j]->data="*";
				newBTNode[j]->lchild=a;
                newBTNode[j]->rchild=b;
                opand.push(newBTNode[j]);
                j++;
                break;
			case '/':
				a = opand.front(); opand.pop();
				b = opand.front(); opand.pop();
                newBTNode[j]->data="/";
				newBTNode[j]->lchild=a;
                newBTNode[j]->rchild=b;
                opand.push(newBTNode[j]);
                j++;
                break;
			default:  //如果是数字 需要考虑二位数三位数的情况
                string tem;
                char x=ch[i];
				while (x >= '0' && x <= '9')
				{   
                    x=ch[i];    
                    if(x >= '0' && x <= '9')
                    {    tem+=x;
                    i++;
                    }
                    
				}
                newBTNode[j]->data=tem;
				opand.push(newBTNode[j]);
                j++;
				break;
			}
			i++;
		}
        BTNode* tem=opand.front();
        return tem;
	}
//我也不知道这个结果对不对
};


//现在是已经可以转化为后缀表达式了
int main()
{
	string str;
	//= "(56-20)/(4+2)";
	//getline(cin, str, ' =' );
    getline(cin >> ws, str, '='); // 读取到 '=' 为止，并忽略开头的空白字符
	Express obj(str);  
	// cout << "中缀表达式：" << str << endl;
	// cout << "转化为后缀为：" << endl;
	obj.Trans();
    BTNode* Node=new BTNode;
    Node=obj.GreateTree();
    BTree Tree;
    Tree.r=Node;
    PerOrder(Tree);  cout<<endl;
    InOrder(Tree);  cout<<endl;
    PostOrder(Tree);  cout<<endl;
    LevelOrder(Tree);  cout<<endl;


    
	return 0;
}
