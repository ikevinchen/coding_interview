#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) (((a)>=(b))?(a):(b))
#define MIN(a, b) (((a)<=(b))?(a):(b))

int search_left(int* arr, int left, int right,
                int left_limit, int right_limit, int target)
{
    int mid;
    
    if (left == right) {
        if (arr[left] == target) {
            return left;
        } else {
            return -1;
        }
    }
    
    mid = (left + right) / 2;
    
    if (arr[mid] == target) {
        if (mid == left_limit || arr[mid - 1] != target) {
            return mid;
        }
        right = MAX(mid - 1, left_limit);
        return search_left(arr, left, right, left_limit, right_limit, target);
    } else if (arr[mid] < target) {
        left = MIN(mid + 1, right_limit);
        return search_left(arr, left, right, left_limit, right_limit, target);
    } else {
        right = MAX(mid - 1, left_limit);
        return search_left(arr, left, right, left_limit, right_limit, target);
    }
}

int search_right(int* arr, int left, int right,
                int left_limit, int right_limit, int target)
{
    int mid;
    
    if (left == right) {
        if (arr[left] == target) {
            return left;
        } else {
            return -1;
        }
    }
    
    mid = (left + right) / 2;
    
    if (arr[mid] == target) {
        if (mid == right_limit || arr[mid + 1] != target) {
            return mid;
        }
        left = MIN(mid + 1, right_limit);
        return search_right(arr, left, right, left_limit, right_limit, target);
    } else if (arr[mid] < target) {
        left = MIN(mid + 1, right_limit);
        return search_right(arr, left, right, left_limit, right_limit, target);
    } else {
        right = MAX(mid - 1, left_limit);
        return search_right(arr, left, right, left_limit, right_limit, target);
    }
}

int* searchRange(int* nums, int numsSize, int target, int* returnSize)
{
	int *answer = malloc(2 * sizeof(int));
	answer[0] = answer[1] = -1;
	*returnSize = 2;
	
	if (numsSize != 0) {    
		answer[0] = search_left(nums, 0, numsSize - 1, 0, numsSize - 1, target); 
		answer[1] = search_right(nums, 0, numsSize - 1, 0, numsSize - 1, target); 		
	}
    
    return answer;
}

int main()
{
    int arr[] = {2, 4, 6, 6, 6, 7, 8};
    int returnSize;
    int *ans;
    ans = searchRange(arr, 7, 6, &returnSize);
    printf("%d : %d %d \n", returnSize, ans[0], ans[1]);

    return 0;
}
