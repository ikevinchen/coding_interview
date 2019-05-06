#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

typedef struct interval {
	int key;
	int data_min;
	int data_max;
	
	bool operator==(const interval& r) const {
        return key == r.key;
    };	
} interval_t;

namespace std
{
  template<>
    struct hash<interval_t>
    {
        size_t operator()(const interval_t& r) const {
            size_t hash = r.key;
            return hash;
        };
    };
}

int longestConsecutive(vector<int>& nums) {
    unordered_set<interval_t> Hash_interval; /* record the endpoint of each interval */
	unordered_set<int> Hash_number;          /* record the existed number */
	int answer = 0;
	
	for (int i = 0; i < nums.size(); i++) {		
	
		int new_num = nums[i];		
		
		//cout << "======== " << new_num <<  " =============" << endl;
		
		
		if (Hash_number.count(new_num) != 0) {
			continue; /* skip reduntand number */
		}

		Hash_number.insert(new_num);
		int new_min = new_num;
		int new_max = new_num;
		interval_t find_entry;
		unordered_set<interval_t>::const_iterator find_iter;
		
		find_entry.key = new_num + 1;
		find_iter = Hash_interval.find(find_entry);
		if (find_iter != Hash_interval.end()) {
			int find_min = find_iter->data_min;
			int find_max = find_iter->data_max;
			new_max = find_max;
			interval_t delete_entry;
			delete_entry.key = find_min;
			Hash_interval.erase(delete_entry); //cout << "delete " << delete_entry.key << endl;
			delete_entry.key = find_max;
			Hash_interval.erase(delete_entry); //cout << "delete " << delete_entry.key << endl;
		}
		
		find_entry.key = new_num - 1;
		find_iter = Hash_interval.find(find_entry);
		if (find_iter != Hash_interval.end()) {
			int find_min = find_iter->data_min;
			int find_max = find_iter->data_max;
			new_min = find_min;
			interval_t delete_entry;
			delete_entry.key = find_min;
			Hash_interval.erase(delete_entry); //cout << "delete " << delete_entry.key << endl; 
			delete_entry.key = find_max;
			Hash_interval.erase(delete_entry); //cout << "delete " << delete_entry.key << endl;
		}
		
		if (new_max - new_min + 1 > answer) {
			answer = new_max - new_min + 1;
			//cout << "answer = " << answer << endl;
		}
		
		interval_t new_entry;
		new_entry.key = new_min;
		new_entry.data_min = new_min;
		new_entry.data_max = new_max;
		Hash_interval.insert(new_entry); //cout << "insert " << new_entry.key << " " << new_min << " " << new_max << endl; 
		new_entry.key = new_max;
		new_entry.data_min = new_min;
		new_entry.data_max = new_max;
		Hash_interval.insert(new_entry); //cout << "insert " << new_entry.key << " " << new_min << " " << new_max << endl; 
	}
	
	return answer;
}

int main()
{
	vector<int> arr{ 1, 2, 10, 12, 2};
	cout << longestConsecutive(arr) << endl;
	return 0;
}
