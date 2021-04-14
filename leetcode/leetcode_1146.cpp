#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

class SnapshotArray {
public:
    SnapshotArray(int length) {
		_snap_num = 0;
		_arr_len = length;
        _arr_val = new int[length];
		_arr_record = new map<int, int>[length];
		for (int i = 0; i < _arr_len; i++) {
			_arr_val[i] = 0;
		}
    }

    void set(int index, int val) {
		if (_arr_val[index] != val) {
			_arr_val[index] = val;
			_dirty.insert(index);
		}
    }

    int snap() {
        if (_snap_num == 0) {
			/* first snap */
			for (int i = 0; i < _arr_len; i++) {
				_arr_record[i][0] = _arr_val[i];
			}
		} else {
			/* add new record only if the value is different with the previous snap */
			std::set<int>::iterator iter;
			for (iter = _dirty.begin(); iter != _dirty.end(); ++iter) {
				map<int, int>::iterator last_iter = _arr_record[*iter].end()--;
				if (last_iter->second != _arr_val[*iter]) {
					_arr_record[*iter][_snap_num] = _arr_val[*iter];
				}
			}
		}
		_dirty.clear();
		_snap_num++;
		return _snap_num - 1;
    }

    int get(int index, int snap_id) {
        if (_arr_record[index].size() == 0) {
			return -1;
		}
		map<int, int>::iterator iter;

		iter = _arr_record[index].lower_bound(snap_id);
		if (iter != _arr_record[index].end() && iter->first == snap_id) {
			return iter->second;
		} else {
			iter--;
			return iter->second;
		}
    }
private:
	int _arr_len;
	int *_arr_val;
	map<int, int> *_arr_record;
	std::set<int> _dirty;
	int _snap_num;
};

int main()
{
	SnapshotArray S(3);
	S.set(0, 1);
	S.snap();
	S.snap();

	for (int s = 0; s < 2; s++) {
		cout << "snap " << s << ": ";
		for (int i = 0; i <3; i++) {
			cout << S.get(i, s) << " ";
		}
		cout << endl;
	}

	S.set(1, 5);
	S.snap();
	S.set(0, 2);
	S.snap();
	S.snap();
	S.set(0, 3);

	for (int s = 0; s < 5; s++) {
		cout << "snap " << s << ": ";
		for (int i = 0; i <3; i++) {
			cout << S.get(i, s) << " ";
		}
		cout << endl;
	}
	return 0;
}

#if 0
/* test lower_bound */
int get(map<int, int>& record, int snap_id) {
	if (record.size() == 0) {
		return -1;
	}
	map<int, int>::iterator iter;
	iter=record.lower_bound(snap_id);
	if (iter->first == snap_id) {
		return iter->second;
	} else  {
		iter--;
		return iter->second;
	}
}

int main()
{
	map<int, int> mymap;
	mymap[0] = 0;
	mymap[3] = 1;

	for (int i = 0; i <= 5; i++) {
		cout << i << ": " << get(mymap, i) << endl;
	}

	return 0;
}
#endif
