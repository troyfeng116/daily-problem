#include <iostream>
using namespace std;

/*
You are given a doubly linked list. Determine if it is a palindrome.
*/

typedef struct ListNode *Node;
struct ListNode {
    char val;
    ListNode *prev;
    ListNode *next;
    ListNode(char v) {
        val = v;
        prev = NULL, next = NULL;
    }
};
void insert_front(Node *head, int v) {
    Node newHead = new ListNode(v);
    newHead->next = *head;
    (*head)->prev = newHead;
    *head = newHead;
}

/* APPROACH 1: Set r pointer to end of list, move l and r towards each other. O(N) */
bool isPalindrome(Node head) {
    if (head == NULL) return true;
    Node l = head, r = head;
    while (r->next != NULL) r = r->next;
    while (l != r) {
        if (l->val != r->val) return false;
        l = l->next;
        if (l == r) return true;
        r = r->prev;
    }
    return true;
}

int main(int argc, char **argv) {
    Node head = new ListNode('a');
    insert_front(&head, 'b');
    insert_front(&head, 'c');
    insert_front(&head, 'b');
    insert_front(&head, 'a');
    std::cout << isPalindrome(head) << '\n';
    return 0;
}
