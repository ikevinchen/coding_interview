#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int weight_max = -1;
		int weight_sum = 0;
		for (int i = 0; i < weights.size(); i++) {
			weight_sum += weights[i];
			if (weights[i] > weight_max) {
				weight_max = weights[i];
			}
		}		
		
		int capacity_max = weight_sum;
		int capacity_min = weight_max;
		
		
		while (capacity_min != capacity_max) {
			int capacity = (capacity_min + capacity_max) / 2;
			int day = day_cal(capacity, weights);
			if (day <= D) {
				capacity_max = capacity;
			} else {
				capacity_min = capacity + 1;
			}
		}
		return capacity_min;
    }
private:
	int day_cal(int capacity, vector<int>& weights) {
		int days = 0;
		int sum = 0; 
		for (int i = 0; i < weights.size(); i++) {
			if (sum + weights[i] > capacity) {
				days++;
				sum = weights[i];
			} else {
				sum += weights[i];
			}
		}
		if (sum > 0) {
			days++;
		}
		return days;
	}
};

int main()
{
	Solution S;
	vector<int> vect1{1, 1, 1, 1, 1, 1, 1}; 
	cout << S.shipWithinDays(vect1, 1) << endl;
	cout << S.shipWithinDays(vect1, 2) << endl;
	cout << S.shipWithinDays(vect1, 7) << endl;
	cout << S.shipWithinDays(vect1, 8) << endl;
	vector<int> vect2{1,2,3,4,5,6,7,8,9,10}; 
	cout << S.shipWithinDays(vect2, 5) << endl;
	return 0;
}
