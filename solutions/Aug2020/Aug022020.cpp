/* 
You are given two linked-lists representing two non-negative integers. The digits are stored in 
reverse order and each of their nodes contain a single digit. Add the two numbers and return it 
as a linked list.

Example:
Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807. 
*/

#include <iostream>
using namespace std;

typedef struct ListNode* Node;

struct ListNode {
	int val;
	Node next;
};

Node* createList() {
	Node* h = (Node*) malloc(sizeof(Node*));
	*h = NULL;
	return h;
}

bool isEmpty(Node* l) {
	return *l == NULL;
}

void add(Node *l, int val) {
	Node newNode = (Node) malloc(sizeof(Node));
	newNode->val = val;
	newNode->next = NULL;
	if (isEmpty(l)) {
		*l = newNode;
		return;
	}
	Node ptr = *l;
	while (ptr->next != NULL) ptr = ptr->next;
	ptr->next = newNode;
}

void insertFront(Node *l, int val) {
	Node newNode = (Node) malloc(sizeof(Node));
	newNode->val = val;
	newNode->next = *l;
	*l = newNode;
}

void print(Node *l) {
	Node ptr = *l;
	while (ptr != NULL) {
		std::cout << ptr->val << " ";
		ptr = ptr->next;
	}
	std::cout << '\n';
}

/* 
We can walk through the two linked lists and track carry. I will assume l1 and l2 are non-empty. 
Runtime is O(max(|l1|,|l2|)^2) because add function has to walk through ans each time.
*/
Node* findSum(Node* l1, Node* l2) {
	Node ptr1 = *l1;
	Node ptr2 = *l2;
	Node* ans = createList();
	int carry = 0;
	while (ptr1 != NULL && ptr2 != NULL) {
		int sum = ptr1->val + ptr2->val + carry;
		add(ans, sum%10);
		carry = sum>=10? 1 : 0;
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}
	while (ptr1 != NULL) {
		int sum = ptr1->val + carry;
		add(ans, sum%10);
		carry = sum>=10? 1 : 0;
		ptr1 = ptr1->next;
	}
	while (ptr2 != NULL) {
		int sum = ptr2->val + carry;
		add(ans, sum%10);
		carry = sum>=10? 1 : 0;
		ptr2 = ptr2->next;
	}
	if (carry == 1) add(ans, 1);
	return ans;
}

int main(int argc, char **argv) {
	Node *l1 = createList();
	add(l1, 2);
	add(l1, 4);
	add(l1, 3);
	add(l1, 9);
	add(l1, 9);
	print(l1);
	Node *l2 = createList();
	add(l2, 5);
	add(l2, 6);
	add(l2, 9);
	print(l2);
	print(findSum(l1,l2));
	return 0;
}
