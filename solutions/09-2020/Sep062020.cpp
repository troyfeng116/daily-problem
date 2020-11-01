#include <iostream>
using namespace std;

/*
You are given an array of k sorted singly linked lists. Merge the linked lists into a single sorted linked 
list and return it.
*/

/* Linked list definition */
typedef struct ListNode *Node;
struct ListNode {
    int val;
    ListNode *next;
};
void insert(Node *list, int val) {
    Node newNode = new ListNode;
    newNode->val = val;
    newNode->next = NULL;
    if (*list == NULL) *list = newNode;
    else {
        Node cur = *list;
        while (cur->next != NULL) cur = cur->next;
        cur->next = newNode;
    }
}
void print(Node list) {
    while (list != NULL) {
        std::cout << list->val << " --> ";
        list = list->next;
    }
    std::cout << "null\n";
}

/* APPROACH 1: Divide and conquer a la mergeSort. Should run in O(N log k). */
Node merge(Node l1, Node l2) {
    Node ans = NULL;
    while (l1 != NULL && l2 != NULL) {
        if (l1->val < l2->val) {
            insert(&ans, l1->val);
            l1 = l1->next;
        }
        else {
            insert(&ans, l2->val);
            l2 = l2->next;
        }
    }
    while (l1 != NULL) {
        insert(&ans, l1->val);
        l1 = l1->next;
    }
    while (l2 != NULL) {
        insert(&ans, l2->val);
        l2 = l2->next;
    }
    return ans;
}
Node aux(Node *lists, int l, int r) {
    if (l > r) return NULL;
    if (l == r) return lists[l];
    int m = (l+r)/2;
    Node l1 = aux(lists, l, m);
    Node l2 = aux(lists, m+1, r);
    return merge(l1, l2);
}
Node mergeLists(Node *lists, int k) {
    return aux(lists, 0, k-1);
}

int main(int argc, char **argv) {
/* LINKED LIST TESTING */
    Node l1 = NULL;
    insert(&l1, 1);
    insert(&l1, 3);
    insert(&l1, 12);
    Node l2 = NULL;
    insert(&l2, -1);
    insert(&l2, 5);
    Node l3 = NULL;
    insert(&l3, 0);
    insert(&l3, 4);
    insert(&l3, 10);
    insert(&l3, 11);
    Node l4 = NULL;
    insert(&l4, 2);
    insert(&l4, 6);
    insert(&l4, 7);
    Node l5 = NULL;
    print(l1);
    print(l2);
    print(l3);
    print(l4);
    print(l5);
/* MERGE K LISTS TESTING */
    int k = 5;
    Node lists[] = {l1,l2,l3,l4,l5};
    print(mergeLists(lists, k));
    return 0;
}
