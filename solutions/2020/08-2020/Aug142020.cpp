#include <iostream>
using namespace std;

/* 
Implement a class for a stack that supports all the regular functions (push, pop) and an additional 
function of max() which returns the maximum element in the stack (return None if the stack is empty). 
Each method should run in constant time.
*/

/*
We can just use a modified stack struct with max for each element. Update with push.
*/

typedef struct Node* Stack;
struct Node {
	int val;
	int max;
	Node *rest;
};

void push(Stack *s, int v) {
	Stack newStack = new Node;
	newStack->val = v;
	newStack->max = *s==NULL? v : max(v, (*s)->max);
	newStack->rest = *s==NULL? NULL : *s;
	*s = newStack;
}

int pop(Stack *s) {
	if (*s == NULL) return -1;
	int ans = (*s)->val;
	Stack temp = *s;
	*s = (*s)->rest;
	delete temp;
	return ans;
}

int max(Stack *s) {
	return *s==NULL? -1 : (*s)->max;
}

int main(int argc, char **argv) {
	Stack s = NULL;
	push(&s, 5);
	push(&s, 7);
	push(&s, 1);
	push(&s, 6);
	push(&s, 8);
	std::cout << max(&s) << '\n';
	std::cout << pop(&s) << '\n';
	std::cout << max(&s) << '\n';
	std::cout << pop(&s) << '\n';
	std::cout << pop(&s) << '\n';
	std::cout << pop(&s) << '\n';
	std::cout << max(&s) << '\n';
	std::cout << pop(&s) << '\n';
	std::cout << pop(&s) << '\n';
	std::cout << pop(&s) << '\n';
	std::cout << max(&s) << '\n';
	return 0;
}
