#include <iostream>
#include <vector>
using namespace std;
/* code :  4bit(number of live neighbor)
         + 1bit(cuuent status) 	*/
		 
void neigh_plus(int row, int col,
                int row_max, int col_max, vector<vector<int> >& board)
{
	if(row < 0 || col < 0 || row > row_max || col > col_max) {
		return;
	}
	int status    = (board[row][col] & 0x1);
	int num_neigh = (board[row][col] & 0x1e) >> 1;
	num_neigh++;
	board[row][col] = (num_neigh << 1) | status;
}

void gameOfLife(vector<vector<int> >& board) {
	int row_max = board.size() - 1;
	int col_max = board[0].size() - 1;
	int i, j;
	
	/* calaulate number of live neighbor */
	for(i = 0; i <= row_max; i++) {
		for(j = 0; j <= col_max; j++) {
			if (board[i][j] & 0x1) {
				neigh_plus(i - 1, j - 1, row_max, col_max, board);
				neigh_plus(i - 1, j    , row_max, col_max, board);
				neigh_plus(i - 1, j + 1, row_max, col_max, board);
				neigh_plus(i, j - 1    , row_max, col_max, board);
				neigh_plus(i, j + 1    , row_max, col_max, board);
				neigh_plus(i + 1, j - 1, row_max, col_max, board);
				neigh_plus(i + 1, j    , row_max, col_max, board);
				neigh_plus(i + 1, j + 1, row_max, col_max, board);
			}
		}
	}
	
	/* update answer */
	for(i = 0; i <= row_max; i++) {
		for(j = 0; j <= col_max; j++) {
			int state = board[i][j] & 0x1;
			int num_neigh = (board[i][j] & 0x1e) >> 1;
			if (state) {
				if (num_neigh < 2 || num_neigh > 3) {
					board[i][j] = 0;
				} else {
					board[i][j] = 1;
				}
			} else {
				if (num_neigh == 3) {
					board[i][j] = 1;
				} else {
					board[i][j] = 0;
				}
			}			
		}
	}
}

void Print(vector<vector<int> >& board) {
	for(int i = 0; i < board.size(); i++) {
		for(int j = 0; j < board[i].size(); j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	/*
		Input: 
		[
		  [0,1,0],
		  [0,0,1],
		  [1,1,1],
		  [0,0,0]
		]
		Output: 
		[
		  [0,0,0],
		  [1,0,1],
		  [0,1,1],
		  [0,1,0]
		]	
	 */
	vector<vector<int> > board;
	vector<int> v1, v2, v3, v4;
	v1.push_back(0); v1.push_back(1); v1.push_back(0); board.push_back(v1);
	v2.push_back(0); v2.push_back(0); v2.push_back(1); board.push_back(v2);
	v3.push_back(1); v3.push_back(1); v3.push_back(1); board.push_back(v3);
	v4.push_back(0); v4.push_back(0); v4.push_back(0); board.push_back(v4);
	Print(board);
	gameOfLife(board);
	Print(board);
	return 0;
}
