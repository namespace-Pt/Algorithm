#include<fstream>
#include<iostream>
#include<limits.h>
using namespace std;
// 定义输出数组的函数，方便调试
void print(int * a,int length){
    for(int i = 0;i < length;i++){
        cout<<a[i]<<endl;
    }
    return;
}

// 插入排序
// O((end-start)^2)
void insert_sort(int *A,int start,int end){
    
    int i = start+1;
    while(i < end){
        int v = *(A+i);
        int j = i-1;
        while(*(A+j) > v && j >= start){
            *(A+j+1) = *(A+j);
            j--; 
        }
        *(A+j+1) = v;
        i++;
    }
}

// 划分
// 将小于等于A[pivot]的值都放在其左边，大于的放在右边
int partition(int *A,int start,int end,int pivot){
    int x = A[pivot];
    
    // 首先将A[pivot]换到数组末尾，防止在交换过程中被调换了位置
    // O(1)
    swap(A[pivot],A[end-1]);
    int i = start-1;

    // 进行排序
    // O((end-start)^2)
    for(int j = start;j < end-1;j++){
        if(A[j] <= x){
            i++;
            swap(A[i],A[j]);
        }
    }
    swap(A[i+1],A[end-1]);
    return i+1;
}

// 选择函数
// 从A[start:end]中选出第target小的数的索引
int select(int *A,int start,int end,int target){
    // 如果数组长度为1，则直接返回
    if(end-start == 1) return start;

    // 初始复制
    // O(1)
    int i = 0,j = start;
    int length = end-start;
    int remain = length%5;

    // 因为相当于给O(n/5)个长度为O(5)的数组进行排序
    // O(n/5)*O(25) = O(n)
    for(i = start;i+4 < end;i+=5)
    {
        insert_sort(A,i,i+5);

        // 将中位数交换到数组最前面
        // “原址选择”
        swap(A[i+2],A[j]);
        j++;
    }

    // 如果有不能被5整除的部分，则单独划为一组
    // O(25)
    if(remain){
        insert_sort(A,end-remain,end);

        // 将中位数交换到数组最前面
        // “原址选择”
        swap(A[j],A[end-remain/2-1]);
        j++;
    }

    int pivot = 0;

    // 递归调用select，找中位数的中位数
    // 分情况，考虑一共有奇数组还是偶数组，如果是奇数组则找第 n+1/2 小的元素；如果是偶数组则找第 n/2 小的元素
    // T([n/5])，[x]代表x的上界
    if((j-start) % 2){
        pivot = select(A,start,j,(j-start)/2+1);
    }
    else{
        pivot = select(A,start,j,(j-start)/2);
    }
    
    // 依据找到的中位数的中位数，对数组进行划分
    // 数组A中，大于中位数的中位数的值至少有 3n/10 - 6 个
    // O(3n/10 - 6) = O(n)
    int q = partition(A,start,end,pivot);

    // 记录找到的pivot为数组中第几小的数
    int k = q-start+1;

    // 如果pivot即为第target小的数，则直接返回
    if(target == k){
        return q;
    }

    // 如果大于target，则在前面的一半找第 target 小的元素
    // 如果小于target，则在后面的一半找第 target-k 小的元素
    // 最多有 7n/10 + 6 个元素大于A[pivot]（中位数的中位数）
    // T(7n/10 + 6)
    else if(target < k){
        return select(A,start,q,target);
    }
    else{
        return select(A,q+1,end,target-k);
    }
}

int main(){
    int A[5000];
    int i = 0,j = 0;
    string value;

    // 读入文件
    ifstream fin("D:\\Data\\Class_data\\Alg_data\\lab4.txt");
    for(int i=0;i<5000;i++)
		fin>>A[i];

    cout<<"which ORDER statistic you want to find?"<<endl;
    cin>>j;
    int result = select(A,0,5000,j);
    cout<<j<<"th smallest number is: "<<A[result]<<endl;

    // 可以使用下面的测试
    // insert_sort(A,0,5000);
    // cout<<A[999];
    
    return 0;
}