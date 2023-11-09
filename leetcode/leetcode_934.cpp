#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {

    	int N = grid.size();

        /* distinguish to two islands first to 100, 200 */
        list<int> bfs_x;
    	list<int> bfs_y;
    	for (int i = 0; i < N; i++) {
    		for (int j = 0; j < N; j++) {
    			if (grid[i][j] == 1) {
    				bfs_x.push_back(i);
    				bfs_y.push_back(j);
    				break;
    			}
    		}
    		if (bfs_x.size() != 0) {
    			break;
    		}
    	}
    	while (bfs_x.size() != 0) {
    		int x = bfs_x.front();
    		int y = bfs_y.front();
    		bfs_x.pop_front();
    		bfs_y.pop_front();
    		grid[x][y] = 100;
    		if (x - 1 >= 0 && grid[x - 1][y] == 1) {
    			bfs_x.push_back(x - 1);
    			bfs_y.push_back(y);
    		}
    		if (x + 1 < N  && grid[x + 1][y] == 1) {
    			bfs_x.push_back(x + 1);
    			bfs_y.push_back(y);
    		}
    		if (y - 1 >= 0 && grid[x][y - 1] == 1) {
    			bfs_x.push_back(x);
    			bfs_y.push_back(y - 1);
    		}
    		if (y + 1 < N  && grid[x][y + 1] == 1) {
    			bfs_x.push_back(x);
    			bfs_y.push_back(y + 1);
    		}
    	}
    	for (int i = 0; i < N; i++) {
    		for (int j = 0; j < N; j++) {
    			if (grid[i][j] == 1) {
    				grid[i][j] = 200;
    			}
    		}
    	}

    	/* start to traverse each node (100 or 200) */
    }
};


int main()
{
	return 0;
}
