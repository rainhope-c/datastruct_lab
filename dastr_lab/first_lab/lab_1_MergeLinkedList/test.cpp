// 【问题描述】
//  两组无序整数，要求采用链表形式进行升序合并，例如将链表1->3->2 和 3->15 ->7 ->9 ->7合并为 1-> 2->3->7->9->15，只需输出结果，不能修改两个链表的数据。
// 【输入形式】
//  第一行为第一个链表的各结点值，以空格分隔。
//  第二行为第二个链表的各结点值，以空格分隔。
// 【输出形式】 合并好的链表，以非降序排列，值与值之间以空格分隔。
// 【样例输入】
// 1 4 6 3 4 9
// 5 7 3 4 8 9
// 【样例输出】
// 1 3 4 5 6 7 8 9
// 【评分标准】

//  要求使用链表实现，否则不能得分。

//第一步是把输入的两行数存在链表中
//第二步是把这两组数进行排序
//第三步是对顺序链表进行合并

#include <iostream>
#include <vector>
#include <sstream>
#include <set>

using namespace std;

//链表
struct LinkNode
{
    int data;
    LinkNode* next;
    LinkNode() :data(0), next(NULL) {}  //默认构造函数
    LinkNode(int d) :data(d), next(NULL) {}  //重载构造函数

};
class LinkList
{
public:
    LinkNode* head;  //头结点
    // 构造函数
    LinkList() : head(NULL) {}
    LinkList(LinkNode* h) :head(h) {}//重载构造函数

    // 析构函数
    ~LinkList()
    {
       LinkNode* current = head;
       while (current != NULL)
       {
           LinkNode* next = current->next;
           delete current;
           current = next;
       }
       head = NULL;
    }

    //尾插法建表
    void CreateLinkR(vector<int> arr, int size)  //两个参数，一个是动态数组，一个是数组大小
    {
        LinkNode* tail = NULL;  // 链表尾指针

        // 遍历数组，依次创建节点并插入链表尾部
        for (int i = 0; i < size; i++) 
        {
            // 创建新节点
            LinkNode* newNode = new LinkNode;
            newNode->data = arr[i];
            newNode->next = NULL;
            // 如果链表为空，则新节点同时成为头节点和尾节点
            if (head == NULL) {
                head = tail = newNode;
            }
            else {
                // 否则，将新节点插入到链表尾部
                tail->next = newNode;
                tail = newNode;  // 更新尾指针
            }
        }
    }

    // 打印链表
    void PrintList()
    {
        LinkNode* p = head;
        while (p != NULL)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

    
    //对链表进行排序
    void reorder(int size)
    {
        //利用冒泡算法进行降序排列
        //需要两个指针进行遍历
        //交换时只需要交换数据即可
        int end = size;
        while (end)  //利用end对这个链表进行遍历
        {
            LinkNode* p = head ;
            LinkNode* q = p->next;  //p始终指向q的下一个

            int flag = 0;  //表示已经完成排序了
            while(q!=NULL)
            {
                if (p->data > q->data)  //如果数据需要交换 
                {  //直接交换数据
                    int tem = p->data;
                    p->data = q->data;
                    q->data = tem;
                    flag = 1;  //说明没有完成排序
                }
                p = q;
                q = q->next;  //指针后移
            }
            if (!flag)
            {
                break;  //如果已经完成排序，那么直接跳出来就行
            }

            end--;
        }
    }

};


//现在需要一个去除数组中相同元素的函数
vector<int> removeD(const vector<int>& vec, int& newSize) {
    vector<int> uniqueElements; // 用于存储不重复的元素
    for (int i = 0; i < vec.size(); ++i) {
        bool isDuplicate = false; // 标记当前元素是否重复
        for (int j = 0; j < uniqueElements.size(); ++j) {
            if (vec[i] == uniqueElements[j]) {
                isDuplicate = true; // 如果找到重复元素，标记为true
                break;
            }
        }
        if (!isDuplicate) {
            uniqueElements.push_back(vec[i]); // 如果不重复，将元素添加到uniqueElements中
        }
    }
    newSize = uniqueElements.size(); // 更新新的vector的元素个数
    return uniqueElements; // 返回去重后的vector
}

//对降序链表的二路归并
//现在是知道两个二路链表的数据数量
LinkList merge(LinkList l1, LinkList l2)
{
    LinkNode* head = new LinkNode;
    LinkNode* p = head;  //作为新链表的遍历元素
    LinkNode* p1 = l1.head;  //用p1对l1遍历
    LinkNode* p2 = l2.head;  //用p2对l2遍历
    while (p1 != NULL && p2 != NULL)  //当p1和p2都不为0时
    {
        if (p1->data > p2->data)  //如果p2更小，就插入p2
        {
            LinkNode* newNode = new LinkNode;
            newNode->data = p2->data;
            p->next = newNode;
            p = newNode;
            p2 = p2->next;   
        }
        else if (p1->data < p2->data)  //如果p1更小，就插入p1
        {
            LinkNode* newNode = new LinkNode;
            newNode->data = p1->data;
            p->next = newNode;
            p = newNode;
            p1 = p1->next;   
        }
        else  //如果相等
        {
            LinkNode* newNode = new LinkNode;
            newNode->data = p2->data;
            p->next = newNode;
            p = newNode;
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    //结束遍历时已经遍历完了1或者2
    if (p1 != NULL)  //如果p1还没空
    {
        while (p1 != NULL)
        {
            LinkNode* newNode = new LinkNode;
            newNode->data = p1->data;
            p->next = newNode;
            p = newNode;
            p1 = p1->next;
        }
    }
    if (p2 != NULL)  //如果p1还没空
    {
        while (p2 != NULL)
        {
            LinkNode* newNode = new LinkNode;
            newNode->data = p2->data;
            p->next = newNode;
            p = newNode;
            p2 = p2->next;
        }
    }
    LinkList newlist(head);
    return newlist;
}



int main() {

    // 定义两个数组用于存储输入的数字
    vector<int> arr1, arr2;
    string line;

    // 读取第一行输入
    getline(cin, line);
    stringstream ss(line);  //把这一行转化为输入流以便进行进一步操作
    int num;
    int s1=0;  //第一行数据的个数
    while (ss >> num) {
        arr1.push_back(num);
        s1++;  //数据个数加一
    }
    // 读取第二行输入
    getline(cin, line);
    stringstream ss2(line);
    int s2 = 0;  //第二行数据的个数
    while (ss2 >> num) {
        arr2.push_back(num);
        s2++;  //数据数加一
    }
    arr1=removeD(arr1, s1);
    arr2=removeD(arr2, s2);
    //现在是做到了把两行数据存在两个动态数组中，并且获得了数据个数
    //接下来把它们从数组转移到链表里
    //参数为 vector<int> 的尾插法可以实现
    LinkList l1, l2;
    l1.CreateLinkR(arr1, s1);
    l2.CreateLinkR(arr2, s2);
    //l1.PrintList();
    //l2.PrintList();
    l1.reorder(s1);
    l2.reorder(s2);
    //cout << endl;
    //l1.PrintList();
    //l2.PrintList();
    //现在已经实现了把两行数据存入两个链表中,并且知道两行数据的数量
    //接下来来实现排序的算法
    
    //现在终于是成功实现了两个链表的重新排序
    //接下来就是顺序链表的二路归并
    LinkList l3 = merge(l1, l2);  //注意l3的头结点里没有存数据
    LinkNode* p = l3.head->next;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;

    return 0;
}

