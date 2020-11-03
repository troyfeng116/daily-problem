#include <iostream>
#include <unordered_set>
using namespace std;

/*
Given a linked list, determine if the linked list has a cycle in it. For notation purposes, we use an 
integer pos which represents the zero-indexed position where the tail connects to.

Example:
Input: head = [4,3,2,1,0], pos = 1.  
Output: true
*/

typedef struct ListNode *Node;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int v) {
        val = v;
        next = NULL;
    }
    ListNode (int v, ListNode *n) {
        val = v;
        next = n;
    }
};
void insert(Node head, Node n) {
    if (head == NULL) return;
    Node cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
}

/* APPROACH 1: Hash all visited nodes and check if any node is visited twice. O(N) time + space */
bool findLinkedListCycle(Node head) {
    Node cur = head;
    unordered_set<Node> visited;
    while (cur != NULL) {
        if (visited.count(cur) > 0) return true;
        visited.insert(cur);
        cur = cur->next;
    }
    return false;
}

/* APPROACH 2: Floyd cycle detection algorithm (tortoise and hare). O(N) time */
bool findLinkedListCycle2(Node head) {
    if (head == NULL) return false;
    Node slow = head;
    Node fast = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

int main(int argc, char **argv) {
    Node hasCycle = new ListNode(4);
    Node noCycle = new ListNode(4);
    for (int i = 3; i > 0; i--) {
        insert(hasCycle, new ListNode(i));
        insert(noCycle, new ListNode(i));
    }
    insert(hasCycle, new ListNode(0, hasCycle->next));
    insert(noCycle, new ListNode(0));

    std::cout << "APPROACH 1 TESTING: " << findLinkedListCycle(hasCycle) << " " << findLinkedListCycle(noCycle) << '\n';
    std::cout << "APPROACH 2 TESTING: " << findLinkedListCycle2(hasCycle) << " " << findLinkedListCycle2(noCycle) << '\n';
    return 0;
}
