#include<iostream>
#include<limits.h>
#include<vector>
using namespace std;

// 定义索引孩子和双亲的函数
// 整个题目的索引从1开始，然而vector中的索引从0开始，因此所有索引最终在程序中需要减一
int left(int i){
    return 2*i;
}

int right(int i){
    return 2*i + 1;
}
// 注意i为1时i/2会返回0，导致segmentation fault
int parent(int i){
    if(i = 1) return 1;
    return i/2;
}

// 模板类定义优先队列中的节点
template<typename T>
class Node{
public:
    // 方便起见直接用int作为索引key，要不然得重载很多内容
    int key;
    // 模板类作为值
    T value;

    // 默认构造函数，这里的value其实没有用T
    Node(){key = -1;}
    // 构造函数
    Node(int key,T value);
    // 复制构造函数，这个其实没有用到
    Node(const Node &n);
};

template<typename T>
class Priority_Queue{
public:
    // 构造函数1，可以直接传入vector
    Priority_Queue(vector<Node<T>*>A,int length);

    // 构造函数2，默认构造函数，初始化时不用管vector
    Priority_Queue(){this->_size = 0;}

    // 用vector保存堆数组，方便动态插入，否则得自己写链表
    vector<Node<T>*> A;
    
    // 返回key最小的元素指针
    Node<T>* maximum();
    // 提出key最小的元素
    Node<T>* extract_max();
    // 插入新元素
    void insert(T key,T value);
    // 减小元素的key值
    void incr_key(int i,int k);

protected:
    // 构造堆的基本操作单元
    void _heapify(int i);
    // 保存堆的元素个数
    int _size;
};


// 直接继承最小优先级队列，从INT_MIN开始让新进入元素的优先级（key）逐个升高，实现队列（先进先出）
template<typename T>
class Queue:public Priority_Queue<T>{
public:
    Queue():Priority_Queue<T>(){_key = INT_MIN;}
    // 先进先出队列
    void insert(T value);
    Node<T>* pop();
    
private:
    int _key;
};

// 继承最小优先级队列，从INT_MAX开始让新进入元素的优先级（key）逐个降低，实现栈（先进先出）
template<typename T>
class Stack:public Priority_Queue<T>{
public:    
    Stack():Priority_Queue<T>(){_key = INT_MAX;}
    // 先进后出栈
    void insert(T value);
    Node<T>* pop();
private:
    int _key;
};

template<typename T>
Node<T>::Node(int key,T value){
    this->key = key;
    this->value = value;
}
template<typename T>
Node<T>::Node(const Node &n){
    this->key = n.key;
    this->value = n.value;
}
template<typename T>
Priority_Queue<T>::Priority_Queue(vector<Node<T>*>A,int length){
    this->A = A;
    this->_size = length;
}

template<typename T>
void Priority_Queue<T>::_heapify(int i){
    // 获取待操作节点的左右孩子
    // O(1)
    int l = left(i);
    int r = right(i);
    int largest = -1;

    // 如果比左右孩子的优先级高则交换
    if(l <= this->_size && A[l-1]->key < A[0]->key){
        largest = l;
    }
    else
    {
        largest = i;
    }
    if(r <= this->_size && A[r-1]->key < A[largest-1]->key){
        largest = r;
    }
    if(largest != i){
        Node<T> *tmp = A[largest-1];
        A[largest-1] = A[i-1];
        A[i-1] = tmp;
        // 左右子树中最多有2n/3个节点，因此
        // T(n) = T(2n/3) + O(1)
        // O(lgn)
        _heapify(largest);
    }
}

// 直接取数组头
// O(1)
template<typename T>
Node<T> *Priority_Queue<T>::maximum(){
    return A[0];
}

// 取完头需要把尾置换上来，然后重新维护堆，堆最多有lgn（下界）层
// O(lgn)
template<typename T>
Node<T> *Priority_Queue<T>::extract_max(){
    if(this->_size < 1){
        cout<<"Underflow";
        Node<T>* result = new Node<T>();
        return result;
    }
    Node<T> *head = A[0];
    A[0] = A[_size-1];
    this->_size -= 1;
    _heapify(1);
    return head;
}

// 调整key值
// O(lgn)
template<typename T>
void Priority_Queue<T>::incr_key(int i,int key){
    // 赋值计算
    // O(1)
    int p = parent(i);
    if(key > A[i-1]->key){
        cout<<"new key is larger";
        return;
    }
    A[i-1]->key = key;

    // 最多lgn（下界）层
    // O(lgn)
    while (i > 0 && A[p-1]->key > A[i-1]->key)
    {
        Node<T> *tmp = A[p-1];
        A[p-1] = A[i-1];
        A[i-1] = tmp;
        i = p;
        // 注意更新parent
        p = parent(i);
    }
}

// 插入节点
// O(lgn)
template<typename T>
void Priority_Queue<T>::insert(T key,T value){
    // 初始化key为最大
    Node<T> *node = new Node<T>(INT_MAX,value);
    // 直接vector插入尾部就行
    A.push_back(node);
    _size ++;
    // 调整key
    // O(lgn)
    incr_key(this->_size,key);
}

template<typename T>
void Queue<T>::insert(T value){
    Node<T> *node = new Node<T>(INT_MAX,value);
    this->A.push_back(node);
    this->_size ++;
    this->incr_key(this->_size,_key);
    _key ++;
}

template<typename T>
Node<T>* Queue<T>::pop(){
    return this->extract_max();
}

template<typename T>
void Stack<T>::insert(T value){
    Node<T> *node = new Node<T>(INT_MAX,value);
    this->A.push_back(node);
    this->_size ++;
    this->incr_key(this->_size,_key);
    _key --;
}
template<typename T>
Node<T>* Stack<T>::pop(){
    return this->extract_max();
}


int main(){

    // 按插入方法构造，比较符合实际场景    
    Priority_Queue<int> *p_queue = new Priority_Queue<int>();
    p_queue->insert(30,1);
    p_queue->insert(15,9);
    p_queue->insert(20,7);
    p_queue->insert(2,3);

    // 每次取最大，直到取完
    Node<int> * a = p_queue->extract_max();
    cout<<"key:"<<a->key<<" value:"<<a->value<<endl;
    a = p_queue->extract_max();
    cout<<"key:"<<a->key<<" value:"<<a->value<<endl;
    a = p_queue->extract_max();
    cout<<"key:"<<a->key<<" value:"<<a->value<<endl;
    a = p_queue->extract_max();
    cout<<"key:"<<a->key<<" value:"<<a->value<<endl;

    // 队列，先进先出
    Queue<int> *queue = new Queue<int>();
    queue->insert(10);
    queue->insert(20);
    queue->insert(50);
    cout<<queue->pop()->value<<endl;
    cout<<queue->pop()->value<<endl;
    cout<<queue->pop()->value<<endl;

    // 栈，先进后出 
    Stack<char> *stack = new Stack<char>();
    stack->insert('a');
    stack->insert('b');
    stack->insert('c');
    cout<<stack->pop()->value<<endl;
    cout<<stack->pop()->value<<endl;
    cout<<stack->pop()->value;
    
    return 0;
}