#include <iostream>
#include <map>
using namespace std;

/*
Given a linked list of integers, remove all consecutive nodes that sum up to 0.

Example:
Input: 10 -> 5 -> -3 -> -3 -> 1 -> 4 -> -4
Output: 10

The consecutive nodes 5 -> -3 -> -3 -> 1 sums up to 0 so that sequence should be removed. 
4 -> -4 also sums up to 0 too so that sequence should also be removed.
*/

/*
QUESTIONS: Overlapping consecutive zero sums? i.e. -5 -> 5 -> -3 -> -2: remove all or remove
just one sequence?
Return value? (I'll return head)
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
APPROACH 1: Loop through the list, memoizing the sums we have attained at each node (maybe
using a sum->node map?). If we encounter a previously-encountered sum, we delete all nodes
between map.get(sum) and curNode, making sure to clear all map values as well. Since we
add each value and delete each value at most once, this is O(N) time and space.
*/
/* Remove all values from cur-> until to, inclusive. */
void clearMap(ListNode cur, int sum, ListNode to, map<int,ListNode> m) {
	if (cur == to) return;
	sum += cur->val;
	m.erase(sum);
	clearMap(cur->next, sum, to, m);
}
ListNode removeConsecZeroes(ListNode *list) {
	ListNode dummy = new Node;
	dummy->val = 0;
	dummy->next = *list;
	map<int,ListNode> m;
	ListNode cur = dummy;
	int cSum = 0;
	while (cur != NULL) {
		cSum += cur->val;
		if (m.count(cSum) > 0) {
			ListNode prevNode = m[cSum];
			/* Remove prevNode->next until cur->next from map, exclusive. */
			clearMap(prevNode, cSum, cur, m);
			/* Adjust pointers to remove nodes from list. */
			prevNode->next = cur->next;
		}
		else {
			m.insert(pair<int,ListNode>(cSum, cur));
		}
		cur = cur->next;
	}
	return dummy->next;
}

int main(int argc, char **argv) {
	ListNode list = NULL;
	insert(&list, 10);
	insert(&list, 5);
	insert(&list, -3);
	insert(&list, 1);
	insert(&list, 2);
	insert(&list, -5);
	print(list);
	print(removeConsecZeroes(&list));
	return 0;
}
