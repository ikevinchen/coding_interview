/* g++ leetcode_1.cpp -std=c++0x if lower version of g++ */

#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int lengthOfLongestSubstring(string s) {
	unordered_set<char> Set; /* maintain non-repeated char */
	int answer = 0;
	int left = 0;
	int right = 0;
	
	/* we try to find the longest substring that endding at right position 
	     ex. dabcdbe
		      answer[0] = d
			  answer[1] = da
			  answer[2] = dab
			  answer[3] = dabc
			  answer[4] =  abcd
			  answer[5] =    cdb
			  answer[6] =    cdbe
	 */
	for (right = 0; right < s.length(); right++) {
		if (Set.count(s[right]) == 0) {
			Set.insert(s[right]);			
		} else {
			/* move left postion forward to remove repeatness */
			for (; left < right; left++) {
				Set.erase(s[left]);
				if (s[left] == s[right]) {
					break;
				}				
			}
			left++;
			Set.insert(s[right]);
		}
		/* update answer */
		cout << "[" << right << "] : " << s.substr(left, right - left + 1) << endl;
		if (Set.size() > answer) {
			answer = Set.size();
		}
	}
	
	return answer;
}

int main()
{
	cout << lengthOfLongestSubstring("dabcdbe") << endl;
	cout << lengthOfLongestSubstring("d") << endl;
	cout << lengthOfLongestSubstring("dddd") << endl;
	cout << lengthOfLongestSubstring("") << endl;
	return 0;
}
