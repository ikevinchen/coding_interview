#include <iostream>
#include <map>
#include <vector>


/* 換成unordered map 會更快 */

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        map<int, int> sum_map; /* sum, count */
        
        /* add sum[0:0], sum[0:1], .... sum[0:N-1] into map */
        int temp_sum = 0;                
        for (int i = 0; i < nums.size(); i++) {
            temp_sum += nums[i];
            
            map<int,int>::iterator it;
            it = sum_map.find(temp_sum);
            if (it != sum_map.end()) {
                it->second++;
            } else {
                sum_map.insert(pair<int ,int>(temp_sum ,1));
            }            
        }
        
        /* start 
         *  ex. k = 0
         *     [0]  [1]  [2]  [3]  [4]
         *      1    -1   1   -1    1
         *
         *    initialized map:
         *         sum = 1, count = 3  (0~0, 0~2, 0~4)
         *         sum = 0, count = 2  (0~1, 0~3)
         *    [i = 0] answer = 2 (add 0~1, 0~3)
         *         sum = 0, count = 2  (1~2, 1~4)
         *         sum = -1, count = 2 (1~1, 1~3)   
         *    [i = 1] answer = 4 (add 1~2, 1~4)
         *         sum = 1, count = 2  (2~2, 2~4)
         *         sum = 0, count = 1 (2~3)
         *    [i = 2] answer = 5 (add 2~3)
         *         sum = 0, count = 1  (3~4)
         *         sum = -1, count = 1 (3~3)
         *    [i = 3] answer = 6 (add 3~4)
         *         sum = 1, count = 1  (4~4)
         *    [i = 4] answer = 6
         *
         */
        int answer = 0;
        temp_sum = 0;
        for (int i = 0; i < nums.size(); i++) {            
            
            /* find each range started with index i  */
            map<int,int>::iterator it;
            it = sum_map.find(k + temp_sum);
            if (it != sum_map.end()) {
                answer += it->second;
                //cout << "i = " << i << ", add " << it->second << endl;
            }    
            
            /* remove */
            temp_sum += nums[i];
            it = sum_map.find(temp_sum);
            if (it->second > 1) {
                it->second--;
            } else {
                sum_map.erase(it);   
            }
        }
        return answer;
    }
};
int main()
{
    Solution S;
    int n;
    int arr_0[] = {1, -1, 1, -1, 1}; 
    int arr_1[] = {1, 1, 1}; 
    
    n = sizeof(arr_0) / sizeof(arr_0[0]);   
    vector<int> vect_0(arr_0, arr_0 + n); 
    
    n = sizeof(arr_1) / sizeof(arr_1[0]);   
    vector<int> vect_1(arr_1, arr_1 + n); 
    
    cout << S.subarraySum(vect_0, 0) << endl;
    cout << S.subarraySum(vect_1, 2) << endl;
    return 0;
}
