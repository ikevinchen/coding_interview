#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define MAX (10000)

struct Account {
    string name, email;
    Account(string n, string e) {
        name = n;
        email = e;
    }
    bool operator==(const Account& rhs) const {
        return name == rhs.name && email == rhs.email;
    }
};

class MyHashFunction {
public:
    // We use predfined hash functions of strings
    // and define our hash function as XOR of the
    // hash values.
    size_t operator()(const Account& p) const
    {
        return (hash<string>()(p.name)) ^
               (hash<string>()(p.email));
	}
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
		/* init */
		vector<vector<string>> answer;
        _num = 0;

		/* parse input */
		for (int i = 0; i < accounts.size(); i++) {
			string &name = accounts[i][0];
			int last_id = -1;

			for (int j = 1; j < accounts[i].size(); j++) {
				string &email = accounts[i][j];
				Account input(name, email);
				int input_id;
				unordered_map<Account, int, MyHashFunction>::const_iterator got = _hashTable.find(input);
				if (got == _hashTable.end()) {
					input_id = _num++;
					_hashTable[input] = input_id;
					_indexTable.push_back(input);
				} else {
					input_id = got->second;
				}
				if (input_id >= MAX) {
					cout << "error" << endl;
					return answer;
				}
				if (last_id != -1) {
					_edge[last_id].push_back(input_id);
					_edge[input_id].push_back(last_id);
				}
				last_id = input_id;
			}
		}

		/* find the answer */
		for (int i = 0; i < _num; i++) {
			_touch[i] = false;
		}
		for (int i = 0; i < _num; i++) {
			if (_touch[i] == true)
				continue;
			vector<string> vec;
			vec.push_back(_indexTable[i].name);
			dfs(vec, i);
			sort(vec.begin() + 1, vec.end());
			answer.push_back(vec);
		}
		return answer;
    }
private:
	int _num;
	unordered_map<Account, int, MyHashFunction> _hashTable;
	vector<Account> _indexTable;
	vector<int> _edge[MAX];
	bool _touch[MAX];
	void dfs(vector<string> &vec, int id) {
		if (id >= _indexTable.size()) {
			cout << "error" << endl;
			return;
		}
		if (_touch[id] == true) {
			return;
		}

		_touch[id] = true;
		vec.push_back(_indexTable[id].email);
		for (int i = 0; i < _edge[id].size(); i++) {
			dfs(vec, _edge[id][i]);
		}
	}
};

int main()
{
    Solution S;
    vector<vector<string>> input;
    vector<string> v0{"name_1", "A", "B"};
    vector<string> v1{"name_1", "C", "D", "E"};
    vector<string> v2{"name_1", "A", "C"};
    input.push_back(v0);
    input.push_back(v1);
    input.push_back(v2);
    vector<vector<string>> answer = S.accountsMerge(input);
    for (int i = 0; i < answer.size(); i++) {
        for (int j = 0; j < answer[i].size(); j++) {
            cout << answer[i][j] << " ";
        }
        cout << endl;
    }
	return 0;
}
