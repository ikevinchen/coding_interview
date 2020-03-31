#include <iostream>
#include <vector>
using namespace std;

#define DIST(x1, x2, y1, y2) (((x1)-(x2))*((x1)-(x2)) + ((y1)-(y2))*((y1)-(y2)))


class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
		if (valid(p1, p2, p3, p4) == false) {
			return false;
		}
		if (valid(p2, p1, p3, p4) == false) {
			return false;
		}
		if (valid(p3, p1, p2, p4) == false) {
			return false;
		}
		if (valid(p4, p1, p2, p3) == false) {
			return false;
		}
		return true;
    }
private:
	bool valid(vector<int>& root, vector<int>& o0, vector<int>& o1, vector<int>& o2) {
		int dist[3];
		dist[0] = DIST(root[0], o0[0], root[1], o0[1]);
		dist[1] = DIST(root[0], o1[0], root[1], o1[1]);
		dist[2] = DIST(root[0], o2[0], root[1], o2[1]);

		int max = 0;
		int max_index = -1;
		
		for (int i = 0; i < 3; i++) {
			if (dist[i] == 0) {
				return false;
			}
			if (dist[i] > max) {
				max = dist[i];
				max_index = i;
			}
		}
		
		int adj_1 = dist[(max_index + 1)%3];
		int adj_2 = dist[(max_index + 2)%3];
		
		if (adj_1 != adj_2) {
			return false;
		} else if (adj_1 + adj_2 != max) {
			return false;
		} else {
			return true;
		}
    }
};

int main()
{
	vector<int> p1{ -10000, -10000};
	vector<int> p2{ 10000, -10000};
	vector<int> p3{ 10000, 10000};	
	vector<int> p4{ -10000, 10000};
	Solution S;
	cout << S.validSquare(p1, p2, p3, p4) << endl;
	return 0;
}
