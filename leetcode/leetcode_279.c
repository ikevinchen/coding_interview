#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MIN(a, b) (((a) < (b))? (a): (b))

#if 1
int numSquares(int n){
	int **DP = NULL;
	int n_sqrt = (int)sqrt((double)n);
	int i, j, answer;
	
	//printf("n_sqrt = %d\n", n_sqrt);
	
	/* 
	 * DP[0~n][1~n_sqrt]
	 *    
	 */
	DP = malloc((n + 1) * sizeof(int*));
	for (i = 0; i <= n; i++) {
		DP[i] = malloc((1 + n_sqrt) * sizeof(int));
	}
	
	for (i = 0; i <= n; i++) {
		for (j = 1; j <= n_sqrt; j++) {
			if (i == 0) {
				DP[i][j] = 0;
			} else if (j == 1) {
				DP[i][j] = i;
			} else {
				//printf("calculate DP[%d][%d]\n", i, j);
				int min = DP[i][j - 1];
				//printf("  min = %d\n", min);
				int use_num = 1; /* the number of using j^2 */
				while (i - (use_num * j * j) >= 0) {
					//printf("  DP[%d][%d] = %d, ",
					       // i - (use_num * j * j), j - 1,
							//DP[i - (use_num * j * j)][j - 1]);
					min = MIN(min, DP[i - (use_num * j * j)][j - 1] + use_num);
					use_num++;
					//printf("  min = %d\n", min);
				}
				DP[i][j] = min;
			}
		}
	}
	
	answer = DP[n][n_sqrt];
	for (i = 0; i <= n; i++) {
		free(DP[i]);
		DP[i] = NULL;
	}
	free(DP); 
	DP = NULL;
	return answer;	
}
#endif

int main()
{
	printf("%d\n", numSquares(1));
	printf("%d\n", numSquares(2));
	printf("%d\n", numSquares(3));
	printf("%d\n", numSquares(4));
	printf("%d\n", numSquares(12));
	printf("%d\n", numSquares(57));
	printf("%d\n", numSquares(7115));
	return 0;
}
