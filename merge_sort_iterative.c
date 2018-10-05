#include <stdio.h>

int arr_buf[10];

void merge_sort(int arr[], int num) {
    /*
               X X X X X X X X
       base 1  _ _ _ _ _ _ _ _
       base 2  ___ ___ ___ ___
              (group 0)(group 1)
       base 4  _______ _______
              ( grpup 0       )
     */
    int base = 1;
    while (base < num) {
        int group = 0;
        int group_start;
        while ((group_start = group * (base * 2)) <= (num - 1)) {
            int a_start = group_start;
            int a_end   = a_start + base - 1;
            int b_start = group_start + base;
            int b_end   = b_start + base -1;
            if (a_end >= num) a_end = num - 1;
            if (b_end >= num) b_end = num - 1;
            int a_i = a_start;
            int b_i = b_start;
            int w = a_start;

            while (a_i <= a_end || b_i <= b_end) {
                if      (a_i > a_end) arr_buf[w++] = arr[b_i++];
                else if (b_i > b_end) arr_buf[w++] = arr[a_i++];
                else if (arr[a_i] <= arr[b_i]) arr_buf[w++] = arr[a_i++];
                else    arr_buf[w++] = arr[b_i++];
            }

            for (int i = a_start; i < w; i++) {
                arr[i] = arr_buf[i];
            }

            group++;
        }
        base = base * 2;
    }
}

void print_arr(int arr[], int num) {
    int i;
    for (i = 0; i < num; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int array[6] = {1, 3, 2, 7, 5, 4};
    merge_sort(array, 6);
    print_arr(array, 6);
    return 0;
}
