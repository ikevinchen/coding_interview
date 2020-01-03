#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
using namespace std;

/*
 * Actually I missundertnad the problem.
 * The problem promise that timestamp would be inserted by incresing order
 * Here I auusmae that timestamp would be inserted by any order, so I use biniry tree to handle the data
 * However I just demo that it is also okay to use find a value (with <= key) with upper_bound()
 * could also be log(N)
 */


class TimeMap {
public:
    /** Initialize your data structure here. */
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
		unordered_map<string, map<int, string>>::iterator got = _database.find(key);
		if (got == _database.end()) {
			map<int, string> newmap;
			newmap.insert(pair<int, string>(timestamp, value));			
			_database.insert(pair<string, map<int, string>>(key, newmap));
		} else {
			got->second.insert(pair<int, string>(timestamp, value));
		}
    }
    
    string get(string key, int timestamp) {
		unordered_map<string, map<int, string>>::const_iterator got = _database.find(key);
		if (got == _database.end()) {
			return "";
		}
		if (got->second.empty()) {
			return "";
		}
		/* 
		 * return the largest timestamp <= input timestamp
		 *  ==> use the c++ upper_bound(), it would return the first timestamp > input timestamp
		 *      so just need to use its previous iterator
		 */
        map<int, string>::const_iterator iter = got->second.upper_bound(timestamp);
		if (iter == got->second.begin()) {
			return ""; /* all timesamp are larger than input */
		}
		iter--;		
		return iter->second;
    }
private:
	std::unordered_map<string, map<int, string>> _database;
};

int main()
{
	TimeMap S;
	S.set("HP", "a", 10);
	S.set("HP", "b", 15);
	S.set("HP", "c", 20);
	S.set("HPP", "a", 15);
	S.set("HPP", "b", 20);
	S.set("HPP", "c", 25);
	cout << S.get("HPP", 14) << endl;
	cout << S.get("HP", 14) << endl;
	cout << S.get("HPP", 15) << endl;
	cout << S.get("HP", 15) << endl;
	cout << S.get("HPP", 26) << endl;
	cout << S.get("HP", 26) << endl;
	return 0;
}
