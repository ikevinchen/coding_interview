/*
 *  If your thought is that we creare a priority queue to save each entry
 *      Entry (distance, bike_index, worker_index)
 *         with compare function (distance, then worker_index, then bike_index)
 *      time complexity would be O(N*N) + N*N lg (N*N)
 *  However, there is no need to use priority queue becuase
 *      a) there is no new inserted node durung run-time
 *      b) we alwayd take the smallest distance (then worker_index, then bike_index)
 *  So, it is okay just to "categorize" all enties to the array
 *  and its order has been alreay sorted to distance, then worker_index, then bike_index
 */
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define MAX_NUM (1000)
#define MAX_DST (2000)
#define ABS(x) (((x) < 0)?(-(x)):(x))
#define DST(x1, y1, x2, y2) ((ABS((x1)-(x2)))+(ABS((y1)-(y2))))

struct Entry {
    int bike_index;
    int worker_index;
};

class Solution {
public:
    vector<int> assignBikes(vector<vector<int> >& workers, vector<vector<int> >& bikes) {
        match_num = 0;
        for (int i = 0; i < MAX_NUM; i++) {
            bike_select[i] = false;
            worker_select[i] = false;
        }

        for (int i = 0; i < workers.size(); i++) {
            for (int j = 0; j < bikes.size(); j++) {
                Entry new_entry;
                new_entry.worker_index = i;
                new_entry.bike_index = j;

                int distance = DST(workers[i][0], workers[i][1],
                                   bikes[j][0], bikes[j][1]);
                distance_arr[distance].push_back(new_entry);
            }
        }


        vector<int> answer;
        answer.resize(workers.size(),-1);
        for (int i = 0; i <= MAX_DST; i++) {
            for (int j = 0; j < distance_arr[i].size(); j++) {
                Entry entry = distance_arr[i][j];
                if (bike_select[entry.bike_index] == true ||
                    worker_select[entry.worker_index] == true) {
                    continue;
                }
                answer[entry.worker_index] = entry.bike_index;
                bike_select[entry.bike_index] = true;
                worker_select[entry.worker_index] = true;
                match_num++;
                if (match_num == workers.size()) {
                    return answer;
                }
            }
        }
        return answer;
    }
private:
    int match_num;
    bool bike_select[MAX_NUM];
    bool worker_select[MAX_NUM];
    vector<Entry> distance_arr[MAX_DST+1];
};

int main()
{
    Solution S;
    vector<vector<int> > bikes{{ 0, 1},
                               { 2, 1}};
    vector<vector<int> > workers{{ 1, 0},{1, 2}};
    vector<int> answer = S.assignBikes(workers, bikes);
    for (int i = 0; i < workers.size(); i++) {
        cout << "worker " << i << " : bike " << answer[i] << endl;
    }
    return 0;
}
