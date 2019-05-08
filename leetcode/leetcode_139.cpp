#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

bool wordBreak(string s, vector<string>& wordDict)
{	
	unordered_set<string> Hash;
	for (int i = 0; i < wordDict.size(); i++) {
		Hash.insert(wordDict[i]);
	}
	
	vector<bool> DP;
	DP.reserve(s.length());
	
	for (int i = s.length() - 1; i >= 0; i--) {		
		DP[i] = false;
		
		if (Hash.count(s.substr(i)) != 0) {
			DP[i] = true;
		} else if (i != s.length() - 1) {
			for (int j = i + 1; j <= s.length() - 1; j++) {
				if (Hash.count(s.substr(i, j - i)) != 0 && DP[j] == true) {
					DP[i] = true;
					break;
				}
			}
		}
	}	
	return DP[0];
}

int main()
{
	vector<string> arr1{ "leet", "code" };
	vector<string> arr2{ "apple", "pen" };
	vector<string> arr3{ "cats", "dog", "sand", "and", "cat" };
	cout << wordBreak("leetcode", arr1) << endl;
	cout << wordBreak("applepenapple", arr2) << endl;
	cout << wordBreak("catsandog", arr3) << endl;
	return 0;
}
