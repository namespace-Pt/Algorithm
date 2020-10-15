#include<iostream>
#include<ctime>
#include<math.h>
using namespace std;

// 随机数产生
int random(int x){
    srand(time(NULL));
    return rand()%(x);
}
// 定义结构体，分治策略时用于保存出现次数最多的数值和次数
typedef struct Node{
    int value;
    int count;
}Node;
// Divide-and-Conquer
Node majority_DaC(int * t,int length){
    // 结束条件，当数组长度小于2时，直接返回当前值，次数默认为1
    // O(1)
    if(length == 1){
        Node node;
        node.value = *t;
        node.count = 1;
        return node;
    }

    // 2分治，定义中间长度，将数组通过指针一分为二
    // 计算中间长度
    // O(1)
    int mid = length/2;
    int * s1 = t;
    int * s2 = t + mid;

    // 分治
    // 2T(n/2)
    Node node1 = majority_DaC(t,mid);
    Node node2 = majority_DaC(s2,length-mid);
    
    // 如果两个分支的“多数”相等则直接返回
    // O(1)
    if(node1.value == node2.value){
        node1.count += node2.count;
        return node1;
    }

    // 新的“多数”肯定是从两个分支的“多数”中产生，否则新的“多数”在某一个分支中出现的次数一定大于其当前“多数”，矛盾
    // 整合分治的两半时，只需要分别遍历分支的另一半数组，分别计算两边出现次数最多的数在拼接后的数组中出现的次数；加起来后刚好相当于便利了一遍整个数组
    // O(n)
    for(int i = 0;i < mid;i++){
        if(*(t + i) == node2.value){
            node2.count ++;
        }
    }
    for(int i = mid;i < length;i++){
        if(*(t + i) == node1.value){
            node1.count ++;
        }
    }
    return node1.count >= node2.count ? node1:node2;
}

// 蒙特卡洛算法的基本单元
// 随机选取index，看其对应元素是不是“多数”
bool Majority_MC(int * t,int length){
    int i = random(length);
    int x = *(t+i);
    int k = 0;
    // O(n)
    for(int j = 0;j < length;j++){
        if(*(t + j) == x){
            k++;
        }
    }
    return (k>length/2);
}

// 重复调用蒙特卡洛算法
// 偏真的1/2正确算法
bool Majority_MC_Wrapper(int *t,int length,double e){
    int k = log2(1/e);

    // 重复lg(1/e)次
    // O(nlg(1/e))
    for(int i = 0;i <= k;i ++){
        if(Majority_MC(t,length)){
            return true;
        }
    }
    return false;
}

int main(){
    int length = 8;
    int a[length] = {0};
    cout<<"--------input array--------"<<endl;
    for(int i = 0;i < length;i++){
        cin>>a[i];
    }
    Node result;
    int mode = 0;
    cout<<"--------input mode , 0 for Divide-and-Conquer while 1 for Monte Carlo--------"<<endl;
    cin>>mode;
    if(mode == 0){
        result = majority_DaC(a,length);
        if(result.count > length/2){
            cout<<"Majority Array!";
            return 0;
        }
        else
        {
            cout<<"Not Majority Array!";
            return 0;
        }
    }
    else
    {
        double e = 0.0;
        cout<<"--------input epsilon--------"<<endl;
        cin>>e;
        bool judge = Majority_MC_Wrapper(a,length,e);
        if(judge){
            cout<<"Majority Array!";
            return 0;
        }
        else{
            cout<<"Not Majority Array!";
            return 0;
        }
    }
}