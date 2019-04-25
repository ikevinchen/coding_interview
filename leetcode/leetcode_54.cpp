#include <iostream>
#include <vector>

using namespace std;

int go_right(int& row_min, int& row_max, int& col_min, int& col_max,
             vector<vector<int> >& array, vector<int> &answer,
			 int& row, int& col)
{
	cout << "go right " << row_min << " " << row_max << " " << col_min << " "<< col_max << " "<< row << " "<< col << endl;
	if (col > col_max) {
		return -1;
	}
	for (int i = col; i <= col_max; i++) {
		answer.push_back(array[row][i]);
	}
	col = col_max;
	row = row + 1;
	row_min++;
	return 0;
}

int go_down(int& row_min, int& row_max, int& col_min, int& col_max,
            vector<vector<int> >& array, vector<int> &answer,
			int& row, int& col)
{
	cout << "go down " << row_min << " " << row_max << " " << col_min << " "<< col_max << " "<< row << " "<< col << endl;
	if (row > row_max) {
		return -1;
	}
	for (int i = row; i <= row_max; i++) {
		answer.push_back(array[i][col]);
	}
	row = row_max;
	col = col - 1;
	col_max--;
	return 0;
}

int go_left(int& row_min, int& row_max, int& col_min, int& col_max,
            vector<vector<int> >& array, vector<int> &answer,
			int& row, int& col)
{
	cout << "go left " << row_min << " " << row_max << " " << col_min << " "<< col_max << " "<< row << " "<< col << endl;
	if (col < col_min) {
		return -1;
	}
	for (int i = col; i >= col_min; i--) {
		answer.push_back(array[row][i]);
	}
	col = col_min;
	row = row - 1;
	row_max--;
	return 0;
}

int go_up(int& row_min, int& row_max, int& col_min, int& col_max,
          vector<vector<int> >& array, vector<int> &answer,
          int& row, int& col)
{
	cout << "go up " << row_min << " " << row_max << " " << col_min << " "<< col_max << " "<< row << " " << col << endl;
	if (row < row_min) {
		return -1;
	}
	for (int i = row; i >= row_min; i--) {
		answer.push_back(array[i][col]);
	}
	row = row_min;
	col = col + 1;
	col_min++;
	return 0;
}

vector<int> spiralOrder(vector<vector<int> >& matrix) {
	vector<int> answer;
	int row_num = matrix.size();
	
	if (row_num == 0) {
		return answer;
	}
	
	int col_num = matrix[0].size();
	
	int row = 0, col = 0;
	int row_min = 0, row_max = row_num - 1;
	int col_min = 0, col_max = col_num - 1;
	int first_round = 1;

	
	while (1) {
		int rv;
		
		rv = go_right(row_min, row_max, col_min, col_max,
                      matrix, answer, row, col);
		if (rv == -1 && first_round == 0) break;
		first_round = 0;
		
		rv = go_down(row_min, row_max, col_min, col_max,
                     matrix, answer, row, col);
		if (rv == -1) break;
		
		rv = go_left(row_min, row_max, col_min, col_max,
                     matrix, answer, row, col);
		if (rv == -1) break;
		
		rv = go_up(row_min, row_max, col_min, col_max,
                   matrix, answer, row, col);
		if (rv == -1) break;
	}
	
	return answer;
}

int main()
{
	vector<vector<int> > array;
	vector<int> temp_1;
	temp_1.push_back(1);
	temp_1.push_back(2);
	vector<int> temp_2;
	temp_2.push_back(4);
	temp_2.push_back(5);
	vector<int> temp_3;
	temp_3.push_back(7);
	temp_3.push_back(8);
	array.push_back(temp_1);
	array.push_back(temp_2);
	array.push_back(temp_3);
	
	vector<int> answer;
	answer = spiralOrder(array);
	
	for (int i = 0; i < answer.size(); i++) {
		cout << answer[i] << " ";
	}
	cout << endl;
	
	return 0;
}
