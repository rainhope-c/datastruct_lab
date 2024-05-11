// 【问题描述】
//   小米和爸爸一起玩游戏，爸爸随机抽取几张纸牌，将正面朝下，然后依次执行如下步骤：
//  （1）第一步，将最上面一张纸牌移到最底下，新的最上面纸牌翻开放一边，该纸牌是梅花1（A）。
//  （2）第二步，将最上面一张纸牌移到最底下，这样做两次，两次完后将新的最上面纸牌翻开放一边，该纸牌是梅花2。
//  （3）第三步，将最上面一张纸牌移到最底下，这样做三次，三次完后新的最上面纸牌翻开放一边，该纸牌是梅花3。
//  （4）以此类推，第n步做n次移动后新的最上面纸牌翻开放一边，该纸牌是梅花n。
//   小米说爸爸一定提前安排了纸牌顺序，并且很快推算出纸牌初始顺序，请用循环队列编写程序验证纸牌初始顺序。
// 【输入形式】
// 第一行输入一个正整数m，表示测试用例数（接下来的行数位m），接着每行输入一个样例（即n）
// 【输出形式】
// 输出m行，每行对应相应测试用例的纸牌初始顺序，即1到n这n个整数的某种排列（以空格隔开）
// 【样例输入】
// 2
// 3
// 4
// 【样例输出】
// 3 1 2
// 2 1 4 3
// 【评分标准】
// 通过所有测试点得满分。



//第一步，根据输入的第一行得到所需要的数组数量
//第二步，根据后面两行创建相应的数组
//第三步，求出相应的数组的序号
//第四步，输出这几个数组

#include <iostream>
#include <vector>
using namespace std;

//链队的定义
struct LinkNode
{
	int data;
	LinkNode* next;
	LinkNode() :next(NULL) {}
	LinkNode(int d) :data(d) {}
};

class LinkQueue
{
public:
	LinkNode* front;
	LinkNode* rear;
	
	LinkQueue()  //构造函数
	{
		front = NULL;
		rear = NULL;
	}
	~LinkQueue()
	{
		LinkNode* pre = front, * p;
		if (pre != NULL)
		{
			if (pre == NULL)
			{
				delete pre;
			}
			else {
				p = p->next;
				while (p != NULL)
				{
					delete pre;
					pre = p;p = p->next;
				}
				delete pre;
			}
		}
	}
	bool empty()
	{
		return rear == NULL;
	}
	bool push(int e)
	{
		LinkNode* p = new LinkNode(e);
		if (rear == NULL)
			front = rear = p;
		else
		{
			rear->next = p;
			rear = p;
		}
		return true;
	}
	int pop(int& e)
	{
		if (rear == NULL)
		{
			return false;
		}
		LinkNode* p = front;
		if (front == rear)
		{
			front = rear = NULL;
		}
		else
			front = front->next;
		e = p->data;
		delete p;
		return true;
	}
	bool gethead(int& e)
	{
		if (rear == front) return false;
		e = front->data;
		return true;
	}
	bool sethead(int e)
	{
		if (rear == front) return false;
		front->data = e;
		return 0;
	}
};

vector<int> calcu(int size)  //这个函数来实现需要的功能，传递的参数是操作的次数
{
	vector<int>re(size);
	LinkQueue result;
	for (int i = 0;i < size;i++)
	{
		result.push(i + 1);  //先依次存入1 2 3...
	}
	for (int i = 1;i < size + 1;i++)
	{
		//第i次进行出队i次得到的队头为i
		for (int j = 0;j < i;j++)
		{
			int tem = 0;
			result.pop(tem);  //相当于拿起第一张
			result.push(tem);  //放在最后面
		}
		//出队进队i次后,队头元素设置为i
		int tem=0;
		result.pop(tem);  //这个就相当于利用那个1 2 3...标记的当前的位置进行获取这个元素的数值i所处的实际位置
		//出队了，不进了，进一个新的数组
		re[tem - 1] = i;
	}
	return re;
}


int main()
{
	int m = 0;
	cin >> m;
	for (int i = 0;i < m;i++)
	{
		int x = 0;
		cin >> x;
		vector<int>a = calcu(x);
		for (int j = 0;j < x;j++)
		{
			cout << a[j] << " ";
		}
		cout << endl;
	}
	return 0;
}
