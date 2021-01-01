#include <iostream>
using namespace std;

/*
Given a singly-linked list, reverse the list. This can be done iteratively or recursively. Can you get 
both solutions?

Example:
Input: 4 -> 3 -> 2 -> 1 -> 0 -> NULL
Output: 0 -> 1 -> 2 -> 3 -> 4 -> NULL
*/

/*  */

typedef struct Node *ListNode;

struct Node {
	int val;
	struct Node* next;
};

void add(ListNode *list, int v) {
	ListNode newNode = new Node;
	newNode->val = v;
	newNode->next = NULL;
	if (*list == NULL) {
		*list = newNode;
		return;
	}
	ListNode cur = *list;
	while (cur->next != NULL) cur = cur->next;
	cur->next = newNode;
}

void printList(ListNode *list) {
	ListNode cur = *list;
	if (cur == NULL) {
		std::cout << "null\n";
		return;
	}
	std::cout << cur->val;
	cur = cur->next;
	while (cur != NULL) {
		std::cout << " -> " << cur->val;
		cur = cur->next;
	}
	std::cout << " -> null\n";
}

void reverseLinkedList(ListNode *list) {
	/* Head of reverse linked list. */
	ListNode head = NULL;
	/* Keep pointer to next node in old list. */
	ListNode cur = *list;
	while (cur != NULL) {
		/* Store next node in old list. */
		ListNode next = cur->next;
		/* Add this node to front of new list. */
		cur->next = head;
		/* Set head pointer of new list to new front. */
		head = cur;
		/* Move cur to next node in old list. */
		cur = next;
	}
	/* Set list pointer to head of reversed list. */
	*list = head;
}

int main(int argc, char **argv) {
	ListNode list = NULL;
	for (int x = 20; x >= 0; x--) {
		add(&list,x);
	}
	printList(&list);
	reverseLinkedList(&list);
	printList(&list);
	return 0;
}
