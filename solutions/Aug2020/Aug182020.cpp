#include <iostream>
#include <string>
using namespace std;

/*
Given a mathematical expression with just single digits, plus signs, negative signs, and brackets, 
evaluate the expression. Assume the expression is properly formed.

Example:
Input: - ( 3 + ( 2 - 1 ) )
Output: -4
*/

/*
QUESTIONS: 
-spaces?
-format? (string? array of chars?)
*/

/*
APPROACH: Once we hit a left bracket, we go until we find the matching right bracket.
-If we hit a nested left bracket, we recurse. The recursive function returns the value of the
expression inside the brackets, as well as the index of the corresponding right bracket
using a pointer.
*/
static int PLUS = 0;
static int MINUS = 1;
int recurse(string exp, int *index) {
	int val = 0;
	if (exp.at(*index) >= '0' && exp.at(*index) <= '9') {
		while (*index < exp.length() && exp.at(*index) >= '0' && exp.at(*index) <= '9') {
			val*=10;
			val += exp.at(*index) - 48;
			(*index)++;
		}
		return val;
	}
	if (exp.at(*index) == '(') {
		(*index)++;
		int state = PLUS;
		while (*index < exp.length()) {
			if (exp.at(*index) == ' ') (*index)++;
			else if (exp.at(*index) == '(') {
				val += recurse(exp, index);
			}
			else if (exp.at(*index) == '-') {
				state = MINUS;
				(*index)++;
			}
			else if (exp.at(*index) == '+') {
				state = PLUS;
				(*index)++;
			}
			else if (exp.at(*index) >= '0' && exp.at(*index) <= '9') {
				if (state == PLUS) val += recurse(exp, index);
				else val -= recurse(exp, index);
				(*index)++;
			}
			else if (exp.at(*index) == ')') return val;
		}
		return val;
	}
	return val;
}
int evaluate(string exp) {
	int val = 0;
	int index = 0;
	int state = PLUS;
	while (index < exp.length()) {
		if (exp.at(index) == ' ') ;
		else if (exp.at(index) == '(') {
			val += recurse(exp, &index);
		}
		else if (exp.at(index) == '-') {
			state = MINUS;
		}
		else if (exp.at(index) == '+') {
			state = PLUS;
		}
		else if (exp.at(index) >= '0' && exp.at(index) <= '9') {
			if (state == PLUS) val += recurse(exp, &index);
			else val -= recurse(exp, &index);
		}
		index++;
	}
	return val;
}

int main(int argc, char **argv) {
	string test = "-(321+(2- 11 ) ) + 12-4+56";
	std::cout << evaluate(test) << '\n';
	return 0;
}
