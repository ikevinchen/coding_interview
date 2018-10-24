#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<int, int> Hash; /* sum, ref_cnt */

void previous_sum_add(int sum) {
    unordered_map<int, int>::iterator iter = Hash.find(sum);
    if (iter == Hash.end()) {
        pair<int, int> new_entry (sum, 1);
        Hash.insert(new_entry);
    } else {
        iter->second++;
    }
}

void previous_sum_del(int sum) {
    unordered_map<int, int>::iterator iter = Hash.find(sum);
    if (iter == Hash.end()) {
        cout << "something wrong" << endl;
    } else {
        iter->second--;
        if (iter->second == 0) {
            Hash.erase(iter);
        }
    }
}

int previous_sum_count(int sum) {
    unordered_map<int, int>::iterator iter = Hash.find(sum);
    if (iter == Hash.end()) {
        return 0;
    } else {
        return iter->second;
    }
}

typedef struct node_s {
    int data;
    struct node_s* left;
    struct node_s* right;
} Node_t ;

int answer = 0;

void check(Node_t *node, int last_sum, int target) {
    /*
        At each node, we check the sum that from every starting node.

        Ex, at node D, we check the sum (A-->D) (B-->D) (C-->D) (D)
        The precious sum has alreay record (A) (A-->B) (A-->C)

        so we need to check
            (1) A-->D            (last_sum + D)
            (2) B-->D, C-->D , D (last_sum - each previous sum)

                  A ---> B ---> C ---> D
                |---|   *****************
                |--------|     **********
                |----------------|    ***
                  (previous sum)

     */

     int cur_sum = last_sum + node->data;
     if (cur_sum == target) {
        answer++;
     }
     answer += previous_sum_count(cur_sum-target);

     /* traverse next */
     previous_sum_add(cur_sum);
     if(node->left != NULL)  check(node->left,  cur_sum, target);
     if(node->right != NULL) check(node->right, cur_sum, target);
     previous_sum_del(cur_sum);
}

int main() {
    Node_t *root = NULL;
    Node_t *n_0 = new Node_t();
    Node_t *n_1 = new Node_t();
    Node_t *n_2 = new Node_t();
    Node_t *n_3 = new Node_t();
    Node_t *n_4 = new Node_t();
    Node_t *n_5 = new Node_t();
    Node_t *n_6 = new Node_t();
    Node_t *n_7 = new Node_t();

    /*
                3
              /
            1       -1
          /   \    /
        -1    -1  -2    1
                  /
                 0
     */

    root = n_0;
    n_0->data = 3;      n_0->left = n_1;    n_0->right = n_2;
    n_1->data = -1;     n_1->left = n_3;    n_1->right = n_4;
    n_2->data = -1;     n_2->left = n_5;    n_2->right = n_5;
    n_3->data = -1;     n_3->left = NULL;   n_3->right = NULL;
    n_4->data = -1;     n_4->left = NULL;   n_4->right = NULL;
    n_5->data = -2;     n_5->left = n_7;    n_5->right = NULL;
    n_6->data = 1;      n_6->left = NULL;   n_6->right = NULL;
    n_7->data = 0;      n_7->left = NULL;   n_7->right = NULL;


    answer = 0;
    check(root, 0, 0);
    cout << "answer = " << answer << endl;
    return 0;
}
