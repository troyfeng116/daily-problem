#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
Given a list of building in the form of (left, right, height), return what the skyline should look 
like. The skyline should be in the form of a list of (x-axis, height), where x-axis is the next 
point where there is a change in height starting from 0, and height is the new height starting from 
the x-axis.

ex. 
            2 2 2
            2 2 2
        1 1 2 2 2 1 1
        1 1 2 2 2 1 1
        1 1 2 2 2 1 1
 pos: 1 2 3 4 5 6 7 8 9

input [(2, 8, 3), (4, 6, 5)] => [(2, 3), (4, 5), (6, 3), (8, 0)]
*/

void print(vector<vector<int> > arr) {
    std::cout << "[ ";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << "[" << arr[i][0] << ", " << arr[i][1] << "], ";
    }
    std::cout << "[" << arr[arr.size()-1][0] << ", " << arr[arr.size()-1][1] << "] ]\n";
}

/* APPROACH 1: Add buildings one by one to the skyline. Each building's top left and bottom right
points could determine skyline: we'll call these key points. To deal with overlap, we need to find 
max height at each key point x. O(N^2) */
int myCompare(vector<int> a, vector<int> b, bool x) {
    return x ? a[0] - b[0] : a[1] - b[1];
}
void sort(vector<vector<int> > &arr, int l, int r, bool x) {
    if (l <= r) {
        vector<int> splitter = arr[r];
        int m = l;
        for (int i = l; i < r; i++) {
            if (myCompare(arr[i], splitter, x) < 0) {
                vector<int> temp = arr[i];
                arr[i] = arr[m];
                arr[m] = temp;
                m++;
            }
        }
        arr[r] = arr[m];
        arr[m] = splitter;
        sort(arr, l, m-1, x);
        sort(arr, m+1, r, x);
    }
}
vector<vector<int> > getSkyline(vector<vector<int> > buildings) {
    vector<vector<int> > keyPoints;
    for (int i = 0; i < buildings.size(); i++) {
        int max1 = 0, max2 = 0;
        for (int j = 0; j < buildings.size(); j++) {
            if (buildings[j][0] <= buildings[i][0] && buildings[i][0] <= buildings[j][1]) {
                max1 = max(buildings[j][2], max1);
            }
            if (buildings[j][0] <= buildings[i][1] && buildings[i][1] < buildings[j][1]) {
                max2 = max(buildings[j][2], max2);
            }
        }
        keyPoints.push_back({buildings[i][0], max1});
        keyPoints.push_back({buildings[i][1], max2});
    }
    sort(keyPoints, 0, keyPoints.size()-1, true);
    vector<vector<int> > ans;
    int i = 0;
    while (i < keyPoints.size()) {
        ans.push_back(keyPoints[i]);
        int y = keyPoints[i][1];
        i++;
        while (i < keyPoints.size() && keyPoints[i][1] == y) i++;
    }
    return ans;
}

/* APPROACH 2: Priority Queue. O(N log N) */
vector<vector<int> > getSkyline2(vector<vector<int> > buildings) {
    vector<vector<int>> skyline;
        
    int curr_height = 0;
    int i;
        
    priority_queue<pair<int, int>> pq; // (k,v) = (height, right) of building
    pair<int, int> tope;

    for (i = 0; i < buildings.size(); i++) {
        while (pq.size() && pq.top().second < buildings[i][0]) {
            tope = pq.top(); 
            pq.pop();
            // if the new top has exhausted before the current top
            // i.e., right of the new top <= right of the previous top
            while (pq.size() && pq.top().second <= tope.second)
                pq.pop();
            if (pq.size())
                curr_height = pq.top().first;
            // no buildings after the end of previous top (tope) and start of new building
            else
                curr_height = 0;
            // the decrease in the height has been confirmed
            if (curr_height < tope.first)
                skyline.push_back({tope.second, curr_height});
        }
        pq.push(make_pair(buildings[i][2], buildings[i][1])); // now insert the new building
        // if increase in height, it will be due to new building
        if (curr_height < pq.top().first) {
            // next building also has same begining as this, then skip
            if (i != buildings.size() - 1) {
                if (buildings[i + 1][0] == buildings[i][0]) continue;
            }
            curr_height = pq.top().first;
            skyline.push_back({buildings[i][0], curr_height}); // pair<left limit, height>
        }
    }
    // when all the inputs have exhausted
    while (pq.size() && true) {
        tope = pq.top();
        pq.pop();
        while (pq.size() && pq.top().second <= tope.second) pq.pop();
        if (pq.size())
            curr_height = pq.top().first;
        else 
            curr_height = 0;
        if (curr_height < tope.first)
            skyline.push_back({tope.second, curr_height});
    }  
    return skyline;
}

int main(int argc, char **argv) {
    vector<vector<int> > buildings = { {2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8} };
    vector<vector<int> > buildings2 = {{2, 8, 3}, {4, 6, 5}};
    std::cout << "APPROACH 1 TESTING: \n";
    print(getSkyline(buildings));
    print(getSkyline(buildings2));

    std::cout << "APPROACH 2 TESTING: \n";
    print(getSkyline2(buildings));
    print(getSkyline2(buildings2));
    return 0;
}
