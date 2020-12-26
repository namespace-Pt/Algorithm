#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Node{
    int freq;
    char word;
    Node* left;
    Node* right;
    Node(char c,int x){
        word = c;
        freq = x;
        left = nullptr;
        right = nullptr;
    }
    Node(const Node& node){
        word = node.word;
        freq = node.freq;
        left = node.left;
        right = node.right;
    }
    bool operator < (const Node& a) const
    {
        return freq > a.freq;
    }
};

struct tmp2
{
    bool operator() (Node * a, Node * b) 
    {
        return a->freq > b->freq;
    }
};

Node* huffman(priority_queue<Node*,vector<Node *>, tmp2> queue){
    int max = queue.size();
    for(int i = 0; i < max - 1; i++){
        Node * tmp1 = queue.top();
        queue.pop();

        Node * tmp2 = queue.top();
        queue.pop();

        Node * new_node = new Node('\0',tmp1->freq + tmp2->freq);
        new_node->left = tmp1;
        new_node->right = tmp2;

        queue.push(new_node);
    }
    return queue.top();
}

void print_huffman_code(Node* top, vector<int> encode){
    if(top->left){
        encode.push_back(0);
        print_huffman_code(top->left,encode);
        encode.pop_back();
    }
    if(top->right){
        encode.push_back(1);
        print_huffman_code(top->right,encode);
        encode.pop_back();
    }
    if(top->word){
        cout<<top->word;
        for(int i = 0;i < encode.size();i ++){
            cout<<encode[i];
        }
        cout<<'\n';
    }
}

int main(){

    vector<int> encode;
    priority_queue<Node*,vector<Node *>, tmp2> d;
    
    int length = 0;
    int tmp = 0;
    char c = '\0';
    cout << "please type in number of words to encode:";
    cin >> length;
    for(int i = 0; i<length; i++){
        cout<<"word NO."<<i<<" is:";
        cin>>c;
        cout<<"frequency of "<<c<<" is:";
        cin>>tmp;

        Node *n = new Node(c,tmp);
        d.push(n);
    }
    Node* root = huffman(d);
    print_huffman_code(root,encode);
        
}