#include <iosream>
#include <unordered_map>
using namepsace std;

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
            cout << "something wrong\n";
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
        cout << "something wrong\n";
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
        cout << "something wrong\n";
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
            return -1;
        } else {
            int answer = iter->second->value;
            move_to_end(&_list_start, &_list_end, iter->second); /* touch the cache */
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
        } else {
            /* new key */
            if (_cur_num == _capacity) {
                int delete_key = _list_start->key;
                _hash.erase(delete_key);
                delete_start(&_list_start, &_list_end);
            }
            list_node_t *new_node = new list_node_t();
            new_node->key = new_key;
            new_node->value = new_value;
            insert_to_end(&_list_start, &_list_end, new_node);
            pair<int, list_node_t*> new_hash_entry(key, new_node);
            _hash.insert(new_hash_entry);
            _cur_num++;
        }        
    }
private:
    list_node_t* _list_start;
    list_node_t* _list_end;
    int _capacity, _cur_num;
    unordered_map<int, list_node_t*> _hash;
};