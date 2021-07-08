#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int plus = 0;
        int res = 0;
        ListNode * head = new ListNode();
        ListNode * node = head;

        ListNode* node_new = head;
        while(l1){
            node = node_new;

            cout<<l1->val<<l2->val;
            res = l1->val + l2->val + plus;
            if(res > 9){
                res = res-10;
                node->val = res;
                plus = 1;
            }
            else{
                node->val = res;
                plus = 0;
            }

            node_new = new ListNode();
            node->next = node_new;

            l1 = l1->next;
            l2 = l2->next;
        }
        if(plus > 0){
            node_new->val = 1;
        }
        else{
            node->next = nullptr;
            delete node_new;
        }
        return head;
    }
};

int main(){
    ListNode * l13 = new ListNode(3);
    ListNode * l12 = new ListNode(4,l13);
    ListNode * l1 = new ListNode(2,l12);

    ListNode * l23 = new ListNode(4);
    ListNode * l22 = new ListNode(6,l23);
    ListNode * l2 = new ListNode(5,l22);

    Solution x;
    ListNode* res = x.addTwoNumbers(l1,l2);
    while(res){
        cout<<res->val;
        res = res->next;
    }
}