#include <iostream>
#include <queue>
#include <vector>
#include <set>
#define KEY_MAX (10001)
using namespace std;

struct Entry
{
    int key;
    int value;
    int touch_num;
    int touch_time;

    // compare for order.     
    const bool operator <(const Entry& pt) const
    {
        if (touch_num < pt.touch_num) {
            return true;
        } else if (touch_num == pt.touch_num && touch_time < pt.touch_time) {
            return true;
        }
        return false;
    }
};


class LFUCache {
public:
    LFUCache(int capacity) {
        _capacity = capacity;
        _time = 0;
        _vector = vector<Entry*>(KEY_MAX, NULL);    
    }
    
    int get(int key) {
        if (_capacity == 0) {
            return -1;
        }
        _time++;
        Entry* entry = _vector[key];
        if (entry != NULL) {
            _tree.erase(*entry);
            entry->touch_time = _time;
            entry->touch_num++;
            _tree.insert(*entry);
        }
        if (entry != NULL) {
            return entry->value;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        if (_capacity == 0) {
            return;
        }
        _time++;
        Entry* entry = _vector[key];
        if (_vector[key] != NULL) {
            _tree.erase(*entry);
            entry->touch_num++;
            entry->touch_time = _time;
            entry->value = value;
            _tree.insert(*entry);
        } else {
            Entry *entry_new= new Entry();
            entry_new->key = key;
            entry_new->value = value;
            entry_new->touch_num = 1;
            entry_new->touch_time = _time;
            if (_tree.size() == _capacity) {
                int delete_key = _tree.begin()->key;
                _tree.erase(_tree.begin());
                delete _vector[delete_key];
                _vector[delete_key] = NULL;
            }
            _tree.insert(*entry_new);
            _vector[key] = entry_new;
        }   
        
    }    
    
    void dump() {
        cout << "-- current time " << _time << " ---\n";
        for (set<Entry>::iterator it=_tree.begin(); it!=_tree.end(); ++it) {
            Entry entry = *it;
            cout << "  [" << entry.key << "] " << entry.value << " touch num:"
                     << entry.touch_num << " last time:" << entry.touch_time << endl;
        }
    }
private:
    int _capacity;
    int _time;
    set<Entry> _tree;
    vector<Entry*> _vector;
};

int main()
{
    LFUCache lfu = LFUCache(2);
    lfu.put(10, 100); lfu.dump();
    lfu.put(20, 200); lfu.dump();
    cout << lfu.get(10) << endl; lfu.dump();
    cout << lfu.get(30) << endl; lfu.dump();
    lfu.put(30, 300); lfu.dump();
    cout << lfu.get(30) << endl; lfu.dump();
    lfu.put(40, 400); lfu.dump();
    lfu.put(40, 500); lfu.dump();
    return 0;
}
