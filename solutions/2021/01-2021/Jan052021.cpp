#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

/*
A task is a some work to be done which can be assumed takes 1 unit of time. Between the same
type of tasks you must take at least n units of time before running the same tasks again.

Given a list of tasks (each task will be represented by a char), and a positive integer n
representing the time it takes to run the same task again, find the minimum amount of time
needed to run all tasks.

ex. tasks = {'q', 'q', 's', 'q', 'w', 'w'}, cooldown = 4 => return 9
could run 'q', 'w', 's', idle, 'q', 'w', idle, idle, 'q'
*/

/*
APPROACH 1: The task that appears most frequently will set a lower bound on the time.
I.e. say that A appears 10 times with cooldown = 2. Then we need at least 
10*3 - 2 = 28 ticks.
The total number of tasks also sets a lower bound on the time.    
Let the max frequency be M, and let numMax be the number of tasks that appear M times. Then
if cooldown + 1 >= numMax, we would need
(M - 1) * (cooldown + 1) + numMax ticks, and we would have
(M - 1) * (cooldown - numMax) free slots
spaces n apart.
If numMax >= cooldown, we need M*x ticks, with 0 free slots.
It seems we should sort by decreasing frequency. Once the most frequent are placed,
we can place stuff between them with no problems (only makes them farther apart). So
if we place the most frequent first, and then place the rest between them, we can always
do so.
O(N) time and space
*/
int minTimeToCompleteTasks(vector<char> tasks, int cooldown) {
    unordered_map<char, int> table;
    int maxFreq = 0; // max frequency
    int numMax = 0; // Number of tasks with max frequency
    for (char c : tasks) {
        int count = table.count(c) > 0 ? table[c] : 0;
        table[c] = count + 1;
        if (count + 1 > maxFreq) {
            maxFreq = count + 1;
            numMax = 1;
        }
        else if (count + 1 == maxFreq) numMax++;
    }
    int ans = cooldown + 1 >= numMax ? ((maxFreq - 1) * (cooldown+1) + numMax) : maxFreq * numMax;
    int numIdle = cooldown + 1 >= numMax ? (maxFreq - 1) * (cooldown + 1 - numMax) : 0;
    if (tasks.size() - maxFreq * numMax <= numIdle) return ans;
    return ans + tasks.size() - maxFreq * numMax - numIdle;
}

/* APPROACH 2: Max heap. Store frequencies in max heap, and then remove them one by one
to simulate doing tasks. Do this cooldown + 1 times to guarantee no task is done twice
within cooldown time units. Subtract one from each of the frequencies to simulate
completing the task once. Then, after doing cooldown + 1 tasks, put all the tasks back
into the heap. O(N log N) time, O(N) space */
int minTimeToCompleteTasks2(vector<char> tasks, int cooldown) {
    unordered_map<char, int> table;
    for (char c : tasks) {
        table[c]++;
    }
    priority_queue<int, vector<int>, less<int> > maxHeap;
    for (auto it = table.begin(); it != table.end(); it++) {
        maxHeap.push(it->second);
    }
    int ans = 0;
    while (!maxHeap.empty()) {
        vector<int> tasks;
        int time = 0;
        for (; time <= cooldown && !maxHeap.empty(); time++) {
            int freq = maxHeap.top();
            maxHeap.pop();
            tasks.push_back(freq - 1);
        }
        for (int updatedFreq : tasks) {
            if (updatedFreq > 0) maxHeap.push(updatedFreq);
        }
        ans += maxHeap.empty() ? time : cooldown + 1;
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<char> tasks = {'q', 'q', 'x', 'q', 'w', 'w'};
    int cooldown = 4;
    std::cout << "APPROACH 1: " << minTimeToCompleteTasks(tasks, cooldown) << '\n';
    std::cout << "APPROACH 2: " << minTimeToCompleteTasks2(tasks, cooldown) << '\n';
    return 0;
}
