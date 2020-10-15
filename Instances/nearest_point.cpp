#include<iostream>
#include<algorithm>
#include<math.h>
#include<map>
#include<fstream>
using namespace std;

// 定义乘方函数
float pow(float x){
    return x*x;
}

// 定义平面点的结构体
typedef struct
{
    int x=0;
    int y=0;
}point;

// 定义函数输出点对列表中的所有元素，方便调试
void print(point * a,int length){
    for(int i = 0;i < length;i++){
        cout<<(a+i)->x<<','<<(a+i)->y<<endl;
    }
    cout<<endl;
    return;
}

// 定义快排的比较函数
int compare_x(const void * a,const void * b){
    return ((point *)a)->x - ((point *)b)->x;
}
// 定义快排的比较函数
int compare_y(const void * a,const void * b){
    return ((point *)a)->y - ((point *)b)->y;
}

//根据讲义定义函数
float cpair2(point* s,int length){
    // 如果分治后得到的一边仅有一个点，那么将其距离设置为正无穷，这样默认在合并两边区域的时候进行计算其和另一边点之间的距离
    // O(1)
    if(length < 2){
        return 10000000000;
    }
    // 这里的mid_x可以用中位数
    // O(1)
    int mid = length/2;
    int mid_x = s[mid].x;

    // 分治
    // 注意分治的数组长度，千万不要越界，length是长度，mid可以理解为索引
    // T(n/2) * 2
    float d1 = cpair2(s1,mid);
    float d2 = cpair2(s2,length-mid);

    // O(1)
    float dm = (d1<d2)?d1:d2;

    // 定义指针偏移量，索引s构造p1和p2，不用新建数组
    int start = 0;
    int end = length;

    // 这里的逻辑不能用横坐标小于mid_x的点作为集合s1，大于等于的点作为集合s2
    // 因为有可能超过半数的点的坐标相同，这样的话中位数恒为该定值，那么在分治时无法将当前s分为两半
    // 因为横坐标小于等于mid_x的点会被归到一边，造成死循环
    // O(1)
    point* s1 = s;
    point* s2 = s+mid;
    // 新建两个数组，分别保存分界线两边的点
    point * p1 = new point[mid];
    point * p2 = new point[length-mid];
    // 数组的索引
    int p1_idx = 0;
    int p2_idx = 0;
    
    // 将s1中抽取距离中线一个dm内的点作为候选集
    // 两段加起来是整个数组，因此
    // O(n)
    for(int i = 0;i < mid;i ++){
        if(mid_x - (s1+i)->x >= 0 && mid_x - (s1+i)->x < dm){
            p1[p1_idx++] = *(s1+i);
        }
    }
    for(int j = 0;j < length-mid;j ++){
        if ((s2+j)->x - mid_x >= 0 && (s2+j)->x - mid_x < dm)
        {
            p2[p2_idx++] = *(s2+j);
        }
    }

    // 将候选集中的点按纵坐标排序
    // p1可以不进行排序，但是这样会隐性扩大y的搜索范围，如果排序后y的搜索区间重叠最小
    // 利用qsort，两段合起来才是n个点
    // O(nlgn)
    qsort(p1,p1_idx,sizeof(point),compare_y);
    qsort(p2,p2_idx,sizeof(point),compare_y);

    // 没必要保存dl=dm，节省空间
    // 记录上一次遍历到的位置，但严格来说并不能保证每次只遍历6个点，因为没办法保证上一次遍历到的点在恰好不满足下一次的条件
    int pre = 0;

    // 首先遍历中线左边的n/2个点
    // 之后从上一次遍历到的位置开始，分别向上和向下遍历中线右边的点，向上的点y差值不能超过dm，向下的点y差值不能超过dm，尽可能保证仅遍历6个点
    // n/2 * 6 = 3n
    for(int i = 0;i < p1_idx;i++){
        for(int k = pre;k >= 0; k--){
            if(p1[i].y - p2[k].y > dm){
                break;
            }
            
            // 保存临时距离
            // 更新最小值
            // O(1)
            pre = k;
            float tmp = sqrt(pow(p1[i].x - p2[k].x) + pow(p1[i].y - p2[k].y));
            if(tmp < dm){
                dm = tmp;
            }
        }
        for(int j = pre;j < p2_idx;j++){
            if(p2[j].y - p1[i].y > dm){
                // 仅在向下遍历时更新上次遍历到的位置
                pre = j;
                break;
            }

            // 保存临时距离
            // 更新最小值
            // O(1)
            float tmp = sqrt(pow(p1[i].x - p2[j].x) + pow(p1[i].y - p2[j].y));
            if(tmp < dm){
                dm = tmp;
            }
        }
    }
    delete []p1;
    delete []p2;

    return dm;
}
int main(){
    // 去重后只有2046个点
    point* a = new point[2046];
    string value;
    int n = 0;
    //转换成csv后读取
	ifstream fin("D:\\Data\\Class_data\\Alg_data\\lab1_points.csv");
    while(!fin.eof()){
        getline(fin,value);
        sscanf(value.c_str(),"%d,%d",&a[n].x,&a[n].y);
        n++;
    }
    //初始的点沿x必须是有序的
    qsort(a,2046,sizeof(point),compare_x);
    cout<<cpair2(a,2046);

    //测试用
    // point * a = new point[4];
    // for(int i = 0;i < 4;i++){
    //     scanf("%d,%d",&a[i].x,&a[i].y);
    // }
    // qsort(a,4,sizeof(point),compare_x);
    // cout<<cpair2(a,4);
}
