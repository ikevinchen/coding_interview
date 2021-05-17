/* if the input intervals is sorted ... */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;

        int temp_start = -1;
        int temp_end = -1;
        int new_interval_used = 0;

        for (int i = 0; i <= intervals.size(); i++) {
            int this_start, this_end;
            if (i == intervals.size()) {
                if (new_interval_used == 0) {
                    this_start = newInterval[0];
                    this_end = newInterval[1];
                    new_interval_used = 1;
                } else {
                    break;
                }
            } else {
                if (new_interval_used == 0 && newInterval[0] < intervals[i][0]) {
                    this_start = newInterval[0];
                    this_end = newInterval[1];
                    new_interval_used = 1;
                    i--;
                } else {
                    this_start = intervals[i][0];
                    this_end = intervals[i][1];
                }
            }

            if (temp_start == -1) {
                temp_start = this_start;
                temp_end = this_end;
            } else {
                if (this_start > temp_end) {
                    vector<int> new_interval;
                    new_interval.push_back(temp_start);
                    new_interval.push_back(temp_end);
                    result.push_back(new_interval);
                    temp_start = this_start;
                    temp_end = this_end;
                } else {
                    if (this_end > temp_end) {
                        temp_end = this_end;
                    }
                }
            }
        }

        if (temp_start != -1) {
            vector<int> new_interval;
            new_interval.push_back(temp_start);
            new_interval.push_back(temp_end);
            result.push_back(new_interval);
        }

        return result;

    }
};



int main()
{
    set<struct Interval> s;
    Interval t1 = {1, 4}, t2 = {4, 7},
             t3 = {10, 12}, t4 = {4, 8}, t5 = {8, 9};
    s.insert(t1);
    s.insert(t2);
    s.insert(t3);
    s.insert(t4);
    s.insert(t5);

    set<struct Interval>::iterator iter;
    for (iter = s.begin(); iter != s.end(); iter++)
    {
        cout << "[" << iter->start << ", " << iter->end << "] ";
    }
    cout << endl;

    vector<vector<int>> ans = merge(s);
    for (int i = 0; i < ans.size(); i++) {
        cout << "[" << ans[i][0] << ", " << ans[i][1] << "] ";
    }
    cout << endl;

    return 0;
}

/* if the input intervals is not sorted, sorted first */
#if 0
#include <iostream>
#include <vector>
#include <set>
using namespace std;


struct Interval {
    int start;
    int end;
    bool operator<(const Interval& rhs) const
    {
        if (this->start < rhs.start) {
            return true;
        } else if (this->start == rhs.start) {
            if (this->end > rhs.end) {
                return true;
            }
        }
        return false;
    }
};

vector<vector<int>> merge(set<struct Interval> &s) {
    vector<vector<int>> result;

    int temp_start = -1;
    int temp_end = -1;

    set<struct Interval>::iterator iter;
    for (iter = s.begin(); iter != s.end(); iter++)
    {
        if (temp_start == -1) {
            temp_start = iter->start;
            temp_end = iter->end;
        } else {
            if (iter->start > temp_end) {
                vector<int> new_interval;
                new_interval.push_back(temp_start);
                new_interval.push_back(temp_end);
                result.push_back(new_interval);
                temp_start = iter->start;
                temp_end = iter->end;
            } else {
                if (iter->end > temp_end) {
                    temp_end = iter->end;
                }
            }
        }
    }
    if (temp_start != -1) {
        vector<int> new_interval;
        new_interval.push_back(temp_start);
        new_interval.push_back(temp_end);
        result.push_back(new_interval);
    }
    return result;
}

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        for (int i = 0; i < intervals.size(); i++) {
            Interval t = {intervals[i][0], intervals[i][1]};
            s.insert(t);
        }
        Interval t = {newInterval[0], newInterval[1]};
        s.insert(t);
        return merge(s);
    }
private:
    set<struct Interval> s;
};



int main()
{
    set<struct Interval> s;
    Interval t1 = {1, 4}, t2 = {4, 7},
             t3 = {10, 12}, t4 = {4, 8}, t5 = {8, 9};
    s.insert(t1);
    s.insert(t2);
    s.insert(t3);
    s.insert(t4);
    s.insert(t5);

    set<struct Interval>::iterator iter;
    for (iter = s.begin(); iter != s.end(); iter++)
    {
        cout << "[" << iter->start << ", " << iter->end << "] ";
    }
    cout << endl;

    vector<vector<int>> ans = merge(s);
    for (int i = 0; i < ans.size(); i++) {
        cout << "[" << ans[i][0] << ", " << ans[i][1] << "] ";
    }
    cout << endl;

    return 0;
}
#endif
