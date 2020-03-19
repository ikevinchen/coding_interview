#include <iostream>
#include <list>

using namespace std;
#define MAX_NUM (300)

struct entry_s {
    int time;
    int data;
};

class HitCounter {
public:
    /** Initialize your data structure here. */
    HitCounter() {
        _sum = 0;
    }
    
    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        
        _sum++;    
        
        if (_list.empty() || _list.back().time != timestamp) {
            /* a new entry */
            struct entry_s new_entry;
            new_entry.time = timestamp;
            new_entry.data= 1;
            _list.push_back(new_entry);
            update(timestamp);        
        } else {
            /* update */
            _list.back().data++;
        }    
        
    }
    
    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        update(timestamp);
        return _sum;
    }
private:
    void update(int timestamp) {
        /* remove the entries that less than 300 */
        int min_limit = timestamp - MAX_NUM + 1;
        while (!_list.empty() && _list.front().time < min_limit) {
            _sum -= _list.front().data;
            _list.pop_front();
        }    
    }
    list<struct entry_s> _list;
    int _sum;
};

int main()
{
    HitCounter obj;
    #if 0
    cout << obj.getHits(0) << endl;
    obj.hit(1);
    obj.hit(1);
    cout << obj.getHits(1) << endl;
    obj.hit(2);
    obj.hit(300);
    obj.hit(300);
    obj.hit(300);
    cout << obj.getHits(300) << endl;
    cout << obj.getHits(301) << endl;
    #endif
    obj.hit(2);
    obj.hit(3);
    obj.hit(4);
    cout << obj.getHits(300) << endl;
    cout << obj.getHits(301) << endl;
    cout << obj.getHits(302) << endl;
    cout << obj.getHits(303) << endl;
    cout << obj.getHits(304) << endl;
    obj.hit(501);
    cout << obj.getHits(600) << endl;
    return 0;
}
