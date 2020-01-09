#include <vector>
#include <iostream>
#define MIN(a,b)    ((a)<(b)?(a):(b))
#define MINT(a,b,c) (MIN(MIN(a,b),c) )

using namespace std;

void print(vector<vector<int> > &vect)
{
	for (int m = 0; m < vect.size(); m++) {
		for (int n = 0; n < vect[0].size(); n++) {
			cout << vect[m][n] << " ";
		}
		cout << endl;
	}
}

int maximalSquare(vector<vector<char> >& matrix) {
	int M = matrix.size();
	
	if (M == 0) {
		return 0;
	}
	
	int N = matrix[0].size();
	int answer = 0;
	int m, n;
	
	

	
	/*    n=0  1  2  3  4
	  m=0 : 1  0  1  0  1
		1   1  1  1  1  1
        2   0  0  1  1  1	 
		3   0  0  0  1  1
		
		R[1][2] = the number of consecutive '1' right of [1][2] = 2
		D[1][2] = the number of consecutive '1' down  of [1][2] = 1
		S[1][2] = the length of max squre that left-top corner located at [1][2] 
		        = 1 + min (R[1][2], D[1][2], S[2][3])
		        = 1 + min (2, 1, 2) = 2
	 */
	vector<vector<int> > S( M , vector<int> (N));
	vector<vector<int> > R( M , vector<int> (N)); 
	vector<vector<int> > D( M , vector<int> (N)); 	
	
	for (m = 0; m < M; m++) {
		for (n = N - 1; n >= 0; n--) {
			if (n == N - 1) {
				R[m][n] = 0;
			} else if (matrix[m][n+1] == '0') {
				R[m][n] = 0;
			} else {
				R[m][n] = R[m][n+1] + 1;
			}
		}
	}
	
	
	
	for (n = 0; n < N; n++) {
		for (m = M - 1; m >= 0; m--) {
			if (m == M - 1) {
				D[m][n] = 0;
			} else if (matrix[m+1][n] == '0') {
				D[m][n] = 0;
			} else {
				D[m][n] = D[m+1][n] + 1;
			}
		}
	}
	
	for (m = M - 1; m >= 0; m--) {
		for (n = N - 1; n >= 0; n--) {
			if (m == M - 1) {
				S[m][n] = (matrix[m][n] == '1') ? 1 : 0;
			} else if (n == N - 1) {
				S[m][n] = (matrix[m][n] == '1') ? 1 : 0;
			} else {
				if (matrix[m][n] == '0') {
					S[m][n] = 0;
				} else {
					S[m][n] = 1 + MINT(D[m][n], R[m][n], S[m+1][n+1]);
				}
			}
			if (S[m][n] > answer) {
				answer = S[m][n];
			}
		}
	}
	
	//print(R); cout <<"--------\n";
	//print(D); cout <<"--------\n";
	//print(S); cout <<"--------\n";
	
	return answer*answer;
}

int main()
{
	vector<vector<char> > vect{ {'1', '0', '1', '0', '1'}, 
                                {'1', '1', '1', '1', '1'}, 
                                {'0', '0', '1', '1', '1'},
								{'0', '0', '1', '1', '1'}}; 								
	cout << maximalSquare(vect) << endl;
	
	vector<vector<char> > vect2; 								
	cout << maximalSquare(vect2) << endl;
	
	return 0;
}
