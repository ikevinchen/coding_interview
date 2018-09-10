#include <iostream>
#include <unordered_map>
using namespace std;

/* key : sum, data : reference count */
typedef unordered_map<int,int> HashMap;

typedef struct node {
    int data;
    struct node *left, *right;
} Node;

void check_node(Node *n, HashMap *hash,
                int last_sum, int target, int *ans) {
    HashMap::iterator iter;
    int cur_sum = last_sum + n->data;

    /* ans increse when
        1) cur_sum meet targe
        2) some previous path sum meet targe
     */
    if (cur_sum == target) {
        (*ans) ++;
    }

    iter = hash->find(cur_sum-target);
    if(iter!=hash->end()) {
        (*ans) += iter->second;
    }

    /* traverse downward if there is child */
    if (n->left != NULL || n->right != NULL) {
        /* add this cur_sum into hash */
        iter = hash->find(cur_sum);
        if(iter!=hash->end()) {
            iter->second++;
        } else {
            hash->insert(HashMap::value_type(cur_sum, 1));
            //or hash->insert(pair<int,int>(cur_sum, 1));
        }

        /* traverse child */
        if(n->left != NULL) {
            check_node(n->left, hash, cur_sum, target, ans);
        }
        if(n->right != NULL) {
            check_node(n->right, hash, cur_sum, target, ans);
        }

        /* delete hash after back */
        iter = hash->find(cur_sum);
        if (iter->second == 1) {
            hash->erase(iter);
        } else {
            iter->second--;
        }
    }
}

void check(Node *root, int target) {
    HashMap hash;
    int ans = 0;
    if (root != NULL) {
        check_node(root, &hash, 0, target, &ans);
    }
    cout << "ans = " << ans << endl;
}


int main() {
    Node *root = NULL;
    Node *n_0 = new Node();
    Node *n_1 = new Node();
    Node *n_2 = new Node();
    Node *n_3 = new Node();
    Node *n_4 = new Node();
    Node *n_5 = new Node();
    Node *n_6 = new Node();
    Node *n_7 = new Node();

    /*
                3
              /    \
            1       -1
          /   \    /   \
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

    check(root, 0);
}
