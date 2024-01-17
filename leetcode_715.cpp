#include <iostream>
#include <map>
using namespace std;

class RangeModule {
public:
    RangeModule() {
        
    }
    
    void addRange(int left, int right) {
        cout << "Add range [" << left << ", " << right << "]\n"; 
        if (mymap.empty()) {
            mymap[left] = right;
        } else {
            map<int, int>::iterator overlay_L, overlay_R;
            find_overlay(left, right, overlay_L, overlay_R);
          
            /* check */
            if (overlay_L != mymap.end() && overlay_R != mymap.end()) {
                int new_left = (left < overlay_L->first)? left: overlay_L->first;
                int new_right = (right > overlay_R->second)? right: overlay_R->second;
                /* erase all overlay and insert the new one */
                mymap.erase(overlay_L, ++overlay_R); /* erase [overlay_L, ++overlay_R)
                                                       * = erase [overlay_L, overlay_R]
                                                       */
                mymap[new_left] = new_right;
            } else if (overlay_L != mymap.end() || overlay_R !=  mymap.end()) {
                cout << "something wrong" << endl;
            } else {
                mymap[left] = right;
            }
        }
    }
    
    bool queryRange(int left, int right) {
        cout << "QueryRange range [" << left << ", " << right << "]\n";
        if (mymap.empty()) {
            return false;
        } else {
            map<int, int>::iterator overlay_L, overlay_R;
            find_overlay(left, right, overlay_L, overlay_R);
          
            /* check */
            if (overlay_L != mymap.end() && overlay_R != mymap.end()) {
                if (overlay_L != overlay_R) {
                    return false;
                } else if (overlay_L->first > left || overlay_L->second < right) {
                    return false;
                } else {
                    return true;
                }                
            } else if (overlay_L != mymap.end() || overlay_R !=  mymap.end()) {
                cout << "something wrong" << endl;
                return false;
            } else {
                return false;
            }
        }
    }
    
    void removeRange(int left, int right) {
        cout << "Remove range [" << left << ", " << right << "]\n"; 
        if (mymap.empty()) {
            /* do nothing */
        } else {
            map<int, int>::iterator overlay_L, overlay_R;
            find_overlay(left, right, overlay_L, overlay_R);
          
            /* check */
            if (overlay_L != mymap.end() && overlay_R != mymap.end()) {
                bool need_new_1 = false; int new_1_left, new_1_right;
                bool need_new_2 = false; int new_2_left, new_2_right;
                
                if (overlay_L->first < left) {
                    need_new_1 = true;
                    new_1_left = overlay_L->first;
                    new_1_right = left;
                }
                if (overlay_R->second > right) {
                    need_new_2 = true;
                    new_2_left = right;
                    new_2_right = overlay_R->second;
                }               
        
                /* erase all overlay and insert the new  */
                mymap.erase(overlay_L, ++overlay_R); /* erase [overlay_L, ++overlay_R)
                                                       * = erase [overlay_L, overlay_R]
                                                       */
                if (need_new_1) {
                    mymap[new_1_left] = new_1_right;
                }
                if (need_new_2) {
                    mymap[new_2_left] = new_2_right;
                }
            } else if (overlay_L != mymap.end() || overlay_R !=  mymap.end()) {
                cout << "something wrong" << endl;
            } else {
                /* do nothing */
            }
        }
    }
    
    void dump() {
        for (map<int,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it) {
            cout << "[" << it->first << " ," << it->second << "]\n";
        }
        cout << "----\n";
    }
    
    /* overlay include "beside(next to)" 
     * ex. [1, 2] and [2, 3]
     */
    void find_overlay(int left, int right,
                      map<int, int>::iterator &overlay_L,
                      map<int, int>::iterator &overlay_R) {
        /*         left                           right
         *          |------------------------------|
         *
         *        |-----|  |-----|  |-----|  |-------|  |-----|
         *           L                           R
         *
         * |-----|         |-----|  |-----|  |-------|  |-----|
         *                     L                 R
         *
         * |-----|                                               (L, R = NULL)
         *
         *                                              |-----|  (L, R = NULL)
         *
         * |-----|                                      |-----|  (L, R = NULL)
         *
         * |-----|                   |-----|            |-----|
         *                             L,R
         */
        map<int, int>::iterator find, prev;
        
        /* find the overlay L */
        find = mymap.upper_bound(left); /* upper_bound: find the first iter that > left
                                          *              also need to check the previous one as well
                                          * check priority: 1. prev  2. find
                                          */
        if (find != mymap.begin()) {
            prev = find;
            prev--;
        } else {
            prev = mymap.end(); /* NULL*/ 
        }
        
        overlay_L = mymap.end(); /* NULL*/
        if (overlay_L == mymap.end() && prev != mymap.end()) {
            if (prev->second >= left) {
                overlay_L = prev;
            }
        }
        if (overlay_L == mymap.end() && find != mymap.end()) {
            if (find->first <= right) {
                overlay_L = find;
            }
        }
        if (overlay_L != mymap.end()) {
            cout << "  overlay_L: [" << overlay_L->first << ", " << overlay_L->second << "]\n";
        } else {
            cout << "  overlay_L: NULL\n";
        }
        
        /* find the overlay R */
        find = mymap.upper_bound(right); /* upper_bound: find the first iter that > right
                                          *  just need to check the previous one
                                          */
        if (find != mymap.begin()) {
            prev = find;
            prev--;
        } else {
            prev = mymap.end(); /* NULL*/ 
        }
        
        overlay_R = mymap.end(); /* NULL*/
        if (prev != mymap.end()) {
            if (prev->first == right || prev->second >= left) {
                overlay_R = prev;
            }
        }
        if (overlay_R != mymap.end()) {
            cout << "  overlay_R: [" << overlay_R->first << ", " << overlay_R->second << "]\n";
        } else {
            cout << "  overlay_R: NULL\n";
        }
    }
private:
    map<int, int> mymap;
};

int main() {
    RangeModule R;
    #if 1
    R.addRange(3, 4);
    R.addRange(10, 11);
    R.addRange(6, 7);
    R.dump();
    R.addRange(4, 7);
    R.dump();
    R.addRange(0, 1);
    R.dump();
    R.addRange(2, 10);
    R.dump();
    R.addRange(13, 15);
    R.dump();
    R.addRange(2, 12);
    R.dump();
    R.removeRange(2, 12);
    R.dump();
    R.addRange(2, 12);
    R.removeRange(5, 6);
    R.dump();
    R.removeRange(3, 10);
    R.dump();
    R.removeRange(10, 12);
    R.dump();
    R.removeRange(4, 4);
    R.dump();
    R.removeRange(1, 18);
    R.dump();
    R.addRange(1, 2);
    R.dump();
    R.addRange(3, 5);
    R.addRange(7, 8);
    R.dump();
    cout << R.queryRange(3, 5) << endl;
    cout << R.queryRange(3, 6) << endl;
    cout << R.queryRange(1, 1) << endl;
    cout << R.queryRange(7, 7) << endl;
    #endif
    #if 0
    R.addRange(6, 8);
    R.dump();
    R.removeRange(7, 8);
    R.dump();
    R.removeRange(8, 9);
    R.dump();
    R.addRange(8, 9);
    R.dump();
    R.removeRange(1, 3);
    R.dump();
    R.addRange(1, 8);
    R.dump();
    cout << R.queryRange(2, 4) << endl;
    cout << R.queryRange(2, 9) << endl;
    cout << R.queryRange(4, 6) << endl;
    #endif
    return 0;
}

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
