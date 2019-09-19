/* g++ leetcode_1.cpp -std=c++0x if lower version of g++ */
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

typedef struct object_s{
	int value;
	int index;

	inline bool operator==(const struct object_s& r) const {
		return (value == r.value);
	}
} object_t;

namespace std
{
  template<>
    struct hash<object_t>
    {
        size_t operator()(const object_t& r) const {
            size_t hash = r.value;
            return hash;
        };
    };
}

vector<int> twoSum(vector<int>& nums, int target) {
	vector<int> answer;
	unordered_set<object_t> myset;	

	/* insert data into hash */
	for (int i = 0; i < nums.size(); i++) {
		object_t new_obj;
		new_obj.value = nums[i];
		new_obj.index = i;
		
		unordered_set<object_t>::const_iterator find_itr = myset.find(new_obj);
		if ( find_itr != myset.end() ) {
			/* second value occurs, delete the old one and update to new index */
			myset.erase(find_itr);
		}
		myset.insert(new_obj);
	}
	
	/* find the answer */
	for (int i = 0; i < nums.size(); i++) {
		object_t find_obj;
		find_obj.value = target - nums[i];
		unordered_set<object_t>::const_iterator find_itr = myset.find(find_obj);
		if ( find_itr != myset.end() ) {
			if (find_itr->index == i) {
				continue;
			}			
			answer.push_back(i);
			answer.push_back(find_itr->index);
			break;
		}
	}
	return answer;
}

void print_ans(vector<int>& ans, vector<int>& nums)
{
	cout << ans[0] << ":" << nums[ans[0]] << ", " << ans[1] << ":" << nums[ans[1]] << endl;
}

int main()
{
	vector<int> nums_1, nums_2;
	vector<int> ans;
	
	nums_1.push_back(3);
	nums_1.push_back(2);
	nums_1.push_back(3);
	ans = twoSum(nums_1, 6);	
	print_ans(ans, nums_1);
	
	nums_2.push_back(3);
	nums_2.push_back(2);
	nums_2.push_back(4);
	ans = twoSum(nums_2, 6);	
	print_ans(ans, nums_2);


	return 0;
}
