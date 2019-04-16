#include <stdio.h>
#include <stdlib.h>

void print_arr(int* arr, int arrSize) {
    
    int i;
    for (i = 0; i < arrSize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void reverse(int* arr, int start, int end) {
    int count = end-start+1;
    int *r_arr = malloc(count * sizeof(int));
    int i;
    for (i = 0; i < count; i++) {
        r_arr[i] = arr[end - i];
    }
    for (i = 0; i < count; i++) {
        arr[start + i] = r_arr[i];
    }
    free(r_arr);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void find_index_of_bigger(int* arr, int start, int end, int target, int *ret_index) {
    /* assume that the arr ios sorted by decending order 
     *   ex. arr = 10,  7,  4,  3,  1
                   [1] [2] [3] [4] [5]
                target = 3 
            ==> ret_index = 3 (arr[3] = 4 is the next bigger than target value)
     */
    int i;
    for (i = end; i >= start; i--) {
        if (arr[i] > target) {
            *ret_index = i;
            return;
        }
    }
    *ret_index = -1;
}

void nextPermutation(int* nums, int numsSize) {
    /*
        ex. nums = 3,  10,  7,  4,  3,  1
                   [0] [1] [2] [3] [4] [5]
          step 1. from the end to begining, find the number that become smaller
                    ==> get index 0 (nums[0] = 3)
          step 2. during range index 1 ~ 5, find the index of next bigger of 3
                    ==> get index 3
          step 3. swap index 0 and 3
                        nums = 4,  10,  7,  3,  3,  1
                               [0] [1] [2] [3] [4] [5]
                  then reverse index 1 ~ 5
                        nums = 4,  1,   3,  3,  7,  10
                               [0] [1] [2] [3] [4] [5]
     */

    /* step 1 */
    int i;
    int find_first_smaller_index = -1;
    for (i = numsSize - 2; i >= 0; i--) {
        if (nums[i] < nums[i+1]) {
            find_first_smaller_index = i;
            break;
        }
    }

    /* step 2 */
    int reverse_start = 0;
    int reverse_end = numsSize - 1;
    if (find_first_smaller_index != -1) {
        int index_of_next_bigger = -1;
        find_index_of_bigger(nums, find_first_smaller_index + 1, numsSize - 1,
                             nums[find_first_smaller_index],
                             &index_of_next_bigger);
        swap(&(nums[find_first_smaller_index]), &(nums[index_of_next_bigger]));
        reverse_start = find_first_smaller_index + 1;
    }

    /* step 3 */
    reverse(nums, reverse_start, reverse_end);
}


int main()
{
    int arr_1[3] = {1, 2, 3};
    int arr_2[3] = {3, 2, 1};
    int arr_3[3] = {1, 1, 5};
    int arr_4[6] = {3, 10, 7, 4, 3, 1};

    nextPermutation(arr_1, sizeof(arr_1) / sizeof(int));
    print_arr(arr_1, sizeof(arr_1) / sizeof(int));
    
    nextPermutation(arr_2, sizeof(arr_2) / sizeof(int));
    print_arr(arr_2, sizeof(arr_2) / sizeof(int));
    
    nextPermutation(arr_3, sizeof(arr_3) / sizeof(int));
    print_arr(arr_3, sizeof(arr_3) / sizeof(int));

    nextPermutation(arr_4, sizeof(arr_4) / sizeof(int));
    print_arr(arr_4, sizeof(arr_4) / sizeof(int));
    return 0;
}
