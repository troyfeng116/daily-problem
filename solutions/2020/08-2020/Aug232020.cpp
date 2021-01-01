#include <iostream>
using namespace std;

/*
You are given two singly linked lists. The lists intersect at some node. Find, and return 
the node. Note: the lists are non-cyclical.

Example:

A = 1 -> 2 -> 3 -> 4
B = 6 -> 3 -> 4

This should return 3 (you may assume that any nodes with the same value are the same node).
*/

/*
The back parts of the two lists are shared, meaning we can walk the lists in parallel starting
from the point at which the longer list has a remainder length equal to the shorter list.
*/

typedef struct Node* ListNode;
struct Node {
	int val;
	Node *next;
};

void insert(ListNode *list, int val) {
	ListNode newNode = new Node;
	newNode->val = val;
	newNode->next = NULL;
	if (*list == NULL) {
		*list = newNode;
		return;
	}
	ListNode cur = *list;
	while (cur->next != NULL) cur = cur->next;
	cur->next = newNode;
}
void insert(ListNode *list, ListNode newNode) {
	if (*list == NULL) {
		*list = newNode;
		return;
	}
	ListNode cur = *list;
	while (cur->next != NULL) cur = cur->next;
	cur->next = newNode;
}
void print(ListNode list) {
	ListNode cur = list;
	while (cur != NULL) {
		std::cout << cur->val << " -> ";
		cur = cur->next;
	}
	std::cout << " NULL\n";
}

int length(ListNode l) {
	int len = 0;
	while (l != NULL) {
		len++;
		l = l->next;
	}
	return len;
}
int findIntersection(ListNode list1, ListNode list2) {
	int len1 = length(list1);
	int len2 = length(list2);
	if (len1 > len2) {
		for (int i = 0; i < len1-len2; i++) list1 = list1->next;
	}
	else {
		for (int i = 0; i < len2-len1; i++) list2 = list2->next;
	}
	while (list1 != NULL && list1->val != list2->val) {
		list1 = list1->next;
		list2 = list2->next;
	}
	return list1 == NULL ? -1 : list1->val;
}

int main(int argc, char **argv) {
	ListNode list1 = NULL;
	insert(&list1, 1);
	insert(&list1, 2);

	ListNode list2 = NULL;
	insert(&list2, 6);

	ListNode shared = NULL;
	insert(&shared, 3);
	insert(&shared, 4);
	insert(&list1, shared);
	insert(&list2, shared);

	print(list1);
	print(list2);

	std::cout << findIntersection(list1, list2) << '\n';
	return 0;
}
