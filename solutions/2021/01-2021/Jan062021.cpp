#include <iostream>
using namespace std;

/*
Given a sorted linked list of integers, remove all the duplicate elements in the linked list so that
all elements in the linked list are unique.
*/

typedef struct ListNode *Node;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int v) {
        val = v;
        next = nullptr;
    }
    ListNode(int v, ListNode *n) {
        val = v;
        next = n;
    }
};
void print(Node list) {
    Node cur = list;
    while (cur != nullptr) {
        std::cout << cur->val << " -> ";
        cur = cur->next;
    }
    std::cout << "NULL\n";
}

/* APPROACH 1: Simple in-place pointer fiddling since sorted. Track current value in list.
While nodes are equal, skip over and then assign cur->next to next node that is not equal
and repeat. O(N) */
Node removeDuplicates(Node list) {
    Node cur = list;
    while (cur != nullptr && cur->next != nullptr) {
        if (cur->val == cur->next->val) {
            cur->next = cur->next->next;
        } else cur = cur->next;
    }
    return list;
}

int main(int argc, char **argv) {
    Node list = new ListNode(1, new ListNode(2, new ListNode(2, new ListNode(3, new ListNode(3)))));
    Node res = removeDuplicates(list);
    print(res);
    return 0;
}
