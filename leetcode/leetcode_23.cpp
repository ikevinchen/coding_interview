/**
 *  * Definition for singly-linked list.
 *   * struct ListNode {
 *    *     int val;
 *     *     ListNode *next;
 *      *     ListNode(int x) : val(x), next(NULL) {}
 *       * };
 *        */
 
#include <iostream>
#include <queue>
 
using namespace std; 
 
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

typedef pair<ListNode*, int> Pair; /* node*, K-th list */

struct CompareFunc { 
    bool operator()(Pair const& p1, Pair const& p2) 
    { 
        return p2.first->val < p1.first->val; 
    } 
};
 
class Solution {
public:
    /* merge K sorted list into one */
    ListNode* mergeKLists(vector<ListNode*>& lists) {        
        int K = lists.size();
        int i;
        
        ListNode* answer_root = NULL;
        ListNode* answer_end = NULL;
        priority_queue<Pair, vector<Pair>, CompareFunc> pq;    /* min-heap */    
        for (i = 0; i < K; i++) {
            if (lists[i] != NULL) {
                pq.push(make_pair(lists[i], i)); 
            }
        }
        
        /* start */
        while (!pq.empty()) {
            Pair top_element = pq.top();
            pq.pop();            
            ListNode* new_node = new ListNode(top_element.first->val);
            if (answer_root == NULL) {
                answer_root = new_node;
                answer_end = new_node;
            } else {
                answer_end->next = new_node;
                answer_end = new_node;
            }
            if (top_element.first->next != NULL) {
                pq.push(make_pair(top_element.first->next, top_element.second)); 
            }
        }        
        return answer_root;
    }
};

void ListAdd(ListNode** head, int new_value) {
    ListNode* new_node = new ListNode(new_value);
    if (*head == NULL) {
        *head = new_node;
    } else {
        ListNode* iter = *head;
        while (iter->next != NULL) {
            iter = iter->next;
        }
        iter->next = new_node;
    }    
}

void ListPrint(ListNode* head) {
    ListNode* iter = head;
    while (iter != NULL) {
        cout << iter->val << " ";
        iter = iter->next;
    }
    cout << "\n";
}

int main() {
    ListNode* list_empty = NULL; 
    ListNode* list_1 = NULL;    
    ListNode* list_2 = NULL;
    ListNode* list_3 = NULL;
    Solution S;
    vector<ListNode*> lists;
    ListNode* ans = NULL;
    
    lists.push_back(list_empty);
    ans = S.mergeKLists(lists);
    ListPrint(ans);    
    
    ListAdd(&list_1, 1); ListAdd(&list_1, 4); ListAdd(&list_1, 5);
    ListAdd(&list_2, 1); ListAdd(&list_2, 3); ListAdd(&list_2, 4);
    ListAdd(&list_3, 2); ListAdd(&list_3, 6);    
    lists.push_back(list_1);
    lists.push_back(list_2);
    lists.push_back(list_3);
    ans = S.mergeKLists(lists);
    ListPrint(ans);
    return 0;
}
