#include<iostream>
#include<vector>
using namespace std;

# define MAX 10

class Sort_N{
public:
    Sort_N(){};

    void count_sort(vector<int> &l){
        int count[MAX+1] = {0};
        int n = l.size();
        int *res = new int[n];

        // given the range of elements 1~MAX, then count the appearance of each value in l
        for(int i = 0;i < n;i++){
            count[l[i]] += 1;
        }
        // get the index next to the last appearance of i
        for(int i = 1;i < MAX+1;i++){
            count[i+1] += count[i];
        }

        // unstable, the order of identical values is inverted
        // for(int i = 0;i < n;i++){
        //     res[count[l[i]]-- -1] = l[i];
        // }

        // stable
        for(int i = n-1;i >= 0;i--){
            res[count[l[i]]-- -1] = l[i];
        }

        l.clear();
        for(int i = 0;i < n;i++){
            l.push_back(res[i]);
        }
    }


    void radix_sort(vector<int> &l){
        
    }
};

int main(){
    vector<int> l;
    l.push_back(3);
    l.push_back(10);
    l.push_back(8);
    l.push_back(7);
    l.push_back(5);
    l.push_back(1);
    l.push_back(2);

    Sort_N s;
    // s.heap_sort(l);
    s.count_sort(l);

    for(auto i:l){
        cout<<i<<",";
    }
}