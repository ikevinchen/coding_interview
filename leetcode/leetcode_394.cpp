#include <unordered_map>
#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    string decodeString(string s) {
        /* create hash map for brackets indexing */
        stack<int> brackets_stack;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '[') {
                brackets_stack.push(i);
            } else if (s[i] == ']') {
                int left_bracket_index = brackets_stack.top();
                int right_bracket_index = i;
                index_map[left_bracket_index] = right_bracket_index;
                brackets_stack.pop();
            }
        }
        /* start */
        return print(s, 0, s.length() - 1);
    }
private:
    string print(string &str, int left, int right) {
        //cout << left << " " <<right << "\n";
        string output_s;
        for (int i = left; i <= right; i++) {
            /* case A : "number[" */
            if (str[i] >= '1' && str[i] <= '9') {
                int number = 0;
                while (1) {
                    if (str[i] == '[') {
                        break;
                    }
                    int digit = str[i] - '0';
                    number = number * 10 + digit;
                    i++;
                }
                int left_bracket = i;
                int right_bracket = index_map[i];
                for (int j = 0; j < number; j++) {
                    output_s += print(str, left_bracket + 1, right_bracket - 1);
                }
                i = right_bracket;
            }
            /* case B : letters */
            else {
                output_s += str[i];
            }
        }
        return output_s;
    }
    unordered_map<int ,int> index_map;
};

int main()
{
    Solution S;
    cout << S.decodeString("abc") << "\n";
    cout << S.decodeString("10[ac]") << "\n";
    cout << S.decodeString("5[a3[bd]c]") << "\n";
    return 0;
}
