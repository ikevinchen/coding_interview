#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(NULL), right(NULL) {}
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:
    int averageOfSubtree(TreeNode* root) {
        if (root == NULL) {
            return 0;
        } else {
            int final_ans = 0, cnt = 0, sum = 0;
            DFS(root, &cnt, &sum, &final_ans);
            return final_ans;
        }
    }
private:
    void DFS(TreeNode* root, int* ret_cnt, int* ret_sum, int* final_ans) {
        int left_subtree_cnt = 0;
        int left_subtree_sum = 0;
        int right_subtree_cnt = 0;
        int right_subtree_sum = 0;
        
        if (root->left != NULL) {
            DFS(root->left, &left_subtree_cnt, &left_subtree_sum, final_ans);
        }
        if (root->right != NULL) {
            DFS(root->right, &right_subtree_cnt, &right_subtree_sum, final_ans);
        }
        
        *ret_sum = root->val + left_subtree_sum + right_subtree_sum;
        *ret_cnt = 1 + left_subtree_cnt + right_subtree_cnt;
        cout << "val = " << root->val << " (sum = " << *ret_sum << ", cnt = " << *ret_cnt << ")"; 
        if (root->val == (int)((*ret_sum)/(*ret_cnt))) {
            cout << " ==> Yes";
            (*final_ans)++;
        }
        cout << endl;
    }
};

int main()
{
    TreeNode A(2);
    TreeNode B(1);
    TreeNode C(2, &A, &B);
    Solution S;
    cout << S.averageOfSubtree(&C) << endl;
    return 0;
}
