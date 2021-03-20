#include <iostream>
#include <unordered_map>
using namespace std;

/*
Given a linked list, remove all duplicate values from the linked list.

ex.
list = 1 -> 2 -> 3 -> 3 -> 4
return 1 -> 2 -> 4
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
    void print() {
        cout << val << " -> ";
        if (next == nullptr) {
            cout << "NULL\n";
        } else next->print();
    }
};

/* APPROACH 1: map values in hash table with [k,v] = [node value, freq]. Then,
iterate through linked list and remove nodes while decrementing counts in table.
O(N) time + space */
Node removeDuplicatesFromLinkedList(Node list) {
    if (list == nullptr) return list;
    Node head = list;
    Node cur = list;
    unordered_map<int, int> map;
    while (cur != nullptr) {
        if (map.find(cur->val) == map.end()) {
            map[cur->val] = 0;
        }
        map[cur->val]++;
        cur = cur->next;
    }
    Node prev = head;
    cur = head->next;
    while (cur != nullptr) {
        if (map[cur->val] > 1) {
            prev->next = cur->next;
            map[cur->val]--;
        } else prev = cur;
        cur = cur->next;
    }
    return head;
}

int main(int argc, char **argv) {
    Node list = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(3, new ListNode(4)))));
    removeDuplicatesFromLinkedList(list)->print();
    return 0;
}
