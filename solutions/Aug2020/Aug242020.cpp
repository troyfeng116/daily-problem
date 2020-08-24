#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
using namespace std;

/*
Given a string with the initial condition of dominoes, where:

. represents that the domino is standing still
L represents that the domino is falling to the left side
R represents that the domino is falling to the right side

Figure out the final position of the dominoes. If there are dominoes that get pushed on both ends, 
the force cancels out and that domino remains upright.

Example:
Input:  ..R...L..R.
Output: ..RR.LL..RR
*/

/*
QUESTIONS: It seems that R.L and R..L don't topple any, but R...L and any R[...]L with >=3 still
dominoes between them will topple until either R.L or R..L. In short, as long as we aren't given
RL to begin with, we will never end with any RLs: there will be either 1 or 2 still dominoes between
them? And L and R dominoes fall instantaneously at the same rate and must meet in middle?
*/

/*
Approach 1: One pass L-R, one pass R-L, topple one domino at a time. This guarantees the R[...]L
will meet in the middle. Since at most N dominoes topple per turn, and each turn takes two linear
passes (actually 1 using mirroring), this is O(N^2).
*/

/* state.at(i) is either 'R' or 'L' (based on bool right). Return true if it is safe to topple the
dominot to the R/L respectively of i (i.e. if we haven't reached middle of R[...]L segment). */
bool isSafe(string state, int i, bool right) {
	if (right) {
		if (state.at(i+1) != '.') return false;
		if (i < state.length()-2 && state.at(i+2) == 'L') return false;
		if (i < state.length()-3 && state.at(i+3) == 'L') return false;
	}
	else {
		if (state.at(i-1) != '.') return false;
		if (i >= 2 && state.at(i-2) == 'R') return false;
		if (i >= 3 && state.at(i-3) == 'R') return false;
	}
	return true;
}
string toppleDominoes1(string state) {
	bool noneToppled = true;
	for (int i = 0; i < state.length()-1; i++) {
		int mirror = state.length()-i-1;
		if (state.at(i) == 'R' && isSafe(state, i, true)) {
			noneToppled = false;
			state.replace(i+1,1,"r");
		}
		else if (state.at(mirror) == 'L' && isSafe(state, mirror, false)) {
			noneToppled = false;
			state.replace(mirror-1, 1, "l");
		}
	}
	std::transform(state.begin(), state.end(),state.begin(), ::toupper);
	return noneToppled? state : toppleDominoes1(state);
}

/*
Approach 2: Take one L-R pass and one R-L pass. If R, mark all non-toppled dominoes to its right
with the distance to R. Same for L. Then loop through. If distance to nearest R is within 1 of
distance to nearest L, don't topple. This takes O(N).
*/
string toppleDominoes2(string state) {
	int *distToR = new int[state.length()];
	int *distToL = new int[state.length()];
	for (int i = 0; i < state.length(); i++) {
		distToR[i] = 0;
		distToL[i] = 0;
	}
	int index = 0;
	while (index < state.length()-1) {
		if (state.at(index) == 'R') {
			index++;
			int count = 0;
			while (index < state.length() && state.at(index) == '.') {
				count++;
				distToR[index] = count;
				index++;
			}
		}
		else index++;
	}
	index = state.length()-1;
	while (index >= 1) {
		if (state.at(index) == 'L') {
			index--;
			int count = 0;
			while (index >= 0 && state.at(index) == '.') {
				count++;
				distToL[index] = count;
				index--;
			}
		}
		else index--;
	}
	for (int i = 0; i < state.length(); i++) {
		std::cout << distToR[i] << " " << distToL[i] << '\n';
	}
	for (int i = 0; i < state.length(); i++) {
		if (distToR[i] == 0 && distToL[i] == 0) ;
		else if (distToR[i] == 0) state.replace(i,1,"L");
		else if (distToL[i] == 0) state.replace(i,1,"R");
		else if (distToR[i] - distToL[i] > 1) state.replace(i,1,"L");
		else if (distToL[i] - distToR[i] > 1) state.replace(i,1,"R");
		else ;
	}
	return state;
}

int main(int argc, char **argv) {
	string state = "..R......L..L..R";
	std::cout << toppleDominoes1(state) << '\n';
	std::cout << state << '\n';
	std::cout << toppleDominoes2(state) << '\n';
	return 0;
}
