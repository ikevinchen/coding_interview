#if 0
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main()
{
	multiset<int> myset;
	myset.insert(1);
	myset.insert(2);
	myset.insert(3);
	myset.insert(3);
	myset.insert(5);

	cout << myset.lower_bound (3) - myset.begin() << endl; /* this is linear time ... */
}
#endif


/*
   input : -10000 ~ 10000
   changes to 0 ~ 20000

   2^14 = 16384
   2^15 = 32768
 */

#include <iostream>
#include <vector>
#define POW_2(N) (1 << (N))
#define MAX_DEPTH 15
#define MAX_NUM (POW_2(MAX_DEPTH) - 1)
#define ARR_MAX (POW_2(MAX_DEPTH + 1))
using namespace std;

/*
   ex. MAX_DEPTH = 3

   depth           arr[index]

    3     [ 8] [ 9] [10] [11] [12] [13] [14] [15]
    2     [   4   ] [   5   ] [   6   ] [   7   ]
    1     [        2        ] [        3        ]
    0     [                  1                  ]

 */

class Solution {
public:
    Solution() {
        int i;
        for (i = 0; i < MAX_NUM * 2; i++) {
            arr[i] = 0;
        }
    }
    vector<int> countSmaller(vector<int>& nums) {
        vector <int> ans;
        ans.resize(nums.size());

        for (int i = nums.size() - 1; i >=0; i--) {
            int insert_value = nums[i] + 10000;
            touch(insert_value);
            if (insert_value == 0) {
                ans[i] = 0;
            } else {
                ans[i] = query(0, insert_value - 1, 0, 1);
            }
        }
        return ans;
    }
    void touch(int num) {
        int index = POW_2(MAX_DEPTH) + num;
        if (index >= ARR_MAX) {
            printf("error\n");
            return;
        }
        arr[index]++;
        while(index != 1) {
            index = index / 2;
            arr[index]++;
        }
    }
    int query(int l, int r, int depth, int index) {
        int num_in_depth   = POW_2(MAX_DEPTH - depth);
        int index_in_depth = index % POW_2(depth);
        int L = num_in_depth * index_in_depth;
        int R = L + num_in_depth - 1;
        int L1 = -1, R1 = -1, L2 = -1, R2 = -1;
        if (num_in_depth >= 2) {
            L1 = L, R1 = L1 + (num_in_depth/2 - 1);
            R2 = R, L2 = R2 - (num_in_depth/2 - 1);
        }
        /*
            [L1            R1] [L2            R2]
            [L            (index)              R]
             l <-case 1 ---------------------> r
             l <-case 2-----------------> r
             l <-case 3-> r

         */
        if (l != L) {
            printf("error\n");
            return -1;
        } else if (r == R) {
            return arr[index];
        } else if (r > R1) {
            return query(l, R1, depth + 1, index * 2) +
                   query(L2, r, depth + 1, index * 2 + 1);
        } else {
            return query(l, r, depth + 1, index * 2);
        }
    }
private:
    int arr[ARR_MAX];
};

int main()
{
    Solution S;
    #if 0
    S.touch(0); S.touch(2); S.touch(7); S.touch(1); S.touch(0); S.touch(2);
    for (int i = 0; i <= 7; i++) {
        printf("0 ~ %d : %d\n", i, S.query(0, i, 0, 1));
    }
    #endif

    int arr[] = {0, 2, -7, 1, 0, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    vector<int> vect(arr, arr + n);
    vector<int> ans = S.countSmaller(vect);
    for (int i = 0; i < vect.size(); i++) {
        printf("%2d ", vect[i]);
    }
    printf("\n");
    for (int i = 0; i < ans.size(); i++) {
        printf("%2d ", ans[i]);
    }
    printf("\n");

    return 0;
}
