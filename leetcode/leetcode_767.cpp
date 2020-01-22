#include <iostream>
#include <string>
#include <queue>
using namespace std;

typedef struct Data_s { 
	char c; 
	int num; 
} Data_t;

struct CompareData { 
    bool operator()(Data_t const& p1, Data_t const& p2) 
    { 
        return p1.num < p2.num;
    } 
}; 

string reorganizeString(string S) {
	priority_queue<Data_t, vector<Data_t>, CompareData> prio_queue;
	string answer="";
	
	int c_num[26] = {0};
	for (int i = 0; i < S.length(); i++) {
		int c = S[i] - 'a';
		if (c >= 0 && c <= 25) {
			c_num[c]++;
		}
	}
	
	for (int i = 0; i < 26; i++) {
		if (c_num[i] != 0) {
			Data_t new_data;
			new_data.c = 'a' + i;
			new_data.num = c_num[i];
			prio_queue.push(new_data); 
		}
	}
	
	/* policy : pickup the most frequent character first 
	            if the next frequent character is the same, save it as temporary and 2nd high
				then push back the temporary
	 */
	Data_t data_temp;
	data_temp.num = 0;
	char last_char = '\0';
	
	while (!prio_queue.empty()) {
		Data_t data_get = prio_queue.top(); 
        prio_queue.pop();
		
		if (data_get.c == last_char) {
			data_temp = data_get;
		} else {
			answer += data_get.c;
			last_char = data_get.c;
			data_get.num--;
			if (data_get.num > 0) {
				prio_queue.push(data_get); 
			}
			if (data_temp.num > 0) {
				/* push back if there is temporary before */
				prio_queue.push(data_temp); 
				data_temp.num = 0;
			}
		}		
	}
	
	if (data_temp.num != 0) {
		/* if there is still exist temporary when queue is empty ==> no answer */
		return "";
	}	
	
	return answer;
}

int main()
{
	cout << reorganizeString("aaabbb") << endl;
	cout << reorganizeString("abbb") << endl;
	cout << reorganizeString("aaaabbbc") << endl;
	cout << reorganizeString("") << endl;
	return 0;
}

