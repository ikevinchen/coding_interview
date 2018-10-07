#include <stdio.h>

int arr_buf[10];

void print_arr(int arr[], int num) {
    int i;
    for (i = 0; i < num; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void merge(int arr[], int left, int right) {
    if(left == right) return;

    int mid = (left + right) / 2;
    merge(arr, left, mid);
    merge(arr, mid + 1, right);

    int a_start, a_end, a_i;
    int b_start, b_end, b_i;
    int write_i;
    a_start = a_i = left; a_end = mid;
    b_start = b_i = mid + 1; b_end = right;
    write_i = left;

    while (a_i <= a_end || b_i <= b_end) {
        if (a_i > a_end) {
            arr_buf[write_i++] = arr[b_i++];
        } else if (b_i > b_end) {
            arr_buf[write_i++] = arr[a_i++];
        } else if (arr[a_i] <= arr[b_i]) {
            arr_buf[write_i++] = arr[a_i++];
        } else {
            arr_buf[write_i++] = arr[b_i++];
        }
    }



    for(write_i = left; write_i <= right; write_i++) {
        arr[write_i] = arr_buf[write_i];
    }
}


int main() {
    int array[6] = {3, 5, 6, 1, 10, 2};
    merge(array, 0, 5);
    print_arr(array, 6);
}

