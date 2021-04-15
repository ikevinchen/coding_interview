/* however, it seems that it just need to maintain one map,
 * try to enhance it
 */
#include <iostream>
#include <map>
using namespace std;

struct Event {
    int start;
    int end;
};

class MyCalendar {
public:
    MyCalendar() {
    }
    ~MyCalendar() {
        map<int, Event*>::iterator iter;
        for (iter = _map_index_by_start.begin();
             iter != _map_index_by_start.end(); iter++) {
            delete iter->second;
        }
        _map_index_by_start.clear();
        _map_index_by_end.clear();
    }
    bool book(int start, int end) {
        if (_map_index_by_start.size() != 0) {
            /* find the nearest one whose end time > input start time */
            map<int, Event*>::iterator itlow;
            itlow = _map_index_by_end.lower_bound(start + 1);
            if (itlow != _map_index_by_end.end()) {
                if (itlow->second->start < end) {
                    return false;
                }
            }
            /* find the nearest one whose start time < input end time */
            map<int, Event*>::iterator itup;
            itup = _map_index_by_start.upper_bound(end - 1);
            if (itup != _map_index_by_start.begin()) {
                itup--;
                if (itup->second->end > start) {
                    return false;
                }
            }
        }
        Event *event = new Event{start, end};
        _map_index_by_start[start] = event;
        _map_index_by_end[end] = event;
        return true;
    }
private:
    map<int, Event*> _map_index_by_start;
    map<int, Event*> _map_index_by_end;
};

int main()
{
    MyCalendar C;
    cout << MyCalendar.book(10, 20) << endl;
    cout << MyCalendar.book(15, 25) << endl;
    cout << MyCalendar.book(20, 30) << endl;
    return 0;
}


#if 0
/* test */
int main()
{
    map<int, Event*> map_index_by_start;
    map<int, Event*> map_index_by_end;
    Event e1 = {10, 20};
    Event e2 = {30, 40};
    Event e3 = {50, 60};
    map_index_by_start[e1.start] = &e1;
    map_index_by_start[e2.start] = &e2;
    map_index_by_start[e3.start] = &e3;
    map_index_by_end[e1.end] = &e1;
    map_index_by_end[e2.end] = &e2;
    map_index_by_end[e3.end] = &e3;

    /* find the nearest one whose end time > input start time */
    for (int i = 0; i < 5; i++) {
        int testcase[5] = {10, 20, 50, 60, 70};
        map<int, Event*>::iterator itlow;
        itlow = map_index_by_end.lower_bound(testcase[i] + 1);
        cout << testcase[i] << " : ";
        if (itlow == map_index_by_end.end()) {
            cout << "null" << endl;
        } else {
            cout << "["<< itlow->second->start << ", " << itlow->second->end << "]" << endl;
        }
    }

    /* find the nearest one whose start time < input end time */
    for (int i = 0; i < 5; i++) {
        int testcase[5] = {0, 10, 15, 50, 60};
        map<int, Event*>::iterator itup;
        itup = map_index_by_start.upper_bound(testcase[i] - 1);
        cout << testcase[i] << " : ";
        if (itup == map_index_by_start.begin()) {
            cout << "null" << endl;
        } else {
            itup--;
            cout << "["<< itup->second->start << ", " << itup->second->end << "]" << endl;
        }
    }

    return 0;
}
#endif
