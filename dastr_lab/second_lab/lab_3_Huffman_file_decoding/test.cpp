// 【问题描述】
// 给定一组字符的Huffman编码表（从标准输入读取），给定一个用该编码表进行编码的Huffman编码文件（存在当前目录下的in.txt中），编写程序对Huffman编码文件进行解码。
// 例如给定的一组字符的Huffman编码表为：
// 6

// 1:111
// 2:0
// +:110
// *:1010
// =:1011
// 8:100
// 第一行的6表示要对6个不同的字符进行编码，后面每行中冒号（:）左边的字符为待编码的字符，右边为其Huffman编码，冒号两边无空格。对于该编码表，对应的Huffman树（树中左分支表示0，右分支表示1）应为：
// 假如Huffman编码文件in.txt中的内容（由0和1字符组成的序列）为：
// 111011010010110101010011001100
// 则遍历上述Huffman树即可对该文件进行解码，解码后的文件内容为：
// 12+8=2*8+2+2
// 【输入形式】
// 先从标准输入读入待编码的字符个数（大于等于2，小于等于30），然后分行输入各字符的Huffman编码（先输入字符，再输入其编码，字符和编码中间以一个英文字符冒号:分隔），编码只由0和1组成。
// Huffman编码文件为当前目录下的in.txt文本文件，即：其中的0和1都是以单个字符的形式存储，文件末尾有一个回车换行符。
// 【输出形式】
// 将解码后的文件内容输出到标准输出上
// 【样例输入】
// 6
// 1:111
// 2:0
// +:110
// *:1010
// =:1011
// 8:100
// 假如in.txt中的内容为：
// 111011010010110101010011001100
// 【样例输出】
// 12+8=2*8+2+2
// 【样例说明】
// 从标准输入读取了6个字符的Huffman编码，因为规定Huffman树中左分支表示0，右分支表示1，所以利用该编码表可构造上述Huffman树（见图1）。遍历该Huffman树对编码文件in.txt的进行解码，即可得到解码后的原文件内容。
// 【评分标准】
// 该题要求根据字符的Huffman编码表对编码文件进行解码。

//根据用哈夫曼码得到的编码进行解码然后把解码得到的树输出
//这题感觉问题不太大
//就是题目没有说清到底是怎么输入就是了
//这个编码用什么存储呢？想用图但是不会，那强行用数组吗
//用两个数组，一个char一个int？不好读取，还有个方法是创建结构体

#include <queue>
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <string>

using namespace std;

struct node  //每个node都有一个字符和一个string
{
    char ch;  //问题在于多位数怎么办->答：不用特殊考虑
    string val;
    node(char chh,string vall)
    {
        ch =chh;
        val =vall;
    }
    //这里忘了重载默认构造函数出了点小问题
    node(){}
};

void disnode(node n)
{
    cout<<"字符串";
    cout<<n.ch<<"对应的编码为："<<n.val;
    cout<<endl;
    return ;
}

//好像需要遍历
void getGoal(queue<char>&target,string &goal)
{
    char x=target.front();
    target.pop();
    goal+=x;
}
void decode(queue<char>target,vector<node>hcode)
{
int cnt=hcode.size();
string goal;
while(!target.empty())  //target全部出队时停止
{
    getGoal(target,goal);  //得到goal
    //然后遍历比较
    for(int j=0;j<cnt;j++)
    {
    if(hcode[j].val==goal)  //比较出来了结果
    {
    cout<<hcode[j].ch;  //输出对应的字符
    goal.clear();  //goal重置
    break;  //停止遍历
    }
    //如果没有比较出结果
    }
    }

}


int main()
{
    int cnt=0;
    cin>>cnt;
    vector<node>hcode(cnt);
    for(int i=0;i<cnt;i++)
    {
        char tem;
        char ch; 
        string str;
        cin>>ch>>tem>>str;
        node newnode=node(ch,str);
        hcode[i]=newnode;
    }  
    //实现了结点的创建
    // for(int i=0;i<cnt;i++)
    // {
    // disnode(hcode[i]);
    // }

    //接下来就想办法实现这个解码的过程
    //两个想法，一是转化为括号表达然后直接转
    //二是直接构建
    //我看着怎么和树没啥关系啊
    //哦哦我懂了，我的思路不一样
    //这样好像更简单 直接利用哈夫曼树的一个性质是得到的编码没有重复

    ifstream infile("in.txt");
    queue<char>target;
    char x;
    while(infile>>x)
    {
    target.push(x);
    }
    // for(int i=0;i<length;i++)
    // {
    // cout << target[i];
    // }
    //现在是存进去了
    decode(target,hcode);
    return 0;
}


