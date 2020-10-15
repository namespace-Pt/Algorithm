#include<random>
#include<iostream>
#include<limits.h>
#include <ctime>
#include<vector>
using namespace std;

int random(int x){
    srand(time(NULL));
    return rand()%(x);
}
int main(){
    vector<int> a;
    a.push_back(1);
    cout<<(a.size());
}