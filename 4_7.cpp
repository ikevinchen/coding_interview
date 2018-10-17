#include <iostream>
#include <list>
#include <stdio.h>
using namespace std;

#define BITSET(_bitmap_, _bit_) ((_bitmap_) |= (1 << (_bit_)))
#define BIT(_bitmap_, _bit_)    ((_bitmap_) & (1 << (_bit_)))
#define MAX (5)
int graph_bitmap[MAX];
int graph_r_bitmap[MAX]; /* reversed graph */

void graph_clear() {
    for (int i = 0; i < MAX; i++) {
        graph_bitmap[i]   = 0x0;
        graph_r_bitmap[i] = 0x0;
    }
}

int is_subset(int bp1, int bp2) {
    /* check if bp1 is the subset of bp2 */
    if (bp1 & (~bp2)) {
        return 0;
    } else {
        return 1;
    }
}

void add_edge(char s, char v) {
    BITSET(graph_bitmap[s-'a'],   v-'a');
    BITSET(graph_r_bitmap[v-'a'], s-'a');
}

void run() {
    int answer_bitmap = 0x0, candidate_bitmap = 0x0;
    list<int> answer;
    
    /* For the first run, add the node without any dependency into candidate */
    for (int i = 0; i < MAX; i++) {
        if (graph_r_bitmap[i] == 0x0) {
            BITSET(candidate_bitmap, i);
        }
    }    
    
    /* In each run, taverse each candidate to see if it could be the answer. 
     * If it is success, check its neighbors again.
     *
     *   About time complexity:
     *      For BFS of graph, the time complexity is O(V+E)
     *         1. add the source into visited queue
     *         2. For each element taken from the queue,
     *            add its non-visted neighbor to the queue
     *
     *      It is the same for this question.
     *         1. add the source into candidate queue
     *         2. For each candidate taken from the queue.
     *            If this candidate's dependency has all been resolved,
     *            add candidate's non-visted neighbor to the queue 
     *        (we just add one more check, and this check is O(1))
     */
    while (candidate_bitmap != 0x0) {

        int candidate_bitmap_next = 0x0;
        
        for (int candidate = 0; candidate < MAX; candidate++) {

            if (BIT(candidate_bitmap, candidate)) {            
                if (is_subset(graph_r_bitmap[candidate], answer_bitmap)) {
                    
                    /* all its dependency has been the answer,
                     * so this one could be answer too
                     */
                    BITSET(answer_bitmap, candidate);
                    answer.push_back(candidate);
                
                    for (int neighbor = 0; neighbor < MAX; neighbor++) {
                        if ( BIT(graph_bitmap[candidate], neighbor) &&
                            !BIT(answer_bitmap, neighbor)) {
                            BITSET(candidate_bitmap_next, neighbor);
                        }
                    }
                }                
            }    

        }
        
        candidate_bitmap = candidate_bitmap_next;
    }
    
    /* output */
    if (answer.size() != MAX) {
        cout << "no answer" << endl;
    } else {
        list<int>::iterator iter;
        for (iter=answer.begin(); iter != answer.end(); iter++) {
            cout << (char)('a'+*iter) << " ";
        }
        cout << endl;
    }
}

int main() {

    /* Example 1 :
    
                a -----> b -----> e -----> d
                |                          |
                |                          |
                |                          |
                -------> c <----------------
    
    */
    graph_clear();
    add_edge('a', 'b');
    add_edge('a', 'c');
    add_edge('b', 'e');
    add_edge('d', 'c');
    add_edge('e', 'd');    
    run();
    
    
    /* Example 2 :
    
                a -----> b -----> e -----> d
                |                 ^        |
                |                 |        |
                |        ---------         |
                |        |                 |
                -------> C <----------------
    
    */
    graph_clear();
    add_edge('a', 'b');
    add_edge('a', 'c');
    add_edge('c', 'e');
    add_edge('b', 'e');
    add_edge('d', 'c');
    add_edge('e', 'd');    
    run();
    
    
    /* Example 3 :
    
                a -----> b        e        d
                |                          ^
                |                          |
                |                          |
                -------> C ----------------
    
    */
    graph_clear();
    add_edge('a', 'b');
    add_edge('a', 'c');
    add_edge('c', 'd');
    run();
    

    return 0;
}
