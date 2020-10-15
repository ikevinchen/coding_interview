#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        if (heights.size() == 0) {
            return 0;
        }
        
        vector<int> L, R;
        int N = heights.size();
        L.resize(N);
        R.resize(N);
        
        /*              O
         *            O O O O
         *      O O O O O O O
         *      O O O O O O O
         *     (0 1 2 3 4 5 6)
         *
         *    L 0 1 0 1 0 3 6   ---->
         *    R 6 5 3 2 0 0 0   <----
         */
        
        L[0] = 0;
        for (int i = 1; i < N; i++) {
            int sum = 0;
            int j = i - 1;
            while (j >= 0) {
                if (heights[j] < heights[i]) {
                    break;
                } else {
                    sum = sum + 1 + L[j];
                    j = j - 1 - L[j];            
                }
            }
            L[i] = sum;
        }
        
        R[N - 1] = 0;
        for (int i = N -2; i >= 0; i--) {
            int sum = 0;
            int j = i + 1;
            while (j < N) {
                if (heights[j] < heights[i]) {
                    break;
                } else {        
                    sum = sum + 1 + R[j];
                    j = j + 1 + R[j];    
                }
            }
            R[i] = sum;
        }
        
        int max = 0;
        for (int i = 0; i < N; i++) {
            int answer = (1 + L[i] + R[i]) * heights[i];
            if (answer > max) {
                max = answer;
            }
        }        
        return max;
    }
};

int main()
{
    int arr_1[] = {2, 2, 3, 3, 4, 3, 2}; 
    int arr_2[] = {1, 1, 1, 1}; 
    int arr_3[] = {1}; 
    int n;
    Solution S;
    
    n = sizeof(arr_1) / sizeof(arr_1[0]);   
    vector<int> vect_1(arr_1, arr_1 + n);     
    cout << S.largestRectangleArea(vect_1) << "\n";
    
    n = sizeof(arr_2) / sizeof(arr_2[0]);   
    vector<int> vect_2(arr_2, arr_2 + n);     
    cout << S.largestRectangleArea(vect_2) << "\n";
    
    n = sizeof(arr_3) / sizeof(arr_3[0]);   
    vector<int> vect_3(arr_3, arr_3 + n);     
    cout << S.largestRectangleArea(vect_3) << "\n";
    
    return 0;
}
