#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        answer.clear();
        run(n, "", 0, 0);
        return answer;
    }
private:
    vector<string> answer;
    void run(int limit, string cur_str, int left_num, int right_num) {
        if (left_num == limit && right_num == limit && cur_str != "") {
            answer.push_back(cur_str);
        } else {
            /* check to whether to add "left" */
            if (left_num != limit) {
                string new_str = cur_str + "(";
                run(limit, new_str, left_num + 1, right_num);
            }
            
            /* check to whether to  add "right" */
            if (right_num != limit && right_num < left_num) {
                string new_str = cur_str + ")";
                run(limit, new_str, left_num, right_num + 1);
            }
        }
    }
};

void print_answer(vector<string> answer) {
    cout << "num : " << answer.size() << endl;
    for (int i = 0; i < answer.size(); i++) {
        cout << answer[i] << endl;
    }
}

int main()
{
    Solution S;
    vector<string> answer = S.generateParenthesis(0);
    print_answer(answer);
    answer  = S.generateParenthesis(3);
    print_answer(answer);
    return 0;
}
