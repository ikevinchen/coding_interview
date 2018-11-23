#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_arr(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int arr[], int index_a, int index_b) {
    int temp = arr[index_a];
    arr[index_a] = arr[index_b];
    arr[index_b] = temp;
}

void quick_sort(int arr[], int left, int right) {
    
    if (left >= right) {
        return;
    }

    /* pick pivot, and place it to the rightmost */
    srand(time(NULL));
    int pivot_index = left + rand() % (right - left + 1);
    int pivot = arr[pivot_index];
    swap(arr, pivot_index, right);
    
    /* start to swap (left to right - 1) */
    int left_i = left, right_i = right - 1;
    while (left_i != right_i) {
        if (arr[left_i] < pivot) {
            left_i++;
        } else if (arr[right_i] >= pivot) {
            right_i--;
        } else {
            swap(arr, left_i, right_i);
        }
    }

    /* 
     * After swap finish,
     *     A    B    C    D    E  |  F
     *    --------  ---  -------- | ---
     *     < pivot  cur  >= pivot | (pivot)
     *     
     *     case 1. if cur < pivot
     *              ==> recusive to qsort [A, C] , [D, F]
     *     case 2. if cur >= pivot
     *              means that F is the C~E all be larger than F
     *              ==> swap C, F
     *                  recusive to qsort [A, B] , [D, F]
     *     In this way, we could recusive to sub-qsort even if cur is at boundary
     */
    int cur = left_i;    
    if (arr[cur] < pivot) {
        quick_sort(arr, left, cur);
        quick_sort(arr, cur+1, right);
    } else {
        swap(arr, cur, right);
        quick_sort(arr, left, cur - 1);
        quick_sort(arr, cur+1, right);
    }
}

int main() {
    int array_1[5] = {2, 1, 5, 4, 3};
    int array_2[5] = {2, 2, 2, 2, 2};
    int array_3[5] = {5, 4, 3, 2, 1};
    quick_sort(array_1, 0, 4);
    print_arr(array_1, 5);
    quick_sort(array_2, 0, 4);
    print_arr(array_2, 5);
    quick_sort(array_3, 0, 4);
    print_arr(array_3, 5);
    return 0;
}
