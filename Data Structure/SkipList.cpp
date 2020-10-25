#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#define LEVEL 8
using namespace std;

int random(int x){
    srand(time(NULL));
    return rand()%(x);
}
//定义节点
template<typename T>
class Node{
public:
    T value;
    vector<Node*> next;
    Node(const Node &v){this->value = v.value;}
    Node(T v);
};
template<typename T>
Node<T>::Node(T v)
{
    this->value = v;
    this->next.resize(LEVEL, NULL);
}

// 定义跳跃表
template<typename T>
class SkipList
{
public:
    Node<T>* head;
    // 最大层数
    int max_level;

    SkipList() {
        this->head = new Node<T>(-1);
        this->_prob = 0.5;
        this->max_level = LEVEL;
    }
    ~SkipList() {
        delete head;
    }
    
    // 插入
    void insert(T v);
    // 搜索
    void search(T v);
    // 删除
    bool erase(T v);
private:
    // 查找比v小的前序节点
    void _getPre(T v, vector<Node<T>*> &pre);
    // 划分级别
    int _level();
    // 定义可能性
    double _prob;
};

template<typename T>
int SkipList<T>::_level(){
    int lev = 0;
    srand(time(NULL));
    // 保证以(p)^i(1-p)的概率引入一个i级别的节点
    while((rand()%99)/(double)100 <= this->_prob)
    {
        lev++;
    }
    return (lev <= this->max_level)?lev:max_level;
}

template<typename T>
void SkipList<T>::_getPre(T v, vector<Node<T>*> &pre){
    Node<T> *p = this->head;
    // 循环，最后一层（level=0）一定能找到
    for (int i = LEVEL - 1; i >= 0; i --) {
        while (p->next[i] && p->next[i]->value < v) {
            p = p->next[i];
        }
        pre[i] = p;
    }
}
template<typename T>
void SkipList<T>::insert(T v) {
    // 找到比v小的前序节点
    vector<Node<T>*> pre(LEVEL);
    this->_getPre(v, pre);
    Node<T> *obj = new Node<T>(v);

    // level为i的概率为：p^i * (1-p)
    int level = _level();
    
    for (int i = 0; i <= level; i ++) {
        obj->next[i] = pre[i]->next[i];
        pre[i]->next[i] = obj;
    }
    
}
// 查找
template<typename T>
void SkipList<T>::search(T v) {
    // 找到比v小的前一个节点
    vector<Node<T>*> pre(LEVEL);
    this->_getPre(v, pre);

    Node<T> *obj = pre[0]->next[0];
    if(obj && obj->value == v){
        cout<<"Found "<<v<<"!"<<endl;;
    }
    else{
        cout<<"Not Found "<<v<<"!"<<endl;
    }
    return;
}

template<typename T>
bool SkipList<T>::erase(T v) {
    // 找到比v小的前一个节点
    vector<Node<T>*> pre(LEVEL);
    this->_getPre(v, pre);

    Node<T> *obj = pre[0]->next[0];

    if (!obj || obj->value != v) {
        return false;
    }
    
    for (int i = 0; i < LEVEL && pre[i]->next[i] == obj; i ++) {
        pre[i]->next[i] = obj->next[i];
    }

    delete obj;

    return true;
}

int main()
{
    SkipList<int> *skiplist = new SkipList<int>();

    skiplist->insert(1);
    skiplist->insert(3);
    skiplist->insert(2);
    // 能找到1，还在链表中
    skiplist->search(1);

    skiplist->erase(1);
    // 找不到1，因为已经删了
    skiplist->search(1);
    return 0;
}
