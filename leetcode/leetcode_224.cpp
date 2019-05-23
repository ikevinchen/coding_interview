#include <iostream>
#include <string>
#include <stack>
using namespace std;

void skip_space(string& s, int* s_pos)
{
	while (*s_pos < s.length() && s[*s_pos] == ' ') {
		(*s_pos)++;
	}
}

int calculate(string s) {
	int cur_sum = 0;
	bool prev_operator = true; /* true : plus, false : substract */
	int s_pos = 0;
	
	stack<int> stack_sum;
	stack<bool> stack_operator;
	
	/*                         |---------------------
	 *                         v                    |
	 *  ----(A)--> [number] -----(B)---->  [  )  ]--|
	 *    ^           or                   [ +/- ]-----|
	 *    |        [  (   ]                [ EOF ]     |
	 *    |                                            |
	 *    ---------------------------------------------|
	 */
	
	while (s_pos < s.length()) {
		
		skip_space(s, &s_pos);
		
		if (s[s_pos] >= '0' && s[s_pos] <= '9') {
			
			/* fetch number */
			int num = s[s_pos] - '0';
			s_pos++;
			while (s_pos < s.length() && s[s_pos] >= '0' && s[s_pos] <= '9')
			{
				num = num * 10 + (s[s_pos] - '0');
				s_pos++;
			}
			
			/* update current sum */
			if (prev_operator == true) {
				cur_sum += num;
			} else {
				cur_sum -= num;
			}
				
			/* find the next one operator, or EOF */
			while(1) {
				skip_space(s, &s_pos);
				if (s_pos == s.length()) {
					/* the end */
					break;
				} else if (s[s_pos] == '+') {
					/* find the operator, break */
					prev_operator = true;
					s_pos++;
					break;
				} else if (s[s_pos] == '-') {
					/* find the operator, break */
					prev_operator = false;
					s_pos++;
					break;
				} else if (s[s_pos] == ')') {
					/* restore to the previous cur_sum,
					 *  still need to find the next operator (or EOF) 
					 */
					if (stack_operator.top() == true) {
						cur_sum = stack_sum.top() + cur_sum;
					} else {
						cur_sum = stack_sum.top() - cur_sum;
					}
					stack_operator.pop();
					stack_sum.pop();
					s_pos++;
				} else {
					cout << "something wrong" << endl;
					return -1;
				}		
			}
		} else if (s[s_pos] == '(') {
			stack_sum.push(cur_sum);
			stack_operator.push(prev_operator);
			prev_operator = true;
			cur_sum = 0;
			s_pos++;
		} else {
			cout << "something wrong" << endl;
			return -1;
		}
	}
	
	return cur_sum;	
}

int main()
{
	cout << calculate("123") << endl;
	cout << calculate(" 1 + 1 ") << endl;
	cout << calculate("((1 + 1))") << endl;
	cout << calculate("1 + (1 + 1)") << endl;
	cout << calculate("1 - (1 + 1)") << endl;
	cout << calculate("(1+(4+5+2)-3)+(6+8)") << endl;
	return 0;
}

