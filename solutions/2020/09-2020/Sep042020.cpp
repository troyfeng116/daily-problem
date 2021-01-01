#include <iostream>
using namespace std;

/*
Implement a queue class using two stacks. A queue is a data structure that supports the FIFO protocol (First in = first out). Your class 
should support the enqueue and dequeue methods like a standard queue.
*/

/* STACK STRUCT */
typedef struct StackNode *Stack;
struct StackNode {
    int val;
    StackNode *next;
};
void push(Stack *s, int val) {
    Stack newNode = new StackNode;
    newNode->val = val;
    newNode->next = *s;
    *s = newNode;
}
int pop(Stack *s) {
    if (*s == NULL) {
        std::cerr << "ERROR: empty stack\n";
        return -1;
    }
    int ans = (*s)->val;
    *s = (*s)->next;
    return ans;
}

/* QUEUE STRUCT: use a back and front stack. */
struct Queue {
    Stack back;
    Stack front;
};
Queue *createQueue() {
    Queue *q = new Queue;
    q->back = NULL;
    q->front = NULL;
    return q;
}
bool isEmpty(Queue *q) {
    return q->back == NULL && q->front == NULL;
}
void push_back(Queue *q, int val) {
    push(&(q->back), val);
}
int pop_front(Queue *q) {
    if (isEmpty(q)) {
        std::cout << "ERROR: empty queue\n";
        return -1;
    }
    if (q->front != NULL) return pop(&(q->front));
    while (q->back != NULL) {
        push(&(q->front), pop(&q->back));
    }
    return pop(&(q->front));;
}

int main(int argc, char **argv) {
/* STACK TESTING */
    Stack s = NULL;
    push(&s, 1);
    push(&s, 5);
    push(&s, 7);
    std::cout << pop(&s) << '\n';
    std::cout << pop(&s) << '\n';
    std::cout << pop(&s) << '\n';
    std::cout << pop(&s) << '\n';

/* QUEUE TESTING */
    Queue *q = createQueue();
    push_back(q, 5);
    push_back(q, 1);
    push_back(q, 19);
    std::cout << pop_front(q) << '\n';
    std::cout << pop_front(q) << '\n';
    std::cout << pop_front(q) << '\n';
    std::cout << pop_front(q) << '\n';
    return 0;
}
