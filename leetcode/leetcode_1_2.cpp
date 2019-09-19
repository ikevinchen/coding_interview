/* g++ leetcode_1.cpp -std=c++0x if lower version of g++ */
/* use unordered_map instead */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


vector<int> twoSum(vector<int>& nums, int target) {
	vector<int> answer;
	unordered_map<int, int> mymap;	

	/* insert data into hash, it would update index if there is same value second time */
	for (int i = 0; i < nums.size(); i++) {
		mymap[nums[i]] = i;
	}
	
	/* find the answer */
	for (int i = 0; i < nums.size(); i++) {
		unordered_map<int,int>::iterator find_itr = mymap.find(target - nums[i]);
		if ( find_itr != mymap.end() ) {
			if (find_itr->second == i) {
				continue;
			}			
			answer.push_back(i);
			answer.push_back(find_itr->second);
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
