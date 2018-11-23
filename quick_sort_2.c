#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void quick_sort(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }

    srand(time(NULL));
    int pivot = arr[left + rand() % (right - left + 1)];
    int left_i = left, right_i = right;

    while (left_i != right_i) {
        if (arr[left_i] < pivot) {
            left_i++;
        } else if (arr[right_i] >= pivot) {
            right_i--;
        } else {
            int temp = arr[left_i];
            arr[left_i] = arr[right_i];
            arr[right_i] = temp;
        }
    }

    int cur = left_i;
    if (arr[cur] == pivot) {
        quick_sort(arr, left, cur-1);
        quick_sort(arr, cur+1, right);
    } else (arr[cur] < pivot) {
        quick_sort(arr, left, cur);
        quick_sort(arr, cur+1, right);
    } else {
        quick_sort(arr, left, cur-1);
        quick_sort(arr, cur, right);
    }
}


int main() {
    return 0;
}