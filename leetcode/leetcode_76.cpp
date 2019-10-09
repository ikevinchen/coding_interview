#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <stdio.h>
using namespace std;

typedef struct char_data {
	int required_num;
	int existed_num;
} char_data_t;


class Solution {

public:
	Solution()
	{
		_char_total_num = 0;
		_char_meet_num = 0;
	}

	string minWindow(string s, string t) {
		
		for(int i = 0; i < t.size(); i++) {
			char_insert(t[i]);
		}
		
		int ans_width = -1;
		int ans_start = -1;
		int ans_end = -1;
		
		int right = 0;
		int left = 0;
		
		for(right = 0; right < s.size(); right++) {
			
			char_add(s[right]);
			
			if (char_allmeet() == 1) {
				/* we find that there is a available "right",
				 * try to min "left" as possible
				 */
				while(left <= right) {
					char_del(s[left]);
					left++;
					if (char_allmeet() == 0) {
						int cur_start = left - 1;
						int cur_end = right;
						int cur_width = cur_end - cur_start + 1;
						if (ans_width == -1 || cur_width < ans_width) {
							ans_width = cur_width;
							ans_start = cur_start;
							ans_end = cur_end;
						}
						break;
					}
				}
			}
		}
		
		//cout << ans_start << " " << ans_end << endl;
		if (ans_width != -1) {
			return s.substr (ans_start,ans_width);
		} else {
			return "";
		}
	}
	
private:

	int _char_total_num;
	int _char_meet_num;
	unordered_map<char,char_data_t> _char_hash;

	void char_insert(char c) {
		unordered_map<char,char_data_t>::iterator iter = _char_hash.find(c);
		if ( iter == _char_hash.end() ) 
		{
			char_data_t new_data;
			new_data.required_num = 1;
			new_data.existed_num = 0;
			pair<char,char_data_t> new_pair (c, new_data);
			_char_hash.insert(new_pair);		
			_char_total_num++;
		} 
		else
		{
			(iter->second).required_num++;
		}
	}

	void char_add(char c)
	{
		unordered_map<char,char_data_t>::iterator iter = _char_hash.find(c);
		if ( iter != _char_hash.end() )
		{
			char_data_t* data_ptr = &(iter->second);					
			data_ptr->existed_num++;	
			if ((data_ptr->existed_num ) == data_ptr->required_num) {
				_char_meet_num++;
			}
		}
	}
	
	void char_del(char c)
	{
		unordered_map<char,char_data_t>::iterator iter = _char_hash.find(c);
		if ( iter != _char_hash.end() )
		{
			char_data_t* data_ptr = &(iter->second);			
			if ( data_ptr->existed_num == data_ptr->required_num) {
				_char_meet_num--;
			}			
			data_ptr->existed_num--;			
		}
	}

	int char_allmeet()
	{
		if (_char_meet_num == _char_total_num) {
			return 1;
		} else {
			return 0;
		}
	}

};

int main() 
{
	Solution S1, S2, S3, S4;
	cout << S1.minWindow("ABBBC", "b") << endl;
	cout << S2.minWindow("ABBBC", "BB") << endl;
	cout << S3.minWindow("BCCCCAAB", "AB") << endl;
	cout << S4.minWindow("ADOBECODEBANC", "ABC") << endl;
	return 0;
}
