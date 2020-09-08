#include <iostream>
#include <vector>
#define MAX(a, b) (((a)>=(b))?(a):(b))
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size()==0) {
			return -1;
		}
		vector<int> S; /* S[i] = the max interval ending at index i */
		int answer = nums[0];
		S.push_back(nums[0]);
		for (int i = 1; i < nums.size(); i++) {
			S.push_back(MAX(nums[i], S[i - 1] + nums[i]));
			answer = MAX(answer, S[i]);
		}
		return answer;
    }
};

int main()
{
	Solution S;

	
	int arr[] = {-2,1,-3,4,-1,2,1,-5,4}; 
    int n = sizeof(arr) / sizeof(arr[0]);   
    vector<int> nums(arr, arr + n); 	

	cout << S.maxSubArray(nums) << endl;
	return 0;
}

