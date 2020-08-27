#include <iostream>
using namespace std;

/*
You are given a singly linked list and an integer k. Return the linked list, removing the k-th 
last element from the list.

Try to do it in a single pass and using constant space.
*/

/*
QUESTIONS: valid k? (i.e. <= length) Will assume not necessarily
*/

typedef struct Node *ListNode;
struct Node {
	int val;
	Node *next;
};
void insert(ListNode *list, int v) {
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
void print(ListNode list) {
	while (list != NULL) {
		std::cout << list->val << " --> ";
		list = list->next;
	}
	std::cout << "NULL\n";
}

/*
APPROACH 1: Lagging pointer. Start one pointer, and move to (k+1)'th node. Then start another
pointer k nodes behind. When the fast pointer reaches the end, we want the slow pointer to be 
pointing to the (k+1) to last node.
*/
ListNode removeKthLast(ListNode *list, int k) {
	ListNode dummy = new Node;
	dummy->val = 0;
	dummy->next = *list;
	ListNode fast = ;
	int i = 0;
	while (fast != NULL && i <= k) {
		fast = fast->next;
		i++;
	}
	if (fast == NULL || k == 0) return *list;
	std::cout << fast->val << '\n';
	ListNode slow = dummy;
	while (fast != NULL) {
		fast = fast->next;
		slow = slow->next;
	}
	ListNode toRemove = slow->next;
	slow->next = toRemove->next;
	delete toRemove;
	return *list;
}

int main(int argc, char **argv) {
	ListNode list = NULL;
	for (int v = 1; v <= 5; v++) insert(&list, v);
	print(list);
	print(removeKthLast(&list, 4));
	return 0;
}
