#include <iostream>
#include <unordered_map>
using namespace std;

/*
LRU cache is a cache data structure that has limited space, and once there are more items in the cache than available space,
it will preempt the least recently used item. What counts as recently used is any item a key has 'get' or 'put' called on it.

Implement an LRU cache class with the 2 functions 'put' and 'get'. 'put' should place a value mapped to a certain key, and
preempt items if needed. 'get' should return the value for a given key if it exists in the cache, and return None if it
doesn't exist.

ex.
cache = LRUCache(2)

cache.put(3, 3)
cache.put(4, 4)
print(cache.get(3)) -> 3
print(cache.get(2)) -> None

cache.put(2, 2)

print(cache.get(4)) -> None (pre-empted by 2)
print(cache.get(3)) -> 3
*/

struct Node {
    int key;
    int val;
    Node *prev;
    Node *next;
    Node(int k, int v) {
        key = k;
        val = v;
        prev = nullptr;
        next = nullptr;
    }
};

/* APPROACH 1: doubly linked list for queue implementation with hashmap for get. */
class LRUCache {
private:
    int capacity;
    int count;
    Node *front;
    Node *back;
    unordered_map<int, Node*> map;
public:
    LRUCache(int cap) {
        capacity = cap;
        count = 0;
        front = new Node(0, 0);
        back = new Node(0, 0);
        front->next = back;
        back->prev = front;
    }

    int get(int key) {
        if (map.find(key) == map.end()) {
            cout << "NONE";
            return -1;
        } else {
            Node *node = map[key];
            if (front->next == node) return node->val;
            // Remove node from its spot
            node->next->prev = node->prev;
            node->prev->next = node->next;
            // Place node at front of list
            front->next->prev = node;
            node->next = front->next;
            node->prev = front;
            front->next = node;
            return node->val;
        }
    }

    void put(int key, int val) {
        if (map.find(key) == map.end()) {
            Node *newNode = new Node(key, val);
            if (count >= capacity) {
                Node *toDelete = back->prev;
                toDelete->prev->next = back;
                back->prev = toDelete->prev;
                map.erase(toDelete->key);
                delete toDelete;
            } else count++;
            // Place new node at front of list
            front->next->prev = newNode;
            newNode->next = front->next;
            newNode->prev = front;
            front->next = newNode;
            map[key] = newNode;
        } else {
            map[key]->val = val;
            // Bump key to front of list
            get(key);
        }
    }
};

int main(int argc, char **argv) {
    LRUCache *cache = new LRUCache(2);
    cache->put(3, 3);
    cache->put(4, 4);
    cout << cache->get(3) << '\n'; // 3
    cout << cache->get(2) << '\n'; // None
    cache->put(2, 2);
    cout << cache->get(4) << '\n'; // None
    cout << cache->get(3) << '\n'; // 3
    return 0;
}
