#include <iostream>
using namespace std;

/*
Given a non-empty array where each element represents a digit of a non-negative integer, add one to the 
integer. The most significant digit is at the front of the array and each element in the array contains 
only one digit. Furthermore, the integer does not have leading zeros, except in the case of the number 
'0'.

Example:
Input: [2,3,4]
Output: [2,3,5]
*/

typedef struct ListNode *Node;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int v) {
        val = v;
        next = NULL;
    }
};
void insert(Node list, int v) {
    if (list == NULL) return;
    while (list->next != NULL) {
        list = list->next;
    }
    list->next = new ListNode(v);
}
void print(Node list) {
    while (list != NULL) {
        std::cout << list->val << " -> ";
        list = list->next;
    }
    std::cout << "NULL\n";
}
Node reverse(Node list) {
    Node cur = list;
    Node newHead = NULL;
    while (cur != NULL) {
        Node next = cur->next;
        cur->next = newHead;
        newHead = cur;
        cur = next;
    }
    return newHead;
}

/* APPROACH 1: Convert to int, add one, convert to LL. O(N) */
Node addOne(Node list) {
    int num = 0;
    while (list != NULL) {
        num *= 10;
        num += list->val;
        list = list->next;
    }
    num++;
    Node ans = new ListNode(num % 10);
    Node cur = ans;
    num /= 10;
    while (num != 0) {
        cur->next = new ListNode(num%10);
        cur = cur->next;
        num /= 10;
    }
    ans = reverse(ans);
    return ans;
}

/* APPROACH 2: Reverse, add 1, reverse. O(N) */
Node addOne2(Node list) {
    Node reversed = reverse(list);
    Node cur = reversed;
    while (cur->next != NULL && cur->val == 9) {
        cur->val = 0;
        cur = cur->next;
    }
    if (cur->next == NULL && cur->val == 9) {
        cur->val = 0;
        cur->next = new ListNode(1);
    }
    else cur->val++;
    return reverse(reversed);
}

int main(int argc, char **argv) {
    Node head = new ListNode(1);
    insert(head, 2);
    insert(head, 9);
    std::cout << "ORIGINAL NUM: ";
    print(head);

    std::cout << "APPROACH 1 TESTING: ";
    print(addOne(head));
    std::cout << "APPROACH 2 TESTING: ";
    print(addOne2(head));
    return 0;
}
