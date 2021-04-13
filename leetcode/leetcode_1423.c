#include <stdio.h>

int maxScore(int* cardPoints, int cardPointsSize, int k)
{
	int max = 0;

	if (k == cardPointsSize) {
		int i;
		for (i = 0; i < k; i++) {
			max += cardPoints[i];
		}
	} else {
		int ans = 0, i, left_num = k, right_num = 0;

		/* first case : left = k, right_num = 0 */
		for (i = 0; i < k; i++) {
			ans += cardPoints[i];
		}
		max = ans;

		/* check other cases : left = k-1 ~ 0, right_num = 1~k */
		for (i = 1; i <= k; i++) {
			ans -= cardPoints[k - i];
			ans += cardPoints[cardPointsSize - i];
			if (ans > max) {
				max = ans;
			}
		}
	}
	return max;
}

int main()
{
	int arr[] = {1,79,80,1,1,1,200,1};
	printf("%d\n", maxScore(arr, sizeof(arr)/sizeof(arr[0]), 3));
	printf("%d\n", maxScore(arr, sizeof(arr)/sizeof(arr[0]), 8));
	return 0;
}
