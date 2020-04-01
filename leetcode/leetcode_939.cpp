#include <vector>
#include <iostream>
#include <unordered_map>
#define MAX (40001)
using namespace std;

struct Point {
	int x;
	int y;
};

struct YHeight {
	int y1;
	int y2;
	
 
    bool operator==(const YHeight& yh) const
    { 
        return y1 == yh.y1 && y2 == yh.y2; 
    } 
};

class MyHashFunction { 
public: 
    size_t operator()(const YHeight& yh) const
    { 
        return yh.y1 + yh.y2; 
    } 
}; 

class Solution {
public:
    int minAreaRect(vector<vector<int> >& points) {
		/* save each point according to its x */
        for (int i = 0; i < points.size(); i++) {
			Point p;
			p.x = points[i][0];
			p.y = points[i][1];
			point_on_x[p.x].push_back(p);
		}
		/* for each point on a specic x, calcualte all possible yheight */
		for (int x = 0; x < MAX; x++) {
			if (point_on_x[x].size() <= 1) {
				continue;
			}
			for (int i = 1; i < point_on_x[x].size(); i++) {
				for (int j = 0; j < i; j++) {
					YHeight yh;
					yh.y1 = point_on_x[x][j].y;
					yh.y2 = point_on_x[x][i].y;
					
					unordered_map<YHeight,vector<int> >::iterator got = yheight_x.find(yh);
					if ( got == yheight_x.end() ) {
						vector<int> new_v;
						new_v.push_back(x);
						pair<YHeight,vector<int>> new_yh(yh, new_v);
						yheight_x.insert(new_yh); 
					} else {
						(got->second).push_back(x);
					}
				}
			}
		}

		int answer = 0;
		/* traverse each yheight, find the minimal x interval */
		for ( auto iter = yheight_x.begin(); iter != yheight_x.end(); ++iter ) {
			if (iter->second.size() < 2) {
				continue;
			}			
			int y_interval = iter->first.y2 - iter->first.y1;
			int x_interval_min = iter->second[1] - iter->second[0];
			for (int i = 2; i < iter->second.size(); i++) {
				int x_interval = iter->second[i] - iter->second[i - 1];
				if (x_interval < x_interval_min) {
					x_interval_min = x_interval;
				}
			}			
			int area = x_interval_min * y_interval;
			if (answer == 0 || area < answer) {
				answer = area;
			}
		}
		
		return answer; 
    }
private:
	vector<Point> point_on_x[MAX];
	unordered_map<YHeight, vector<int>, MyHashFunction> yheight_x;
};

int main()
{
	vector<vector<int> > points_1{ { 1, 1 }, { 3, 1 }, { 4, 1 },
                                   { 1, 3 }, { 3, 3 }, { 4, 3 }, { 4, 5 }}; 
	vector<vector<int> > points_2{ { 1, 1 }, { 3, 1 }, { 4, 1 }}; 							 
	Solution S;
	cout << S.minAreaRect(points_1) << endl;
	return 0;
}
