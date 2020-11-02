#include<iostream>
#include<limits.h>
using namespace std;

// 备忘录法自顶向下实现动态规划
int Lookup_Chain(int **M,int ** S,int *p,int i,int j){
    
    // 如果值不是初始化的最大值，则返回
    // O(1)
    if(M[i][j] < INT_MAX){
        return M[i][j];
    }
    
    // 如果只有一个矩阵，直接返回0
    // O(1)
    if(i == j){
        return 0;
    }

    else
    {
        // 从i~j中选出一个最优的k
        // 最多只有n-1种情况，即子状态图中每个节点最多只有n-1条边
        for(int k = i;k < j;k++){

            // 计算不同k下Ai...Aj的总计算次数
            int q = Lookup_Chain(M,S,p,i,k) + Lookup_Chain(M,S,p,k+1,j) + p[i-1]*p[k]*p[j];

            // 如果有更优的，则直接替换备忘录中的值
            // 同时更新记录划分位置的矩阵
            if(q < M[i][j]){
                M[i][j] = q;
                S[i][j] = k;
            }
        }
    }
    // 返回Ai...Aj的最优计算次数
    return M[i][j];
}

// 初始化矩阵，调用算法计算最优计算次数
int Memoized(int ** S,int *p,int length){
    // 申请空间
    int ** M = new int*[7];
    for(int i = 1;i < length;i++){
        // 初始化两个数组，一个保存最优值，一个保存最优划分位置
        M[i] = new int[7]();
        S[i] = new int[7]();
        // 初始化为最大int
        for(int j = i;j < length;j++){
            M[i][j] = INT_MAX;
        }
    }
    return Lookup_Chain(M,S,p,1,length-1);
}

// 用于打印最终划分
void print_optimal(int ** s,int i,int j){
    if(i==j){
        cout<<"A"<<i;
    }
    else
    {
        cout<<'(';
        // 打印前半部分最优划分
        print_optimal(s,i,s[i][j]);
        // 打印后半部分最优划分
        print_optimal(s,s[i][j]+1,j);
        cout<<')';
    }
}

int main(){
    // 按照ppt输入矩阵规模序列
    int p[7] = {30,35,15,5,10,20,25};
    int ** S = new int*[7];
    cout<<"input the matrix scale sequence of LENGTH 6:"<<endl;
    for(int i = 0;i < 7;i++){
        cin>>p[i];
    }
    cout<<Memoized(S,p,7)<<endl;
    print_optimal(S,1,6);
    return 0;
}