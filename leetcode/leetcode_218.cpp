#include <iostream>
#include <queue>
#include <vector>
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
using namespace std;

struct Building{
	int left;
	int right;
	int height;
	Building(int left, int right, int height)
        : left(left), right(right), height(height) 
    { 
    } 
};

struct BuildingComp{
    bool operator()(const Building& a, const Building& b){
		if (a.left < b.left) {
			return false;	
		} else if (a.left == b.left) {
			if (a.height > b.height) {
				return false;
			}
		}			
        return true;
    }
};

class Solution {
public:
    vector<vector<int> > getSkyline(vector<vector<int> >& buildings) {
		vector<vector<int> > answer;
        init_pq(buildings);
		
		/* get the first one */
		Building cur(0, 0, 0);
		Building next(0, 0, 0);
		if (pop_next(&cur) == false) {
			return answer; /* return empty answer */
		}
		add_answer(cur.left, cur.height, answer);
		
		/* repeat the next one */
		while (pop_next(&next) == true) {
			if (next.left > cur.right) {
				/* no overlay */
				add_answer(cur.right, 0, answer);
				add_answer(next.left, next.height, answer);
				cur = next;
			} else if (next.left == cur.right) {
				/* just adjacent */
				if (next.height == cur.height) {
					/* extend the current one */
					cur.right = next.right;					
				} else {
					add_answer(next.left, next.height, answer);
					cur = next;
				}
			} else {
				/* with overlay */
				if (next.height > cur.height)  {
					add_answer(next.left, next.height, answer);
					add_extra(cur, next);
					cur = next;
				} else {
					/* would not introduce new answer,
					 * just handle extra 
					 */
					add_extra(next, cur);
				}
			}
		}		
		
		/* add the ending point  */
		add_answer(cur.right, 0, answer);
		return answer;
    }
private:
	void init_pq(vector<vector<int> >& arr) {
		for (int i = 0; i < arr.size(); i++) {
			_pq.push(Building(arr[i][0], arr[i][1], arr[i][2])); 
		}
	}
	void add_answer(int x, int y, vector<vector<int> >& answer) {
		vector<int> new_ans;
		new_ans.push_back(x);
		new_ans.push_back(y);
		answer.push_back(new_ans);
	}
	void add_extra(Building a, Building b) {
		/* add the range that a exceed b 
		 * the caller must ensure that b.height > a.height
		 */
		if (a.right > b.right) {
			_pq.push(Building(b.right, a.right, a.height));
		}
	}
	bool pop_next(Building *ret) {
		if (_pq.empty()) {
			return false;
		} else {
			/* pop out the next one with leftest and heighest building 
			 * if there are multiple buildings with same left and height, merge it!
			 */
			ret->left   = _pq.top().left;
			ret->right  = _pq.top().right;
			ret->height = _pq.top().height;
			_pq.pop();
			while (!_pq.empty()) {
				if (ret->left == _pq.top().left && ret->height == _pq.top().height) {
					ret->right = MAX(ret->right, _pq.top().right);
					_pq.pop();
				} else {
					break;
				}
			}
			return true;
		}
	}
	priority_queue<Building, vector<Building>, BuildingComp> _pq; 
};

void print_answer(vector<vector<int> >& answer) {
	for (int i = 0; i < answer.size(); i++) {
		cout << "[" <<answer[i][0] << ", " << answer[i][1] << "] ";
	}
	cout << endl;
}

void buildings_add(vector<vector<int> >& buildings, int l, int r, int h) {
	vector<int> building_new;
	building_new.push_back(l);
	building_new.push_back(r);
	building_new.push_back(h);
	buildings.push_back(building_new);
}

int main()
{
	Solution S;
	vector<vector<int> > buildings; 
	vector<vector<int> > answer;

	/* test.1 */
	answer = S.getSkyline(buildings);
	print_answer(answer);
	
	/* test.2 */
	buildings_add(buildings, 2, 3, 5);
	buildings_add(buildings, 2, 1, 5);
	buildings_add(buildings, 1, 2, 5);
	answer = S.getSkyline(buildings);
	print_answer(answer);
	
	/* test.3 */
	buildings_add(buildings, 4, 5, 5);
	answer = S.getSkyline(buildings);
	print_answer(answer);
	
	/* test.4 */
	buildings_add(buildings, 5, 10, 10);
	answer = S.getSkyline(buildings);
	print_answer(answer);
	
	/* test.5 */
	buildings_add(buildings, 6, 9, 12);
	answer = S.getSkyline(buildings);
	print_answer(answer);
	
	/* test.6 */
	buildings_add(buildings, 8, 12, 3);
	answer = S.getSkyline(buildings);
	print_answer(answer);

	return 0;
}

