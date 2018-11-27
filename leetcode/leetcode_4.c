#include <stdio.h>

int check(int arr1[], int arr1_left_num, int arr1_right_num,
          int arr2[], int arr2_left_num, int arr2_right_num) {
    /*
        arr 1 : OOOOOO XXXXX
                     a b
        arr 2 : OOOO XXXXXXX
                   c d
     */
    int index_a = -1 + arr1_left_num;
    int index_b = arr1_right_num == 0 ? -1 : index_a + 1;
    int index_c = -1 + arr2_left_num;
    int index_d = arr2_right_num == 0 ? -1 : index_c + 1;

    if (index_b != -1 && index_c != -1 &&
        arr1[index_b] < arr2[index_c]) {
        return 1; /* left part of array 1 should be more */
    }
    else if (index_a != -1 && index_d != -1 &&
             arr1[index_a] > arr2[index_d]) {
        return -1; /* left part of array 1 should be less */   
    }
    else {
        return 0;
    } 
}

double find_median(int nums1[], int nums1Size, int nums2[], int nums2Size) {
    int *arr_m, *arr_n;
    int arr_m_len, arr_n_len;
    int arr_total_len = nums1Size + nums2Size;

    if (nums1Size >= nums2Size) {
        arr_m_len = nums1Size; arr_n_len = nums2Size;
        arr_m = nums1;         arr_n = nums2;
    } else {
        arr_m_len = nums2Size; arr_n_len = nums1Size;
        arr_m = nums2;         arr_n = nums1;
    }

    /* binary search acoring to the left element number of arr_m
     * (the left part ele num = arr_total_len / 2 )
     *
     *  ex. arr_m_len = 8, arr_n_len = 3
     *       ==> search the left element number of arr_m 
     *           from 2 to 5 
     *
     *     arr_m (bigger)     OO|OOOOOO     OOOOO|OOO 
     *     arr_n (small)      OOO|          |OOO
     */
    int bs_left  = arr_total_len / 2 - arr_n_len;
    int bs_right = bs_left + arr_n_len;
    int bs_mid;
    int arr_m_left_num, arr_n_left_num;
    while (1) {
        int result;
        bs_mid = (bs_left + bs_right) / 2;
        arr_m_left_num = bs_mid;
        arr_n_left_num = arr_total_len / 2 - arr_m_left_num;
        result = check(arr_m, arr_m_left_num, arr_m_len - arr_m_left_num,
                       arr_n, arr_n_left_num, arr_n_len - arr_n_left_num);
        if (result > 0) {
            bs_left = bs_mid + 1;
        } else if (result < 0) {
            bs_right = bs_mid - 1;
        } else {
            break;
        }
    }

    /* output the answer

        arr m : OOOOOO XXXXX
                     a b
        arr n : OOOO XXXXXXX
                   c d
     */
    int index_a = -1 + arr_m_left_num;
    int index_b = arr_m_left_num == arr_m_len ? -1 : index_a + 1;
    int index_c = -1 + arr_n_left_num;
    int index_d = arr_n_left_num == arr_n_len ? -1 : index_c + 1;
    int left_num = arr_m_left_num + arr_n_left_num;

    int max_of_left, min_of_right;

    if (index_b == -1) {
        min_of_right = arr_n[index_d];
    } else if (index_d == -1) {
        min_of_right = arr_m[index_b];
    } else if (arr_m[index_b] < arr_n[index_d]) {
        min_of_right = arr_m[index_b];
    } else {
        min_of_right = arr_n[index_d];
    }

    if (index_a == -1) {
        max_of_left = arr_n[index_c];
    } else if (index_c == -1) {
        max_of_left = arr_m[index_a];
    } else if (arr_m[index_a] > arr_n[index_c]) {
        max_of_left = arr_m[index_a];
    } else {
        max_of_left = arr_n[index_c];
    }

    if (left_num * 2 < arr_total_len) {
        return min_of_right;
    } else if (left_num * 2 > arr_total_len) {
        return max_of_left;
    } else {
        return (min_of_right + max_of_left) / 2.0;
    }
}

int main() {
    int arr_a[] = {0, 1, 2, 3, 4};
    int arr_b[] = {0, 1, 2, 3, 4};

    printf("%f\n", find_median(&arr_a[0], 2, &arr_b[2], 2));
    printf("%f\n", find_median(&arr_a[0], 2, &arr_b[2], 1));
    printf("%f\n", find_median(&arr_a[0], 1, &arr_b[2], 2));
    printf("%f\n", find_median(&arr_a[0], 0, &arr_b[2], 2));
    printf("%f\n", find_median(&arr_a[0], 2, &arr_b[2], 0));
    printf("%f\n", find_median(&arr_a[0], 1, &arr_b[1], 4));

    return 0;
}
