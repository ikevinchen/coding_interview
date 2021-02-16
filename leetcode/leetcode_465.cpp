#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int ,int> _map; /* id, money (>0 : in, <0, out) */
        for (int i = 0; i < transactions.size(); i++) {
            int out_id = transactions[i][0];
            int in_id = transactions[i][1];
            int money = transactions[i][2];
            unordered_map<int, int>::const_iterator iter;
            
            if (money < 0) {
                cout << "error" << endl;
                return -1;
            }
            
            iter = _map.find(out_id);
            if (iter == _map.end()) {
                _map[out_id] = -money;
            } else {
                int before = _map[out_id];
                int after = _map[out_id] - money;
                if (after == 0) {
                    _map.erase(iter);
                } else {
                    _map[out_id] = after;
                }
            }
            
            iter = _map.find(in_id);
            if (iter == _map.end()) {
                _map[in_id] = money;
            } else {
                int before = _map[in_id];
                int after = _map[in_id] + money;
                if (after == 0) {
                    _map.erase(iter);
                } else {
                    _map[in_id] = after;
                }
            }
            
            //cout << "Round " << i << " " << out_id << "-->"
            //     << in_id << ": " << money << endl;
        }
        
        /* put the result into two vectors */
        vector<int> out_pq;
        vector<int> in_pq;
        for (auto it = _map.begin(); it != _map.end(); ++it) {
            //cout << it->first << " : " << it->second <<endl;
            if (it->second > 0) {
                in_pq.push_back(it->second);
            } else {
                out_pq.push_back(-it->second);
            }
        }
        if (out_pq.empty()) {
            return 0;
        }
        
        /* 
         * Try to find if there is any 2, 3, 4 .. N in the group whose sum = zero
         * (greedy algo.)
         * C(n, 2) + C(n,3) + .... C(n,n) = O(2^n)
         *
         *  if there are three number in the group.
         *  ==> answer += 2
         *   ex. (out 5, in 3, in 2) ==> need 2 transfers
         */
        int answer = 0;
        int touched = 0;
        //cout << "out : "; print_q(out_pq);
        //cout << "in  : "; print_q(in_pq);
        for (int i = 2; i <= out_pq.size() + in_pq.size(); i++) {
            for(int j = 1; j < i; j++) {
                //cout << "try " << j << " " << i - j << " in a group: ";
                int success_groups = dfs_traverse(out_pq, j, in_pq, i - j);
                if (success_groups != 0) {
                    //cout << "find out !" << endl;
                    touched += (success_groups * i);
                    answer += (success_groups * (i - 1));
                    if (touched == out_pq.size() + in_pq.size()) {
                        return answer;
                    }
                    //cout << "  left out : "; print_q(out_pq);
                    //cout << "  left in  : "; print_q(in_pq);
                } else {
                    //cout << "none" << endl;
                }
            }
        }
        cout << "error" << endl;
        return -1;
    }

    void print_q(vector<int> &q)
    {
        for (int i = 0; i < q.size(); i++) {
            if (q[i] == 0) continue;
            cout << q[i] << " ";
        }
        cout << endl;
    }

    int dfs_traverse(vector<int> &q, int count, vector<int> &q_s, int q_s_count)
    {
        int success_num = 0;
        for (int i = 0; i < q.size(); i++) {
            if (q[i] == 0) continue;
            if (dfs_traverse_recursive(1, count, i, q, 0, q_s, q_s_count) == 0) {
                success_num++;
            }
        }
        return success_num;
    }

    int dfs_traverse_recursive(int level, int level_max,
                               int index, vector<int> &q,
                               int sum, vector<int> &q_s, int q_s_count)
    {
        if (level == level_max) {
            sum += q[index];
            if (dfs_search(q_s, sum, q_s_count) == 0){
                q[index] = 0;
                return 0;
            }
        } else {
            sum += q[index];
            for (int i = index + 1; i < q.size(); i++) {
                if (q[i] == 0) continue;
                if (dfs_traverse_recursive(level + 1, level_max,
                                           i, q, sum, q_s, q_s_count) == 0)
                {
                    q[index] = 0;
                    return 0;
                }
            }
        }
        return -1;
    }

    int dfs_search(vector<int> &q, int target, int count)
    {
        //cout << "dfs_search " << target << " " << count << endl;
        for (int i = 0; i < q.size(); i++) {
            if (q[i] == 0) continue;
            if (dfs_search_recursive(1, count, i, q, 0, target) == 0) {
                return 0;
            }
        }
        return -1;
    }


    int dfs_search_recursive(int level, int level_max,
                             int index, vector<int> &q,
                             int sum, int sum_max)
    {
        if (level == level_max) {
            if (sum + q[index] == sum_max) {
                q[index] = 0;
                return 0;
            }
        } else {
            sum += q[index];
            if (sum >= sum_max) return -1;
            for (int i = index + 1; i < q.size(); i++) {
                if (q[i] == 0) continue;
                if (dfs_search_recursive(level + 1, level_max,
                                         i, q, sum, sum_max) == 0)
                {
                    q[index] = 0;
                    return 0;
                }
            }
        }
        return -1;
    }
};

int main()
{
    vector<vector<int>> vect_1
    {
        {0, 1, 10},
        {1, 0, 1},
        {1, 2, 5},
        {2, 0, 5},
    };
    vector<vector<int>> vect_2
    {
        {0, 1, 10},
        {1, 0, 10},
    };
    vector<vector<int>> vect_3
    {
        {{0,1,5},{2,3,1},{2,0,1},{4,0,2}},
    };
    vector<vector<int>> vect_4
    {
        {{1,5,8},{8,9,8},{2,3,9},{4,3,1}},
    };
    Solution S;
    cout << S.minTransfers(vect_1) << endl;
    cout << S.minTransfers(vect_2) << endl;
    cout << S.minTransfers(vect_3) << endl;
    cout << S.minTransfers(vect_4) << endl;
    return 0;
}
