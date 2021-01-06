#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        _answer = 0;
        //cout << grid.size() << " " << grid[0].size() << endl;
        for (int x = 0; x < grid.size(); x++) {
            for (int y = 0; y < grid[0].size(); y++) {
                //cout << "main loop :" << x << " " << y << endl;
                if (grid[x][y] == 0) {
                    grid[x][y] = -1;
                } else if (grid[x][y] == 1) {
                    int temp_answer = 0;
                    trace(grid, x, y, temp_answer);
                    if (temp_answer > _answer) {
                        _answer = temp_answer;
                    }
                }
            }
        }
        return _answer;
    }
private:
    int _answer;
    void trace(vector<vector<int>>& grid, int x, int y,int &ans) {
        //cout << "trace: "<< x << " " << y << endl; 
        if (grid[x][y] != 1) {
            grid[x][y] = -1;
            return;
        }
        ans++;
        grid[x][y] = -1;
        int x_min = 0, x_max = grid.size() - 1;
        int y_min = 0, y_max = grid[0].size() - 1;
        if (x + 1 <= x_max) {
            trace(grid, x + 1, y, ans);
        }
        if (x - 1 >= x_min) {
            trace(grid, x - 1, y, ans);
        }
        if (y + 1 <= y_max) {
            trace(grid, x, y + 1, ans);
        }
        if (y - 1 >= y_min) {
            trace(grid, x, y - 1, ans);
        }
    }    
};


int main()
{
    Solution S;
    vector<vector<int>> grid_1
    {
        {0,0,1,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,1,1,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,1,0,0,1,0,1,0,0},
        {0,1,0,0,1,1,0,0,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0}
    };
    vector<vector<int>> grid_2
    {
        {0,0,1,0,0,0,0,1,0,0,0,0,0},
    };
    vector<vector<int>> grid_3
    {
        {0},
    };
    cout << S.maxAreaOfIsland(grid_1) << endl;
    cout << S.maxAreaOfIsland(grid_2) << endl;
    cout << S.maxAreaOfIsland(grid_3) << endl;
    return 0;
}
