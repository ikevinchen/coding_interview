#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Logger {
public:
    /** Initialize your data structure here. */
    Logger() {
        
    }
    
    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int timestamp, string message) {
        unordered_map<string, int>::iterator got = str_hash.find(message);
		if (got == str_hash.end()) {
			str_hash.insert({message, timestamp + 10});
			return true;
		} else {
			if (timestamp >= got->second) {
				got->second = timestamp + 10;
				return true;
			} else {
				return false;
			}
		}
    }
private:
	unordered_map<string, int> str_hash;
};

int main()
{
	Logger L;
	cout << L.shouldPrintMessage(1, "A") << endl;
	cout << L.shouldPrintMessage(1, "B") << endl;
	cout << L.shouldPrintMessage(10, "A") << endl;
	cout << L.shouldPrintMessage(11, "B") << endl;
	cout << L.shouldPrintMessage(11, "A") << endl;
	return 0;
}
