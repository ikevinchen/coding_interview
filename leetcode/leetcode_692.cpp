#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <unordered_map>
using namespace std;


typedef struct Entry_s {
    string *str;
	int num;
} Entry_t;

struct EntryComp
{
	bool operator()(const Entry_t* lhs, const Entry_t* rhs) const
	{
		if (lhs->num < rhs->num) {
			return false;
		} else if (lhs->num > rhs->num) {
			return true;
		} else {
			return (*(lhs->str) < *(rhs->str));
		}
	}
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
		for (int i = 0; i < words.size(); i++) {
		    //cout << "=== " << i << " ===" << endl;
			unordered_map<string, Entry_t*>::iterator got = _hash.find(words[i]);
			if (got == _hash.end()) {
				/* new entry, check if it can insert into _set */
				Entry_t *new_entry = new Entry_t();
				new_entry->str = &words[i];
				new_entry->num = 1;
				pair<string, Entry_t*> new_hash_item(words[i], new_entry);
				_hash.insert(new_hash_item);
				_set.insert(new_entry);
			} else {
				/* entry existed, update set and hash */
				Entry_t *entry = got->second;
				set<Entry_t*>::iterator it = _set.find(entry);
				if (it != _set.end()) {
					//cout << "  find it in set, delete" << endl;
					_set.erase(it);
				} else {
					//cout << "  cannot find in set" << endl;
				}
				entry->num++;
				_set.insert(entry);
			}
			if (_set.size() > k) {
				/* delete the smallest one */
				//cout << "delete the smallest one in set" << endl;
				set<Entry_t*>::iterator it = _set.end();
				it--;
				_set.erase(it);
			}
			//dump_hash();
		    //dump_set();
		}

        vector<string> ans;
		for (set<Entry_t*>::iterator it = _set.begin(); it != _set.end(); it++)
		{
			ans.push_back(*((*it)->str));
		}
		return ans;
    }
private:
	unordered_map<string, Entry_t*> _hash;
	set<Entry_t*, EntryComp> _set;
	void dump_hash()
	{
		cout << "--- hash ---" << endl;
		for ( auto it = _hash.begin(); it!= _hash.end(); ++it ) {
			Entry_t* entry = it->second;
			cout << it->first << ": " << entry->num << ", " << *(entry->str) << endl;
		}
	}
	void dump_set()
	{
		cout << "--- set ---" << endl;
		set<Entry_t*>::iterator it;
		for (it = _set.begin(); it != _set.end(); it++)
		{
			cout << (*it)->num << " " << *((*it)->str) << endl;
		}
	}
};

int main()
{
    #if 1
	Solution S;
	vector<string> vect{"abc", "bc", "bbc", "abcdef", "abc", "abc"};
	vector<string> ans = S.topKFrequent(vect, 2);
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << endl;
	}
	#endif

	/* test algo for set */
	#if 0
    string str_arr[4] = {"abc", "bc", "bbc", "abcdef"};
	Entry_t e0 = {&str_arr[0], 3};
	Entry_t e1 = {&str_arr[1], 1};
	Entry_t e2 = {&str_arr[2], 1};
	Entry_t e3 = {&str_arr[3], 1};
	set<Entry_t*, EntryComp> s;
	s.insert(&e0); s.insert(&e1); s.insert(&e2); s.insert(&e3);

	set<Entry_t*>::iterator it;
	for (it = s.begin(); it != s.end(); it++)
    {
        cout << (*it)->num << " " << *((*it)->str) << endl;
    }
	#endif
	return 0;
}
