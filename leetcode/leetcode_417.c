#include <stdio.h>
#include <stdlib.h>


void arr_alloc_1d(int **arr, int len, int val) {
	int i;
	(*arr) = malloc(len * sizeof(int));
	for (i = 0; i < len; i++) {
		(*arr)[i] = val;
	}
}

void arr_alloc(int ***arr, int x, int y) {
	int i;
	(*arr) = malloc(x * sizeof(int*));
	for (i = 0; i < x; i++) {
		(*arr)[i] = malloc(y * sizeof(int));
	}
}

void arr_free(int ***arr, int x, int y) {
	int i;
	for (i = 0; i < x; i++) {
		free((*arr)[i]);
	}
	free(*arr);
	*arr = NULL;
}

void arr_init(int **arr, int x, int y, int val) {
	int i, j;
	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			arr[i][j] = val;
		}
	}
}

void arr_dfs(int **const heights, int map_x, int map_y, int x, int y,
             int **trace, int **result, int *ans_num) {
	if (trace[x][y] == 1) {
		return;
	}
	result[x][y]++;
	trace[x][y] = 1;
	if (result[x][y] == 2) {
		(*ans_num)++;
	}
	// left
	if (x - 1 >= 0 && heights[x - 1][y] >= heights[x][y]) {
		arr_dfs(heights, map_x, map_y, x - 1, y, trace, result, ans_num);
	}
	// right
	if (x + 1 < map_x && heights[x + 1][y] >= heights[x][y]) {
		arr_dfs(heights, map_x, map_y, x + 1, y, trace, result, ans_num);
	}
	// up
	if (y - 1 >= 0 && heights[x][y - 1] >= heights[x][y]) {
		arr_dfs(heights, map_x, map_y, x, y - 1, trace, result, ans_num);
	}
	// down
	if (y + 1 < map_y && heights[x][y + 1] >= heights[x][y]) {
		arr_dfs(heights, map_x, map_y, x, y + 1, trace, result, ans_num);
	}
}

void arr_dump(int **const arr, int x, int y) {
	int i, j;
	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			printf("%2d", arr[i][j]);
		}
		printf("\n");
	}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pacificAtlantic(int** heights, int heightsSize, int* heightsColSize, int* returnSize, int** returnColumnSizes){
	int **trace_arr = NULL, **result_arr = NULL;
	int X_NUM = heightsSize;
	int Y_NUM = heightsColSize[0];
	int x, y, i, j, ans_num = 0;
	int **ans_arr = NULL;
	int *ans_arr_colsize = NULL;

	arr_alloc(&trace_arr, X_NUM, Y_NUM);
	arr_alloc(&result_arr, X_NUM, Y_NUM);
	arr_init(result_arr, X_NUM, Y_NUM, 0);

	/* trverse from Pacific Ocean */
	arr_init(trace_arr, X_NUM, Y_NUM, 0);
	for (y = 0; y < Y_NUM; y++) {
		arr_dfs(heights, X_NUM, Y_NUM, 0, y, trace_arr, result_arr, &ans_num);
	}
	for (x = 1; x < X_NUM; x++) {
		arr_dfs(heights, X_NUM, Y_NUM, x, 0, trace_arr, result_arr, &ans_num);
	}
	/* trverse from Atlantic  Ocean */
	arr_init(trace_arr, X_NUM, Y_NUM, 0);
	for (y = 0; y < Y_NUM; y++) {
		arr_dfs(heights, X_NUM, Y_NUM, X_NUM - 1, y, trace_arr, result_arr, &ans_num);
	}
	for (x = 0; x < X_NUM - 1; x++) {
		arr_dfs(heights, X_NUM, Y_NUM, x, Y_NUM - 1, trace_arr, result_arr, &ans_num);
	}
	/* output the answer */
	arr_alloc(&ans_arr, ans_num, 2);
	arr_alloc_1d(&ans_arr_colsize, ans_num, 2);
	i = 0;
	for (x = 0; x < X_NUM; x++) {
		for (y = 0; y < Y_NUM; y++) {
			if (result_arr[x][y] == 2) {
				ans_arr[i][0] = x;
				ans_arr[i][1] = y;
				i++;
			}
		}
	}
	*returnSize = ans_num;
	*returnColumnSizes = ans_arr_colsize;
	arr_free(&trace_arr, X_NUM, Y_NUM);
	arr_free(&result_arr, X_NUM, Y_NUM);
	return ans_arr;
}


int main()
{
	int h_arr[5][5] = {{1,2,2,3,5},
	                   {3,2,3,4,4},
				       {2,4,5,3,1},
				       {6,7,1,4,5},
				       {5,1,1,2,4}};
    int h_arr_col_size[] = {5};
	int *h_ptr[5] = {h_arr[0], h_arr[1], h_arr[2], h_arr[3], h_arr[4]};


	int **ans_arr;
	int *ans_arr_col_size;
	int ans_num;

	ans_arr = pacificAtlantic(h_ptr, sizeof(h_arr)/sizeof(h_arr[0]), h_arr_col_size, &ans_num, &ans_arr_col_size);
	arr_dump(ans_arr, ans_num, ans_arr_col_size[0]);
	return 0;
}
