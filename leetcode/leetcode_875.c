#include <stdio.h>
#define MAX(a, b) (((a)>(b))?(a):(b))

int binary_search(int* piles, int pilesSize, int h, int L, int R) {
    if (L == R) {
        return L;
    } else {
        int mid = (L + R) / 2;
        int temp = 0, i;
        for (i = 0; i < pilesSize; i++) {
            temp += (piles[i] + (mid - 1)) / mid;
        }
        if (temp > h) {
            return binary_search(piles, pilesSize, h, mid + 1, R);
        } else {
            return binary_search(piles, pilesSize, h, L , mid);
        }
    }
}

int minEatingSpeed(int* piles, int pilesSize, int h) {
    /* find the max numer in the piles first */
    int max = 0, i;
    for (i = 0; i < pilesSize; i++) {
        max = MAX(max, piles[i]);
    }
    return binary_search(piles, pilesSize, h, 1, max);
}

int main() {
    int piles[] = {30,11,23,4,20};
    int h = 6;
    printf("ans = %d\n",
           minEatingSpeed(piles, sizeof(piles)/sizeof(piles)[0], h));
    return 0;
}
