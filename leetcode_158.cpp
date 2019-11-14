#include <iostream>
#include <string>
#include <vector>
#define MIN(a,b) (((a)<(b))?(a):(b))
using namespace std;

int read4_num = 0;
int read4(char *buf) {
	read4_num++;
	if (read4_num == 1) {
		buf[0] = 'a'; buf[1] = 'b'; buf[2] = 'c'; buf[3] = 'd';
		return 4;
	} else if (read4_num == 2) {
		buf[0] = 'e'; buf[1] = 'f'; buf[2] = 'g';
		return 3;
	} else {
		return 0;
	}
}

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
	Solution() {
		cache.clear();
		is_end = false;
	}
	void update_cache(int n) {
		if (is_end == true) {
			return;
		}
		if (n <= cache.length()) {
			return;
		}
		while (cache.length() < n) {
			char temp_buf[4];
			int read_num;
			if ((read_num = read4(temp_buf)) < 4) {
				is_end = true;
			}
			//cout << "read_num : " << read_num << endl;
			for (int i = 0; i < read_num; i++) {
				cache.push_back(temp_buf[i]);
				//cout << "push " << temp_buf[i] << endl;
			}
			if(is_end == true) {
				break;
			}
		}
	}
    int read(char *buf, int n) {
		//cout << "----" <<endl;
        update_cache(n);		
		int copy_len = MIN(n, cache.length());
		cache.copy(buf,copy_len);
		cache = cache.substr(copy_len);
		return copy_len;
    }
private:
	string cache;
	bool is_end;
};

void print_buf(char* buf, int n) {
	cout << n << " : ";
	for (int i = 0; i < n; i++) {
		cout << buf[i] << " ";
	}
	cout<<endl;
}

int main()
{
	Solution S;
	
	char buf[10];
	print_buf(buf, S.read(buf, 8));
	print_buf(buf, S.read(buf, 4));
	print_buf(buf, S.read(buf, 4));
	
	return 0;
}
