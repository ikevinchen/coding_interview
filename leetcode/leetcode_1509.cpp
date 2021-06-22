#include <iostream>
#include <vector>
#include <algorithm>
#define MIN(a, b) ((a)<(b))?(a):(b);
using namespace std;

class Solution {
public:
    int minDifference(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        if (nums.size() < 5) {
            return 0;
        }
        int answer;
        int N = nums.size() - 1;
        /* remove lefest 3 elements */
        answer = nums[N] - nums[3];
        /* remove lefest 2 elements, rightest 1 elements */
        answer = MIN(answer, nums[N - 1] - nums[2]);
        /* remove lefest 1 elements, rightest 2 elements */
        answer = MIN(answer, nums[N - 2] - nums[1]);
        /* remove rightest 3 elements */
        answer = MIN(answer, nums[N - 3] - nums[0]);
        return answer;
    }
};

int main()
{
    int arr[] = {6,6,0,1,1,4,6};
    int n = sizeof(arr) / sizeof(arr[0]);
    vector<int> vect(arr, arr + n);
    Solution S;
    cout << S.minDifference(vect) << endl;
    return 0;
}
