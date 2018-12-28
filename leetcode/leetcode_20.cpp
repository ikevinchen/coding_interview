#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> stack;
        int i;
        
        for (i = 0; i < s.length(); i++) {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
                stack.push(s[i]);
            } else {
                if (stack.empty()) {
                    return false;
                }
                char top_char = stack.top();                
                if ((s[i] == ')' && top_char != '(') ||
                    (s[i] == '}' && top_char != '{') ||
                    (s[i] == ']' && top_char != '[')) {
                    return false;
                }
                stack.pop();
            }
        }
        if (stack.empty()) {
            return true;
        } else {
            return false;
        }
    }
};

int main()
{
    Solution S;
    cout << S.isValid("[]") << endl;
    cout << S.isValid("") << endl;
    cout << S.isValid("[{]}") << endl;
    cout << S.isValid("[{}]") << endl;
    cout << S.isValid("[") << endl;
    return 0;
}
