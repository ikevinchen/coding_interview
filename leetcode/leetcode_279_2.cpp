#include <vector>
#include <iostream>
#define MIN(a, b) (((a) < (b))? (a): (b))
using namespace std;

/* record DP[0~n] */
vector<int> DP;

int numSquares(int n) {
	/* init DP[0] = 0 */
	if (DP.size() == 0) {
		DP.push_back(0);
	}
	/* return answer if existed */
	if (DP.size() - 1 >= n) {
		return DP[n];
	}
	/* fill DP */
	int fill_min = DP.size();
	int fill_max = n;
	for (int num = fill_min; num <= fill_max; num++) {
		/* DP[num] = min(1 + DP[num - anyone perfect number]) 
		 *  ex.  DP[12] = min ( DP[12 - 1*1] + 1,
		 *                      DP[12 - 2*2] + 1,
		 *                      DP[12 - 3*3] + 1 )
		 */
		int min = DP[num - 1 * 1] + 1;
		int cur = 2;
		while (cur * cur <= num) {
			min = MIN(min, DP[num - cur * cur] + 1);
			cur++;
		}
		DP.push_back(min); /* push DP[num] */
	}
	return DP[n];
}

int main()
{
	cout << numSquares(1) << endl;
	cout << numSquares(2) << endl;
	cout << numSquares(3) << endl;
	cout << numSquares(4) << endl;
	cout << numSquares(12) << endl;
	return 0;
}
