#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
		unordered_map<int ,int> _map; /* id, money (>0 : in, <0, out)*/
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
		
		/* calculate answer */
		priority_queue<int> out_pq;
		priority_queue<int> in_pq;
		int answer = 0;
		for (auto it = _map.begin(); it != _map.end(); ++it) {
			cout << it->first << " : " << it->second <<endl;
			if (it->second > 0) {
				in_pq.push(it->second);
			} else {
				out_pq.push(-it->second);
			}
		}
		if (in_pq.empty()) {
			return 0;
		}
		int out_money = out_pq.top();
		int in_money = in_pq.top();
		while (1) {
			if (out_money > in_money) {
				out_money = out_money - in_money;
				answer++;
				in_pq.pop();
				if (in_pq.empty()) {
					cout << "error" << endl;
					return -1;
				}
				in_money = in_pq.top();
			} else if (out_money < in_money) {
				in_money = in_money - out_money;
				answer++;
				out_pq.pop();
				if (out_pq.empty()) {
					cout << "error" << endl;
					return -1;
				}
				out_money = out_pq.top();
			} else {
				answer++;
				in_pq.pop();
				out_pq.pop();
				if (in_pq.empty()) break;
				in_money = in_pq.top();
				out_money = out_pq.top();
			}
		}
		return answer;
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
	//cout << S.minTransfers(vect_1) << endl;
	//cout << S.minTransfers(vect_2) << endl;
	//cout << S.minTransfers(vect_3) << endl;
	cout << S.minTransfers(vect_4) << endl;
	return 0;
}
