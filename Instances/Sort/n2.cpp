#include<iostream>
#include<vector>
using namespace std;

class Sort_N2{
public:
    Sort_N2(){};
    void bubble_sort(vector<int> &l){
        int n = l.size();
        int tmp = 0;
        bool changed = false;
        for(int i = 0;i < n;i++){
            changed = false;
            for(int j = 0;j < n-i-1;j++){
                if(l[j] > l[j+1]){
                    tmp = l[j+1];
                    l[j+1] = l[j];
                    l[j] = tmp;
                    changed = true;
                }
            }
            if(!changed){
                break;
            }
        }
    }

    void insert_sort(vector<int> &l){
        int n = l.size();
        int pivot = 0;
        int i = 1;
        int j = 0;
        for(;i < n;i++){
            pivot = l[i];
            for(j = i-1;j >= 0;j--){
                if(l[j] > pivot){
                    l[j+1] = l[j];
                }
                else{
                    break;
                }
            }
            l[j+1] = pivot;
        }
    }
};
int main(){
    vector<int> l;
    l.push_back(3);
    l.push_back(9);
    l.push_back(8);
    l.push_back(7);
    l.push_back(5);
    l.push_back(-1);
    l.push_back(-2);

    Sort_N2 s;
    // s.bubble_sort(l);
    s.insert_sort(l);
    for(auto i:l){
        cout<<i;
    }
}
