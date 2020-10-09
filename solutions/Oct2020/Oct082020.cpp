#include <iostream>
using namespace std;

/*
Design a simple stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.

Note: be sure that pop() and top() handle being called on an empty stack.
*/

/* APPROACH 1: Add another field to stack. O(1) getMin but O(N) space */
typedef struct StackNode1 *Stack1;
struct StackNode1 {
    int val;
    int minSoFar;
    StackNode1 *next;
    StackNode1(int v, StackNode1 *n) {
        val = v;
        minSoFar = n == NULL ? v : min(v, n->minSoFar);
        next = n;
    }
};

void push(Stack1 *s, int val) {
    Stack1 top = new StackNode1(val, *s);
    *s = top;
}
int pop(Stack1 *s) {
    if (*s == NULL) {
        std::cout << "ERROR: TRIED TO POP EMPTY STACK\n";
        return -1;
    }
    int ans = (*s)->val;
    *s = (*s)->next;
    return ans;
}
int top(Stack1 *s) {
    if (*s == NULL) {
        std::cout << "ERROR: TRIED TO TOP EMPTY STACK\n";
        return -1;
    }
    return (*s)->val;
}
int getMin(Stack1 *s) {
    if (*s == NULL) {
        std::cout << "ERROR: TRIED TO GET MIN EMPTY STACK\n";
        return -1;
    }
    return (*s)->minSoFar;
}
void printStack(Stack1 *s) {
    if (*s == NULL) {
        std::cout << "EMPTY STACK\n";
        return;
    }
    Stack1 cur = *s;
    while (cur != NULL) {
        std::cout << cur->val << ' ';
        cur = cur->next;
    }
    std::cout << '\n';
}

int main(int argc, char **argv) {
    Stack1 stack = NULL;
    push(&stack, -2);
    push(&stack, 0);
    push(&stack, 3);
    std::cout << getMin(&stack) << '\n';
    std::cout << pop(&stack) << '\n';
    std::cout << top(&stack) << '\n';
    std::cout << getMin(&stack) << '\n';
    printStack(&stack);
    return 0;
}
