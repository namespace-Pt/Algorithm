#include<random>
#include<iostream>
#include<limits.h>
#include <ctime>
#include<vector>
#include<fstream>
#include<string>
#include<map>

using namespace std;

int ** a = nullptr;

int random(int x){
    srand(time(NULL));
    return rand()%(x);
}

int myEqual(unsigned int * a, unsigned int * b, unsigned int n){
    for(unsigned int i = 0;i < n;i ++){
        if (a[i] != b[i])
        {
            return 0;
        }

    }
    return 1;
}

void print(){
    for(int i = 0;i < 10;i ++){
        for(int j = 0;j < 10;j++){
            cout<<a[i][j]<<',';
        }
    }
}

int main(){
    // <map>
    // map<int,int> a;
    // a[2]++;
    // a[3] = 0;
    // auto iter = a.find(2);
    // cout<<iter->first<<','<<(++iter)->first;
    
    // <vector>
    // vector<vector<int>> a;
    // vector<int> x;
    // x.push_back(3);
    // x.push_back(2);
    // a.push_back(x);
    // x[1] = -1;
    // a.push_back(x);
    // for(auto iter = a.begin();iter != a.end();iter ++){
    //     for(int i = 0;i < 2;i++){
    //         cout<<(*iter)[i]<<',';
    //     }
    // }
    // int a = sizeof(vector<unsigned int>);
    // int b = sizeof(unsigned int);
    // cout<<a<<','<<b;

    // <array>
    // unsigned int a[2] = {0,1};
    // unsigned int b[2] = {0,2};
    // unsigned int c[2] = {0,1};
    // cout<< myEqual(b,c,2) << myEqual(a,c,2);

    // memory
    int * b = new int [10];
    a = new int * [10];
    int idx = 0;
    for(int i = 0;i < 10;i ++){
        b[i] = i;
    }
    a[idx++] = b;
    // memcpy (a[idx++], b, sizeof(unsigned int)*10);
    while(idx < 10){
        b = new int [10];
        for(int j = 0;j < 10;j++){
            b[j] = 20;
        }
        a[idx++] = b;
    }
    print();
    cout<<"fuck";
    return 0;
}