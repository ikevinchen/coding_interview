#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXLEN (200)
#define MAX(a, b) (((a)>(b))?(a):(b))

struct data_t {
    int x;
    int y;
    int value;
};

bool compareData(data_t i1, data_t i2)
{
    return (i1.value > i2.value);
}

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        vector<data_t> sort_array;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                data_t data = {i, j, matrix[i][j]};
                sort_array.push_back(data);
            }
        }
        sort(sort_array.begin(), sort_array.end(), compareData);

        int answer = 0;
        int longest_path[MAXLEN][MAXLEN] = {0};
        for (int i = 0; i < sort_array.size(); i++) {
            int max_of_neighbor = -1;
            data_t cur = sort_array[i];
            if (cur.x - 1 >= 0 && matrix[cur.x - 1][cur.y] > matrix[cur.x][cur.y]) {
                max_of_neighbor = MAX(max_of_neighbor, longest_path[cur.x - 1][cur.y]);
            }
            if (cur.x + 1 < matrix.size() && matrix[cur.x + 1][cur.y] > matrix[cur.x][cur.y]) {
                max_of_neighbor = MAX(max_of_neighbor, longest_path[cur.x + 1][cur.y]);
            }
            if (cur.y - 1 >= 0 && matrix[cur.x][cur.y - 1] > matrix[cur.x][cur.y]) {
                max_of_neighbor = MAX(max_of_neighbor, longest_path[cur.x][cur.y - 1]);
            }
            if (cur.y + 1 < matrix[0].size() && matrix[cur.x][cur.y + 1] > matrix[cur.x][cur.y]) {
                max_of_neighbor = MAX(max_of_neighbor, longest_path[cur.x][cur.y + 1]);
            }
            if (max_of_neighbor == -1) {
                longest_path[cur.x][cur.y] = 1;
            } else {
                longest_path[cur.x][cur.y] = max_of_neighbor + 1;
            }
            answer = MAX(answer, longest_path[cur.x][cur.y]);
        }
        return answer;
    }
};

int main()
{
    Solution S;
    vector<vector<int>> vect_1
    {
        {9, 9, 4},
        {6, 6, 8},
        {2, 1, 1}
    };
    vector<vector<int>> vect_2
    {
        {3, 4, 5},
        {3, 2, 6},
        {2, 2, 1}
    };
    vector<vector<int>> vect_3
    {
        {1}
    };
    cout << S.longestIncreasingPath(vect_1) << endl;
    cout << S.longestIncreasingPath(vect_2) << endl;
    cout << S.longestIncreasingPath(vect_3) << endl;
    return 0;
}
