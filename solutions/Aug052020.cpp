#include <iostream>
using namespace std;

/*
Imagine you are building a compiler. Before running any code, the compiler must check that the 
parentheses in the program are balanced. Every opening bracket must have a corresponding closing 
bracket. We can approximate this using strings.

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the 
input string is valid.

An input string is valid if:
- Open brackets are closed by the same type of brackets.
- Open brackets are closed in the correct order.
- Note that an empty string is also considered valid.

Example:
Input: "((()))"
Output: True

Input: "[()]{}"
Output: True

Input: "({[)]"
Output: False
*/

typedef struct Node *Stack;

struct Node {
	char val;
	Node *next;
};

void push(Stack *s, char c) {
	Stack newNode = new Node;
	newNode->val = c;
	newNode->next = *s;
	*s = newNode;
}

char pop(Stack *s) {
	if (*s == NULL) return '#';
	char c = (*s)->val;
	Stack temp = *s;
	(*s) = (*s)->next;
	delete temp;
	return c;
}

bool isEmpty(Stack *s) {
	return *s == NULL;
}

bool validBrackets(string s) {
	Stack stack = NULL;
	for (int i = 0; i < s.length(); i++) {
		char c = s.at(i);
		if (c == '(' || c == '{' || c == '[') push(&stack, c);
		else if (c == ')') {
			if (pop(&stack) != '(') return false;
		}
		else if (c == '}') {
			if (pop(&stack) != '{') return false;
		}
		else if (c == ']') {
			if (pop(&stack) != '[') return false;
		}
		else {
			std::cout << "INVALID INPUT STRING\n";
			return false;
		}
	}
	return isEmpty(&stack);
}

int main(int argc, char **argv) {
	string s1 = "((()))";
	string s2 = "[()]{}";
	string s3 = "({[)]";
	std::cout << validBrackets(s1) << '\n';
	std::cout << validBrackets(s2) << '\n';
	std::cout << validBrackets(s3) << '\n';
	return 0;
}
