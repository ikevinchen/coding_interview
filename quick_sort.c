#include <stdio.h>

void print_arr(int arr[], int num) {
    int i;
    for (i = 0; i < num; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int arr[], int left, int right) {
    if (left == right)
        return;
    int pivot_index = (left + right) / 2;
    int pivot = arr[pivot_index];
    int a = left, b = right;

    /*
        update the array to the following:
          [elements < pivot] [pivot] [elements >= pivot]
     */
    while(a < b) {
        /* swap number or update pivot position if need */
        if (a == pivot_index) {
            if (arr[b] < pivot) {
                swap(&arr[a], &arr[b]);
                pivot_index = b;
            }
        } else if (b == pivot_index) {
            if (arr[a] >= pivot) {
                swap(&arr[a], &arr[b]);
                pivot_index = a;
            }
        } else {
            if (arr[a] >= pivot && arr[b] < pivot) {
                swap(&arr[a], &arr[b]);
            }
        }

        /* move pointer, but cannot exceed pivot */
        if (arr[a] < pivot && a != pivot_index) {
            a++;
        }
        if (arr[b] >= pivot && b != pivot_index) {
            b--;
        }
    }

    /* accoring to the pivot postion, recusive the next sorting */
    if (pivot_index > left) {
        quick_sort(arr, left, pivot_index - 1);
    }
    if (pivot_index < right) {
        quick_sort(arr, pivot_index + 1, right);
    }
}


int main() {
    int array_1[6] = {2, 3, 10, 6, 9, 1};
    int array_2[6] = {6, 6, 6, 6, 6, 6};
    int array_3[6] = {4, 5, 3, 6, 7, 6};
    quick_sort(array_1, 0, 5);
    print_arr(array_1, 6);
    quick_sort(array_2, 0, 5);
    print_arr(array_2, 6);
    quick_sort(array_3, 0, 5);
    print_arr(array_3, 6);

    return 0;
}
