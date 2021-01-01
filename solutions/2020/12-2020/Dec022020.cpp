#include <iostream>
using namespace std;

/*
Given a linked list and a number k, rotate the linked list by k places.
*/

/* QUESTION: Rotate left or rotate right? Will assume rotate left */

typedef struct ListNode *Node;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int v) {
        val = v;
        next = NULL;
    }
    ListNode(int v, ListNode *n) {
        val = v;
        next = n;
    }
};

void printList(Node head) {
    while (head != NULL) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "NULL\n";
}

/* APPROACH 1: Find length of linked list with two pointers, reduce k, and rotate. O(N) */
int getLength(Node head) {
    if (head == NULL) return 0;
    Node slow = head, fast = head;
    int len = 0;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        len++;
        slow = slow->next;
    }
    return fast == NULL ? len * 2 : len * 2 + 1;
}
Node rotateLinkedList(Node head, int k) {
    if (k == 0) return head;
    int length = getLength(head);
    if (length <= 1) return head;
    k = k % length;
    if (k == 0) return head;
    Node temp = head;
    for (int i = 0; i < k - 1; i++) {
        temp = temp->next;
    }
    Node newHead = temp->next;
    temp->next = NULL;
    temp = newHead;
    while (temp->next != NULL) temp = temp->next;
    temp->next = head;
    return newHead;
}

int main(int argc, char **argv) {
    Node head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
    Node res = rotateLinkedList(head, 302);
    printList(res);
    return 0;
}
