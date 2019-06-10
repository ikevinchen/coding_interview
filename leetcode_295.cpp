#include <vector>
#include <queue> 
#include <iostream>
using namespace std;

class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        _median_exist = false;
    }
    
    void addNum(int num) {
        /*
         *   1 2 3 4 5     6     7 8 9 10 11
         *     max_pq               min_pq
         */
        if (_median_exist == true) {
            if (num <= _median_value) {
                _left_pq.push(num);
                _right_pq.push(_median_value);
            } else {
                _right_pq.push(num);
                _left_pq.push(_median_value);
            }
            _median_exist = false;
        } else {
            if (_left_pq.size() == 0) {
                /* _right_pq.size() should also be zero */
                _median_value = num;
            } else {
                int max_of_left = _left_pq.top();
                int min_of_right = _right_pq.top();
                if (num >= max_of_left && num <= min_of_right) {
                    _median_value = num;
                } else if (num < max_of_left) {
                    _median_value = max_of_left;
                    _left_pq.pop();
                    _left_pq.push(num);
                } else {
                    _median_value = min_of_right;
                    _right_pq.pop();
                    _right_pq.push(num);
                }
            }
            _median_exist = true;
        }
    }
    
    double findMedian() {
        if (_median_exist == true) {
            return _median_value;
        } else {
            return (_left_pq.top() + _right_pq.top())/2.0;
        }
    }
private:
    bool _median_exist;
    int  _median_value;
    priority_queue<int> _left_pq; /* max queue */
    priority_queue<int, vector<int>, greater<int> > _right_pq; /* min queue */
};

int main()
{
    MedianFinder* obj = new MedianFinder();
    obj->addNum(1);
    cout << obj->findMedian() << endl;
    obj->addNum(5);
    cout << obj->findMedian() << endl;
    obj->addNum(1);
    cout << obj->findMedian() << endl;
    obj->addNum(0);
    cout << obj->findMedian() << endl;
    obj->addNum(6);
    cout << obj->findMedian() << endl;
    return 0;
}
