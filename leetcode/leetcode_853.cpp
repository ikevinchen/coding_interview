#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


struct Data {
    int position;
    float arriveTime;
};

bool DataCmp(const Data& a, const Data& b)
{
    // smallest comes first
    return a.position > b.position;
}


class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<Data> vec;
        for (int i = 0; i < position.size(); i++) {
            vec.push_back({position[i], (float)(target - position[i]) / (float)speed[i]});
        }
        sort(vec.begin(), vec.end(), DataCmp);

        int ans = 0;
        float head_time = 0;
        for (int i = 0; i < vec.size(); i++) {
            if (head_time == 0) {
                head_time = vec[i].arriveTime;
            } else if (vec[i].arriveTime > head_time) {
                /* there is a new head of car fleet */
                head_time = vec[i].arriveTime;
                ans++;
            }
        }
        if (head_time != 0) {
            ans++;
        }
        return ans;
    }
};


int main()
{
    #if 0
    int position[] = {10,8,0,5,3};
    int speed[] = {2,4,1,1,3};
    int target = 12;
    #else
    int position[] = {0,4,2};
    int speed[] = {2,1,3};
    int target = 10;
    #endif

    int n = sizeof(position) / sizeof(position[0]);
    vector<int> position_vect(position, position + n);
    vector<int> speed_vect(speed, speed + n);

    Solution S;
    cout << S.carFleet(target, position_vect, speed_vect) << endl;

    return 0;
}

