#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

/*
We have a list of tasks to perform, with a cooldown period. We can do multiple of these at the same 
time, but we cannot run the same task simultaneously.

Given a list of tasks, find how long it will take to complete the tasks in the order they are input.
tasks = [1, 1, 2, 1]
cooldown = 2
output: 7 (order is 1 _ _ 1 2 _ 1)
*/

/* QUESTION: Are the list of tasks like times or task labels? kinda confusing. So 1,1,2,1 means
do task A, then task A, then task B, then task A? Will assume tasks are labels not durations or
times. */

/* APPROACH 1: Use map to keep track of cooldowns. (k,v) = (task#, last executed). O(N*K) time
and O(N) space */
int minTimeToCompleteTasks(vector<int> &tasks, int cooldown) {
    unordered_map<int, int> table;
    int time = 0;
    int taskIndex = 0;
    while (taskIndex < tasks.size()) {
        int curTask = tasks[taskIndex];
        int lastExecuted = table.count(curTask) > 0 ? table[curTask] : -1;
        if (lastExecuted < 0 || time - lastExecuted > cooldown) {
            table[curTask] = time;
            std::cout << "Completed task " << curTask << " at index " << taskIndex << '\n';
            taskIndex++;
        }
        else {
            std::cout << "Cooldown for task " << curTask << '\n';
        }
        time++;
    }
    return time;
}

/* APPROACH 2: Same as approach 1, but get rid of additional K time increments. O(N) */
int minTimeToCompleteTasks2(vector<int> &tasks, int cooldown) {
    unordered_map<int, int> table;
    int time = 0;
    for (int i = 0; i < tasks.size(); i++) {
        int task = tasks[i];
        if (table.count(task) > 0) {
            int last = table[task];
            int timeSince = time - last;
            if (timeSince <= cooldown) {
                time += cooldown - timeSince + 1;
            }
        }
        table[task] = time;
        time++;
    }
    return time;
}

int main(int argc, char **argv) {
    int cooldown = 2;
    vector<int> tasks = {1, 1, 2, 1, 1};
    std::cout << "APPROACH 1 TESTING: \n" << minTimeToCompleteTasks(tasks, cooldown) << '\n';
    std::cout << "APPROACH 2 TESTING: \n" << minTimeToCompleteTasks2(tasks, cooldown) << '\n';
    return 0;
}
