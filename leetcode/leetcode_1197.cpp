#include <iostream>
#include <queue>
#define ABS(x) (((x) > 0)?(x):(-(x)))
#define MAX (310)
using namespace std;

int map[MAX][MAX];

int minKnightMoves(int x, int y) {
	int width = ABS(x)+8;
	int height = ABS(y)+8;
	int target_x = 4;
	int target_y = 4;
	int origin_x = 4 + ABS(x);
	int origin_y = 4 + ABS(y);
	int answer = -1;	

	for(int i = 0; i < MAX; i++) {
		for(int j = 0; j < MAX; j++) {
			map[i][j] = -1;
		}
	}
	
	queue<int> queue_x;
	queue<int> queue_y;	
	map[origin_x][origin_y] = 0;
	queue_x.push(origin_x);
	queue_y.push(origin_y);
	
	const int offset_x[8] = {1,  1, -1, -1, 2,  2, -2, -2};
	const int offset_y[8] = {2, -2,  2, -2, 1, -1,  1, -1};
	
	while (!queue_x.empty()) {
		int take_x = queue_x.front();
		int take_y = queue_y.front();
		queue_x.pop();
		queue_y.pop();
		
		if (take_x == target_x && take_y == target_y) {
			answer = map[take_x][take_y];
			break;
		}
		
		for (int i = 0; i < 8; i++) {
			int next_x = take_x + offset_x[i];
			int next_y = take_y + offset_y[i];
			if (next_x >= 0 && next_x < width &&
			    next_y >= 0 && next_y < height && map[next_x][next_y] == -1)
			{
				map[next_x][next_y] = map[take_x][take_y] + 1;				
				queue_x.push(next_x);
				queue_y.push(next_y);
			}
		}
	}	
	return answer;	
}

int main()
{
	cout << minKnightMoves(0, 0) << endl;
	cout << minKnightMoves(2, 1) << endl;
	cout << minKnightMoves(2, -1) << endl;
	cout << minKnightMoves(-2, -1) << endl;
	cout << minKnightMoves(-2, 1) << endl;
	cout << minKnightMoves(2, 2) << endl;
	cout << minKnightMoves(5, 5) << endl;
	cout << minKnightMoves(299, 1) << endl;
	cout << minKnightMoves(150, 150) << endl;
	return 0;
}
