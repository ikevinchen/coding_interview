#include <iostream>
#include <vector>
#include <algorithm> 
#define MAX(a ,b) ((a) >= (b))?(a):(b)
#define MIN(a ,b) ((a) <= (b))?(a):(b)
using namespace std;

bool myCompare (vector<int> a,vector<int> b) {
	return (a[0] < b[0]);
}

vector<vector<int> > merge(vector<vector<int> >& intervals) {
	vector<vector<int> > answer;
	int recording = 0;
	int record_min = 0;
	int record_max = 0;
	int i;
	
	if (intervals.size() == 0) {
		return answer;
	}
	
	std::sort(intervals.begin(), intervals.end(), myCompare);
	
	record_min = intervals[0][0];
	record_max = intervals[0][1];
	
	for (i = 1; i < intervals.size(); i++) {
		if ((intervals[i][0] <= record_max && intervals[i][0] >= record_min) ||
			(intervals[i][1] <= record_max && intervals[i][1] >= record_min) ||
			(record_min <= intervals[i][1] && record_min >= intervals[i][0]) ||
			(record_max <= intervals[i][1] && record_max >= intervals[i][0])) {
			record_min = MIN(record_min, intervals[i][0]);
			record_max = MAX(record_max, intervals[i][1]);
		} else {
			vector<int> temp;
			temp.push_back(record_min);
			temp.push_back(record_max);
			answer.push_back(temp);
			record_min = intervals[i][0];
			record_max = intervals[i][1];
		}		
	}

	vector<int> temp;
	temp.push_back(record_min);
	temp.push_back(record_max);
	answer.push_back(temp);
	return answer;
}

int main()
{
	vector<vector<int> > answer;
	vector<vector<int> > interval;
	vector<int> temp;
	temp.push_back(2);
	temp.push_back(3);
	interval.push_back(temp);
	temp[0] = 4; temp[1] = 6; interval.push_back(temp);
	temp[0] = 1; temp[1] = 10; interval.push_back(temp);
	answer = merge(interval);
	
	int i;
	for (i = 0; i < answer.size(); i++) {
		cout << answer[i][0] << " " << answer[i][1] << endl;
	}
	cout << endl;
	return 0;
}
