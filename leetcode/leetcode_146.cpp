#include <iostream>
#include <unordered_map>
using namespace std;

typedef struct list_node
{
    int key;
    int value;
    struct list_node* prev;
    struct list_node* next;
} list_node_t;

void insert_to_end(list_node_t** list_start,
                    list_node_t** list_end, list_node_t* new_node)
{
    new_node->next = NULL;
    if (*list_start == NULL && *list_end == NULL) {
        new_node->prev = NULL;
        *list_start = *list_end = new_node;
    } else {
        if (*list_start == NULL || *list_end == NULL) {
            //cout << "something wrong\n";
            return;
        }
        new_node->prev = *list_end;
        (*list_end)->next = new_node;
        *list_end = new_node;
    }
}

void delete_start(list_node_t** list_start,
                  list_node_t** list_end) 
{
    if (*list_start == NULL && *list_end == NULL) {
        return;
    }
    if (*list_start == NULL || *list_end == NULL) {
        //cout << "something wrong\n";
        return;
    }
    if (*list_start == *list_end) {
        delete *list_start;
        *list_start = *list_end = NULL;
    } else {
        list_node_t* delete_node = *list_start;
        *list_start = delete_node->next;
        (*list_start)->prev = NULL;
        delete delete_node;
    }
}

void move_to_end(list_node_t** list_start,
                 list_node_t** list_end, list_node_t* node)
{
    if (*list_start == NULL || *list_end == NULL) {
        //cout << "something wrong\n";
        return;
    }

    if (*list_end == node) {
        return;
    } 

    /* reach here, means list would be chanched */
    list_node_t* node_prev = node->prev;
    list_node_t* node_next = node->next;

    if (node_prev != NULL) {
        node_prev->next = node_next;
    } 
    if (node_next != NULL) {
        node_next->prev = node_prev;
    }

    if (*list_start == node) {
        *list_start = node_next;
    }

    (*list_end)->next = node; 
    node->prev = *list_end;
    node->next = NULL;
    *list_end = node;
} 

class LRUCache {
public:
    LRUCache(int capacity) {
        _list_start = NULL;
        _list_end = NULL;
        _capacity = capacity;
        _cur_num = 0;
    }
    
    int get(int key) {
        unordered_map<int, list_node_t*>::const_iterator iter = _hash.find(key);
        if ( iter == _hash.end() ) {
            cout << "query " << key << ", return -1\n";
            return -1;
        } else {
            int answer = iter->second->value;
            move_to_end(&_list_start, &_list_end, iter->second); /* touch the cache */
            cout << "query " << key << ", return " << answer <<"\n";
            return answer;
        }
    }
    
    void put(int key, int value) {
        if (_capacity == 0) {
            return;
        }
        unordered_map<int, list_node_t*>::const_iterator iter = _hash.find(key);
        if ( iter != _hash.end() ) {
            /* existed key */
            iter->second->value = value;
            move_to_end(&_list_start, &_list_end, iter->second); /* touch the cache */
            cout << "update key  " << key << " = " << value << "\n";
        } else {
            /* new key */
            cout << "insert key  " << key << " = " << value;
            if (_cur_num == _capacity) {
                int delete_key = _list_start->key;
                _hash.erase(delete_key);
                delete_start(&_list_start, &_list_end);
                cout << ", delete " << delete_key;
                _cur_num--;
            }
            list_node_t *new_node = new list_node_t();
            new_node->key = key;
            new_node->value = value;
            insert_to_end(&_list_start, &_list_end, new_node);
            pair<int, list_node_t*> new_hash_entry(key, new_node);
            _hash.insert(new_hash_entry);
            _cur_num++;
            cout << "\n";
        }        
    }
private:
    list_node_t* _list_start;
    list_node_t* _list_end;
    int _capacity, _cur_num;
    unordered_map<int, list_node_t*> _hash;
};


int main()
{
    LRUCache* obj = new LRUCache(2);
    obj->put(2, 1);
    obj->put(1, 1);
    obj->put(2, 3);
    obj->put(4, 1);
    obj->get(1);
    obj->get(2);
    #if 0
    LRUCache* obj = new LRUCache(3);
    //int param_1 = obj->get(2);
    obj->put(1, 1);
    obj->put(2, 2);
    obj->put(3, 3); /* 1, 2, 3*/
    obj->get(2);    /* 1, 3, 2*/
    obj->put(4, 4); /* 3, 2, 4 */
    obj->get(3);    /* 2, 4, 3 */
    obj->put(5, 5); /* 4, 3, 5 */
    obj->put(5, 6); /* 4, 3, 6 */
    obj->put(7, 7);
    obj->put(8, 8);
    obj->put(9, 9);
    #endif
    return 0;
}