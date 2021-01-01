#include <iostream>
using namespace std;

/*
Given a linked list, swap the position of the 1st and 2nd node, then swap the position of the 
3rd and 4th node etc.
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

void printList(Node head) {
    Node cur = head;
    while (cur != nullptr) {
        std::cout << cur->val << " --> ";
        cur = cur->next;
    }
    std::cout << "NULL\n";
}

/* APPROACH 1: given 1->2->3->4, to swap 2 and 3, we need to store 3's pointer to 4 and 1's
pointer to 2, i.e. prev and next pointers in addition to two swaps. O(N) */
Node swapEveryTwoNodes(Node head) {
    if (head == nullptr) return nullptr;
    Node dummy = new ListNode(0, head);
    Node prev = dummy;
    Node cur = head;
    while (cur != nullptr && cur->next != nullptr) {
        Node n1 = cur;
        Node n2 = n1->next;
        Node next = n2->next;
        n2->next = n1;
        n1->next = next;
        prev->next = n2;
        prev = n1;
        cur = next;
    }
    return dummy->next;
}

int main(int argc, char **argv) {
    Node head = new ListNode(2, new ListNode(1, new ListNode(4, new ListNode(3, new ListNode(5, new ListNode(6))))));
    Node res = swapEveryTwoNodes(head);
    printList(res);
    return 0;
}
