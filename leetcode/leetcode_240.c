#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

/* It has more quick way!! see leetcode Approach 4 in solution tab !*/

int search_recursice(int** matrix, int row_min, int row_max,
                     int col_min, int col_max, int target)
{
	printf("serach %d %d %d %d...", row_min, row_max, col_min, col_max);
	int row = (row_min + row_max) / 2;
	int col = (col_min + col_max) / 2;
	printf("[%d %d]\n", row, col);
	if (matrix[row][col] == target) {
		return true;
	} else if (matrix[row][col] > target) {
		int ans_1 = false, ans_2 = false;
		if (col - 1 >= col_min) {
			ans_1 = search_recursice(matrix, row_min, row_max,
			                                 col_min, col - 1, target);
		}
		if (row - 1 >= row_min) {
			ans_2  = search_recursice(matrix, row_min, row - 1,
			                                  col, col_max, target);
		}
		if (ans_1 == true || ans_2 == true) {
			return true;
		}
	} else {
		int ans_1 = false, ans_2 = false;
		if (col + 1 <= col_max) {
			ans_1 = search_recursice(matrix, row_min, row_max,
			                                 col + 1, col_max, target);
		}
		if (row + 1 <= row_max) {
			ans_2 = search_recursice(matrix, row + 1, row_max,
			                                 col_min, col, target);
		}
		if (ans_1 == true || ans_2 == true) {
			return true;
		}
	}
	return false;
}

int searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    return search_recursice(matrix, 0, matrixRowSize - 1,
	                                0, matrixColSize - 1, target);
}

int main()
{
	int **array;
	int i;
	array = malloc(sizeof(int*) * 5);
	for (i = 0; i < 5; i++) {
		array[i] = malloc(sizeof(int) * 5);
	}
	array[0][0] = 1; array[0][1] = 4; array[0][2] = 7; array[0][3] = 11; array[0][4] = 15;
	array[1][0] = 2; array[1][1] = 5; array[1][2] = 8; array[1][3] = 12; array[1][4] = 19;
	array[2][0] = 3; array[2][1] = 6; array[2][2] = 9; array[2][3] = 16; array[2][4] = 22;
	array[3][0] = 10; array[3][1] = 13; array[3][2] = 14; array[3][3] = 17; array[3][4] = 24;
	array[4][0] = 18; array[4][1] = 21; array[4][2] = 23; array[4][3] = 26; array[4][4] = 30;
	
	printf("%d\n", searchMatrix(array, 5, 5, 20));

	return 0;
}
