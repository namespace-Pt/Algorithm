#include<iostream>
#include<vector>
#include<time.h>
using namespace std;

class Sort_NlgN{
public:
    Sort_NlgN(){}

    // exchange the top of the heap (biggest elements in the array), then re-heapify at the first element
    void heap_sort(vector<int> &l){
        _build_heap(l);

        int tmp = 0;
        int n = l.size();
        for(int i = n-1;i > 0;i--){
            tmp = l[0];
            l[0] = l[i];
            l[i] = tmp;

            _heapify(l,0,i);
        }
    }

    void quick_sort(vector<int> &l, int start, int end){
        if(end > start){
            int pivot = _partition(l, start, end);
            quick_sort(l, start, pivot - 1);
            quick_sort(l, pivot + 1, end);
        }
    }

    void merge_sort(vector<int> &l){

    }

private:
    // subroutine for heap_sort
    // recursively maintain the property of max-heap, which is the parent node is bigger than any child
    void _heapify(vector<int> &l, int idx, int n){
        int left = 2*(idx + 1) - 1;
        int right = 2*(idx + 1);
        int largest = idx;

        if(left < n && l[left] > l[largest]){
            largest = left;
        }
        if(right < n && l[right] > l[largest]){
            largest = right;
        }
        if(largest != idx){
            int tmp = l[idx];
            l[idx] = l[largest];
            l[largest] = tmp;
            _heapify(l, largest, n);
        }
    }
    // subroutine for heap_sort
    // from n/2, all nodes are leaves, so only heapify from n/2 to 0
    void _build_heap(vector<int> &l){
        for(int i = l.size()/2;i >= 0;i--){
            _heapify(l, i, l.size());
        }
    }


    // subroutine for quick_sort
    int _partition(vector<int> &l, int start, int end){
        // int pivot = l[end];

        // random select a pivot, making the expectation to be nlgn
        int idx = rand() % (end - start + 1) + start;
        int pivot = l[idx];
        swap(l[idx], l[end]);

        int i = start;
        int j = start;
        int tmp = 0;
        // skip l[end] because it is pivot
        for(j;j < end;j ++){
            if(l[j] < pivot){
                swap(l[i++],l[j]);
            }
        }
        swap(l[i], l[end]);
        return i;
    };
};

int main(){
    srand(time(NULL));

    vector<int> l;
    l.push_back(3);
    l.push_back(9);
    l.push_back(8);
    l.push_back(7);
    l.push_back(5);
    l.push_back(-1);
    l.push_back(-2);

    Sort_NlgN s;
    // s.heap_sort(l);
    s.quick_sort(l,0,l.size() - 1);

    for(auto i:l){
        cout<<i<<",";
    }
}