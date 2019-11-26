#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool isIsomorphic(string s, string t) {
	unordered_map<char, char> map; /* mapping table , a-->b */
	unordered_set<char> mapped; /* store "b" that has already been mapped */
	int i;
	for (i = 0; i < s.length(); i++) {
		unordered_map<char, char>::const_iterator got = map.find(s[i]);
		if ( got == map.end()) {
			/* No two characters may map to the same character, check first */
			if (mapped.count(t[i]) > 0) {
				return false;	
			}
			/* okay to insert */
			pair<char, char> new_mapping(s[i], t[i]);
			map.insert(new_mapping);
			mapped.insert(t[i]);			
		} else {
			if (t[i] != got->second) {
				return false;
			}
		}
	}
	return true;
}

int main()
{
	cout << isIsomorphic("abc", "abc") << endl;
	cout << isIsomorphic("abb", "cbb") << endl;
	cout << isIsomorphic("abb", "bbb") << endl;
	cout << isIsomorphic("abb", "cba") << endl;
	return 0;
}
