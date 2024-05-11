// 【问题描述】将稀疏矩阵M进行转置为T，要求“按位就座”（对M矩阵的三元组顺序表扫描一次完成转置）
// M的三元组表示
// 【输入形式】
// 从键盘输入一个稀疏矩阵M，要求按三元组形式输入，第一行输入矩阵的行、列以及非零元素个数,接着输入M的每个非零元素的三元组表示
// 【输出形式】
// 在屏幕上输出M的转置矩阵，要求按照三元组形式输出
// 【样例输入】
// 6 7 8

// 0 1 12
// 0 2 9
// 2 0 -3
// 2 5 14
// 3 2 24
// 4 1 18
// 5 0 15
// 5 3 -7

// 【样例输出】
// 7 6 8

// 0 2 -3
// 0 5 15
// 1 0 12
// 1 4 18
// 2 0 9
// 2 3 24
// 3 5 -7
// 5 2 14
// 【评分标准】必须采用“按位就坐”的方法，所有样例全部正确得满分，抽查必选题。

//第一个问题，什么是稀疏矩阵的三元组？->每行三个元素，分别是非零元素所处的行、非零元素所处的列以及这个非零元素的值，题目的输入是第一行的输入是总行数、总列数以及总非零元素的个数
//第二个问题，什么是所谓的“按位就座”  -->扫描一次就完成转置
//第三个问题，在按位就座的情况下怎么对这个稀疏矩阵求逆置？
//第四个问题，输入和输出，这道题比较好解决


//最大的问题是逆置后的顺序
//上个厕所想清楚了
//创建对应非零元素个数个元素的vector，vector中的元素是node，每个node中有一个row,col和val
//逆置函数实现所有node的col和row的交换
//dispaly函数实现按照row优先，col次之从小到大的顺序输出

#include <iostream>
#include <vector>

using namespace std;

struct node
{
    int row;
    int col;
    int val;
    node(int roww,int coll,int vall)
    {row=roww;
    col=coll;
    val=vall;
    }
    node(){}

};

void triple(vector<node>&m)  //这个函数实现矩阵的逆置
{
    int cnt=m.size();
    for(int i=0;i<cnt;++i)  //遍历这个矩阵
    {
        int tem=m[i].row;  //对每个实现行和列的互换
        m[i].row=m[i].col;
        m[i].col=tem;
    }
}

void reorderm(vector<node>&m)  //矩阵重新排列
{
    node min=m[0];
    //冒泡吗
    int cnt=m.size();
    for(int i=0;i<cnt;i++)
    {
        min =m[i];
        int target=i;  //这个标记最小的是第几个
        for(int j=i+1;j<cnt;j++)
        {
        if(min.row>m[j].row)  //如果找到更小的就替换
        {  
        min=m[j];
        target=j;
        }
        if(min.row==m[j].row)  //如果行数相同就比较列数
        {if(min.col>m[j].col)  //如果col的列数也更小的话
            {
                min=m[j];
                target=j;
            }
        }
        }
        //最后把m[target]和m[i]交换，需要标记一下
        //这个列的部分也需要
        if(target!=i)
        {
            node tem=m[i];
            m[i]=m[target];
            m[target]=tem;  //这个赋值错了浪费我半小时
        }
    }
}


int main()
{
    int row,col,cnt=0;
    cin>>row>>col>>cnt;
    vector<node>matrix(cnt);
    for(int i=0;i<cnt;i++)  //遍历建立这个稀疏矩阵
    {int temr,temc,temv;
    cin>>temr>>temc>>temv;  
    node newnode=node(temr,temc,temv);
    matrix[i]=newnode;
    }
    //这样就完成了稀疏矩阵的输入
    triple(matrix);  //先逆置
    reorderm(matrix);  //然后重新排列
    //再输出
    cout<<col<<" "<<row<<" "<<cnt<<endl;  //先输出好搞的
    for(int i=0;i<cnt;i++)
    {
    cout<<matrix[i].row<<" "<<matrix[i].col<<" "<<matrix[i].val<<endl;
    }
    return 0;



}

