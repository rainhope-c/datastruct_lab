// 【问题描述】
// 从标准输入中读入一个整数算术运算表达式，如24 / ( 1 + 2 + 36 / 6 / 2 - 2) * ( 12 / 2 / 2 )= ，计算表达式结果，并输出。
// 要求：
// 1、表达式运算符只有+、-、*、/，表达式末尾的=字符表示表达式输入结束，表达式中可能会出现空格；
// 2、表达式中会出现圆括号，括号可能嵌套，不会出现错误的表达式；
// 3、出现除号/时，以整数相除进行运算，结果仍为整数，例如：5/3结果应为1。
// 4、要求采用逆波兰表达式来实现表达式计算。
// 【输入形式】
// 从键盘输入一个以=结尾的整数算术运算表达式。操作符和操作数之间可以有空格分隔。
// 【输出形式】
// 在屏幕上输出计算结果（为整数，即在计算过程中除法为整除）。
// 【样例输入】
// 24 / ( 1 + 2 + 36 / 6 / 2 - 2) * ( 12 / 2 / 2 )     =
// 【样例输出】
// 18
// 【样例说明】
// 按照运算符及括号优先级依次计算表达式的值。
// 【评分标准】
// 通过所有测试点得满分。


#include <iostream>
#include <string>
using namespace std;

//链栈的定义
template <typename T>
struct LinkNode
{
	T data;
	LinkNode* next;

	LinkNode() :next(NULL) {}
	LinkNode(T d) :data(d), next(NULL) {}
};
template<typename T>
class stack
{
public:
	LinkNode<T>* rear;

	stack() :rear(NULL) {}
	~stack()
	{
		if (rear == NULL) return;
		LinkNode<T>* pre = rear, * p = pre->next;
		while (p != rear)
		{
			delete pre;
			pre = p;p = p->next;
		}
		delete pre;
	}

	bool empty()
	{
		return rear == NULL;
	}
	bool push(T e)
	{
		LinkNode<T>* p = new LinkNode<T>(e);
		if (empty())
		{
			rear = p;
			rear->next = rear;
		}
		else
		{
			p->next = rear->next;
			rear->next = p;
		}
		return true;
	}
	void pop()
	{
		LinkNode<T>* p;
		if (empty()) return;
		if (rear->next == rear)  //栈中只有一个元素
		{
			p = rear;
			rear = NULL;
		}
		else
		{
			p = rear->next;
			rear->next = p->next;
		}
		delete p;
	}
	T gettop()
	{
		if (empty()) return false;
		return rear->next->data;
	}
	T Getbottom()
	{
		return rear->data;
	}
};

class Express
{
	string exp;  //中缀表达式
	string postexp;  //后缀表达式
public:
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
				while (!opor.empty() && opor.gettop() != '(')
				{
					e = opor.gettop();
					opor.pop();
					postexp += e;
				}
				opor.pop();
			}
			else if (ch == '+' || ch == '-')  //加减的运算优先级最低，所以直接把栈上的全部出栈，然后这个入栈就行
			{
				while (!opor.empty() && opor.gettop() != '(')  
				{
					e = opor.gettop();
					opor.pop();
					postexp += e;
				}
				opor.push(ch);
			}
			else if (ch == '*' || ch == '/')  //乘除的优先级最高，一般情况下可以直接进栈，但同时还要考虑一下优先级相等的情况
			{
				while (!opor.empty() && opor.gettop() != '(' && (opor.gettop() == '*' || opor.gettop() == '/'))  //如果栈顶是乘或者除就出栈再进栈
				{
					e = opor.gettop();
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
			e = opor.gettop();
			opor.pop();
			postexp += e;
		}
	}
	int  GetValue()
	{
		stack<int>opand;
		int a, b, c, d;
		char ch;
		int i = 0;
		while (i < postexp.length())
		{
			ch = postexp[i];
			switch (ch)
			{
			case '+':
				a = opand.gettop(); opand.pop();
				b = opand.gettop(); opand.pop();
				c = a + b;
				opand.push(c);
				break;
			case '-':
				a = opand.gettop(); opand.pop();
				b = opand.gettop(); opand.pop();
				c = b - a;
				opand.push(c);
				break;
			case '*':
				a = opand.gettop(); opand.pop();
				b = opand.gettop(); opand.pop();
				c = b * a;
				opand.push(c);
				break;
			case '/':
				a = opand.gettop(); opand.pop();
				b = opand.gettop(); opand.pop();
				c = b / a;
				opand.push(c);
				break;
			default:  //如果是数字 需要考虑二位数三位数的情况
				d = 0;
				while (ch >= '0' && ch <= '9')
				{
					d = 10 * d + (ch - '0');
					i++;
					ch = postexp[i];
				}
				opand.push(d);
				break;
			}
			i++;
		}
		return opand.gettop();
	}
};


//现在是把整个逻辑都搞出来了
//下一步是输入



int main()
{
	string str;
	//= "(56-20)/(4+2)";
	//getline(cin, str, ' =' );
	getline(cin, str, '=');  //在cin中输入到 = 为止
	Express obj(str);  
	//cout << "中缀表达式：" << str << endl;
	//cout << "转化为后缀为：" << endl;
	obj.Trans();
	//cout << obj.getpostexp() << endl;  //前面哪来的两个空格？
	//cout << "求值结果为" << endl;
	cout << obj.GetValue() << endl;
	return 0;
}
