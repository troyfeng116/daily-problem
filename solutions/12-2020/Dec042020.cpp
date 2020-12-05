#include <iostream>
#include <unordered_map>
using namespace std;

/*
Given a nested dictionary, flatten the dictionary, where nested dictionary keys can be represented through dot 
notation.

Example:
Input: {
  'a': 1,
  'b': {
    'c': 2,
    'd': {
      'e': 3
    }
  }
}
Output: {
  'a': 1,
  'b.c': 2,
  'b.d.e': 3
}
You can assume there will be no arrays, and all keys will be strings.
*/

// If nested.size == 0, value is just val.
struct Dict {
    unordered_map<string, Dict*> dict;
    int val;
    Dict() {}
    Dict(int v) {
        val = v;
    }
    void insert(string key, Dict *d) {
        dict[key] = d;
    }
};

void printDict(Dict *d) {
    unordered_map<string, Dict*> dict = d->dict;
    if (dict.size() == 0) {
        std::cout << d->val << ", ";
        return;
    }
    std::cout << "{ ";
    for (auto i = dict.begin(); i != dict.end(); i++) {
        std::cout << i->first << ": ";
        printDict(i->second);
    }
    std::cout << " }, ";
}

/* APPROACH 1: Recursion. */
Dict *flattenDict(Dict *d) {
    unordered_map<string, Dict*> dict = d->dict;
    // "Base case"
    if (dict.size() == 0) return new Dict(d->val);
    unordered_map<string, Dict*> newDict;
    // Flatten all nested dicts in map and add to new map
    for (auto i = dict.begin(); i != dict.end(); i++) {
        Dict *nested = flattenDict(i->second);
        if (nested->dict.size() == 0) newDict[i->first] = nested;
        else {
            for (auto j = nested->dict.begin(); j != nested->dict.end(); j++) {
                newDict[i->first + "." + j->first] = j->second;
            }
        }
    }
    d->dict = newDict;
    return d;
}

int main(int argc, char **argv) {
    Dict *dict = new Dict();
    dict->dict["a"] = new Dict(1);
    dict->dict["b"] = new Dict();
    dict->dict["b"]->dict["c"] = new Dict(2);
    dict->dict["b"]->dict["d"] = new Dict();
    dict->dict["b"]->dict["d"]->dict["e"] = new Dict(3);
    printDict(dict);
    std::cout << '\n';
    printDict(flattenDict(dict));
    std::cout << '\n';
    return 0;
}
