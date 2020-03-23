#include <iostream>
#include <list>
#include <vector>
#define MAX_NUM (1000)
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        vector<TreeNode*> answer;
        
        if (root == NULL) {
            return answer;
        }        

        /* init */
        for (int i = 0; i <= MAX_NUM; i++) {
            node_arr[i] = NULL;
            node_parent_arr[i] = NULL;
            node_answer[i] = false;
        }
        
        /* traverse each value by BFS */
        list<TreeNode*> list;
        list.push_back(root);
        node_parent_arr[root->val] = NULL;
        while (!list.empty()) {
            TreeNode* node = list.front();
            node_arr[node->val] = node;
            if (node->left != NULL) {
                node_parent_arr[node->left->val] = &(node->left);
                list.push_back(node->left);
            }
            if (node->right != NULL) {
                node_parent_arr[node->right->val] = &(node->right);
                list.push_back(node->right);
            }
            list.pop_front();
        }

        /* start to delete node */
        node_answer[root->val] = true;
        for (int i = 0; i < to_delete.size(); i++) {
            TreeNode* node = node_arr[to_delete[i]];
            TreeNode** node_parent = node_parent_arr[to_delete[i]];
    
            /* the children will be the new answer */
            if (node->left != NULL) {
                node_answer[node->left->val] = true;
            }
            if (node->right != NULL) {
                node_answer[node->right->val] = true;
            }

            /* delete this node and update its parnet and child */
            node_answer[node->val] = false;
            if (node_parent != NULL) {
                *(node_parent) = NULL;
            }
            if (node->left != NULL) {
                node_parent_arr[node->left->val] = NULL;
            }
            if (node->right != NULL) {
                node_parent_arr[node->right->val] = NULL;
            }            
            node->left = NULL;
            node->right = NULL;    
        }
        /* generate answer */
        for (int i = 0; i <= MAX_NUM; i++) {
            if (node_answer[i] == true) {
                answer.push_back(node_arr[i]);
            }
        }
        return answer;
    }
private:
    TreeNode*  node_arr[1+MAX_NUM];
    TreeNode** node_parent_arr[1+MAX_NUM];
    bool node_answer[1+MAX_NUM];
};

void Print(TreeNode* root) {
    /* traverse each value by BFS */
    if (root == NULL) {
        return;
    }
    list<TreeNode*> list;
    list.push_back(root);
    while (!list.empty()) {
        TreeNode* node = list.front();
        cout << node->val << " ";
        if (node->left != NULL) {
            list.push_back(node->left);
        }
        if (node->right != NULL) {
            list.push_back(node->right);
        }
        list.pop_front();
    }
    cout << endl;
}

int main()
{
    TreeNode n1(1); TreeNode n2(2); TreeNode n3(3); TreeNode n4(4);
    TreeNode n5(5); TreeNode n6(6); TreeNode n7(7);
    n1.left = &n2; n1.right = &n3;
    n2.left = &n4; n2.right = &n5;
    n3.left = &n6; n3.right = &n7;
    
    Solution S;
    vector<int> del_arr;
    del_arr.push_back(2);
    del_arr.push_back(6);
    del_arr.push_back(3);
    vector<TreeNode*> answer = S.delNodes(&n1, del_arr);
    for (int i = 0; i < answer.size(); i++) {
        Print(answer[i]);
    }
    return 0;
}
