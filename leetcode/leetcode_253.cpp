#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

bool CompareInterval(vector<int>& i1, vector<int>& i2) 
{ 
    return (i1[0] < i2[0]); 
} 

int minMeetingRooms(vector<vector<int> >& intervals) {
	int answer = 0;
	priority_queue <int, vector<int>, greater<int> > pq; /* minimun queue */
	sort(intervals.begin(), intervals.end(), CompareInterval);	
	for (int i = 0; i < intervals.size(); i++) {
		if (i == 0) {	
			answer = 1;						
		} else {
			int next_smallest_availtime = pq.top();
			if (intervals[i][0] < next_smallest_availtime) {
				answer++;				
			} else {
				pq.pop();							
			}
		}
		pq.push(intervals[i][1]);
	}
	return answer;
}

int main()
{
	vector<int> i1, i2, i3;
	vector<vector<int> > intervals;
	cout << minMeetingRooms(intervals) << endl;	
	i1.push_back(0);  i1.push_back(30); intervals.push_back(i1);
	cout << minMeetingRooms(intervals) << endl;	
	i2.push_back(30);  i2.push_back(40); intervals.push_back(i2);
	cout << minMeetingRooms(intervals) << endl;	
	i3.push_back(15); i3.push_back(20); intervals.push_back(i3);
	cout << minMeetingRooms(intervals) << endl;	
	return 0;
}
