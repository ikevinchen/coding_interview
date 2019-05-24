/*Input:  [0,1,2,4,5,7]
  Output: ["0->2","4->5","7"] */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
  
/* return the ending index of this range */
int find_the_range(vector<int>& nums, int index) {
	if (index == nums.size() - 1) {
		return index;
	}	
	if (nums[index + 1] != (nums[index] + 1)) {
		return index;
	}
	
	int last_check = 1;
	while (1) {
		int this_check_index = MIN(index + (last_check * 2), nums.size() - 1);
		if (nums[this_check_index] != (nums[index] + (this_check_index - index))) {
			return find_the_range(nums, index + last_check);
		}
		if (this_check_index == nums.size() - 1) {
			return this_check_index;
		}
		last_check = last_check * 2;
	}
}
  
vector<string> summaryRanges(vector<int>& nums) {
	vector<string> answer_vec;
	
	if (nums.size() == 0) {
		return answer_vec;
	}
	
	int idx_s = 0, idx_e;
	while (1) {
		stringstream ss;
		idx_e = find_the_range(nums, idx_s);
		if (idx_s == idx_e) {
			ss << nums[idx_s];
		} else {
			ss << nums[idx_s] << "->" << nums[idx_e];
		}
		answer_vec.push_back(ss.str());
		if (idx_e == nums.size() - 1) {
			break;
		}
		idx_s = idx_e + 1;
	}
	return answer_vec;
}

void Print(vector<string>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

int main()
{
	vector<int> vect;
	vect.push_back(1);
	vect.push_back(2);
	vect.push_back(4);
	vect.push_back(5);
	vect.push_back(6);
	vect.push_back(8);
	vector<string> answer = summaryRanges(vect);
	Print(answer);
	return 0;
}
