#include <iostream>     // std::cout
#include <algorithm>    // std::binary_search, std::sort
#include <vector>       // std::vector

using namespace std;

class Solution {
public:
    Solution(vector<int>& w) {
        
    }
    
    int pickIndex() {
        
    }
private:
	int binary_search (vector<int>& array, int target) {
		/* ex.
			   [0] [1] [2] [3]  [4]
				1	4	6	7   11
			if target = 0   ==> return index 0
			           1~3  ==> return index 1
					   4~5  ==> return index 2
					    6   ==> return index 3
					   7~10 ==> return index 4
		 */
		int left = 0;
		int right = array.size()-1;
		while (left <= right) {
			int mid = (left + right) / 2;
		}
	}
};

int main()
{
	return 0;
}
