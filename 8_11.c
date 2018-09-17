#include <stdio.h>

#define N (50)

/*
    S[n][k] : 在可以使用(k+1)種幣值之下, 組成n的方法數
                (k = 0 : 可以使用硬幣1元)
                (k = 1 : 可以使用硬幣5, 1元)
                (k = 2 : 可以使用硬幣10, 5, 1元)

        S[any][0] = 1
        S[1][1]  =  (使用5元硬幣0個) S[1][0] = 1
        S[5][1]  =  (使用5元硬幣0個) S[5][0]
                   +(使用5元硬幣1個) S[0][0] = 1 + 1 = 2
        S[11][1] =  (使用5元硬幣0個) S[11][0]
                   +(使用5元硬幣1個) S[6][0]
                   +(使用5元硬幣2個) S[1][0] = 1 + 1 + 1 = 3
        S[11][2]=  (使用10元硬幣0個)S[11][1]
                  +(使用10元硬幣1個) S[1][1] = 3 + 1 = 4
*/

int main()
{
    int S[N+1][4];
    int coin_value[4] = {1, 5, 10, 25};
    int n, k;

    for (k = 0; k <= 3; k++) {
        for (n = 0; n < N; n++) {
            if (k == 0) {
                S[n][k] = 1;
            } else {
                int temp = S[n][k-1];
                int cur = n - coin_value[k];
                while(cur >= 0) {
                    temp += S[cur][k-1];
                    cur = cur - coin_value[k];
                }
                S[n][k] = temp;
            }
        }
    }


    printf("%d\n", S[11][2]);
    printf("%d\n", S[25][3]);

    return 0;
}
