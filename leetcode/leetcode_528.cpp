#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <stdlib.h>

using namespace std;

class Solution {
public:
    Solution(vector<int>& w) {
		sum = 0;
        for (int i = 0; i < w.size(); i++) {
			sum += w[i];
			w_sum.push_back(sum);
		}
    }
    int pickIndex() {
        int r = rand() % sum;
		return binary_search(r);
    }
private:
	int sum;
	vector<int> w_sum;
    int binary_search (int target) {
        /* ex.
               [0] [1] [2] [3]  [4]
                1   4   6   7   11
            if target = 0   ==> return index 0
                       1~3  ==> return index 1
                       4~5  ==> return index 2
                        6   ==> return index 3
                       7~10 ==> return index 4
         */
        int left = 0;
        int right = w_sum.size()-1;
        while (left <= right) {
            int mid = (left + right) / 2;
            
            int mid_rnage_min = (mid == 0)? 0 : w_sum[mid - 1];
            int mid_rnage_max = w_sum[mid] - 1;
            
            if (target >= mid_rnage_min && target <= mid_rnage_max) {
                return mid;
            } else if (target < mid_rnage_min) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }
};

int main()
{
	vector<int> vect{ 1, 2}; 
	Solution S(vect);
	cout << S.pickIndex() << endl;
	cout << S.pickIndex() << endl;
	cout << S.pickIndex() << endl;
	cout << S.pickIndex() << endl;
	cout << S.pickIndex() << endl;
	cout << S.pickIndex() << endl;
	cout << S.pickIndex() << endl;
	cout << S.pickIndex() << endl;
	cout << S.pickIndex() << endl;
	cout << S.pickIndex() << endl;
	cout << S.pickIndex() << endl;
    return 0;
}
