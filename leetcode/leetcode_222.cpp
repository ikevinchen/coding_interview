#include <iostream>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int countNodes(TreeNode* root) {
	if (root == NULL)
		return 0;
	
	int max_height = -1;
	int num_of_max_height = 0;
	
	stack<TreeNode*> s_node;
	stack<int> s_height;
	
	s_node.push(root);
	s_height.push(0);
	
	while (!s_node.empty())
	{
		TreeNode* node_got = s_node.top();
		int height_got = s_height.top();
		s_node.pop();
		s_height.pop();
		
		if (node_got->left == NULL && node_got->right == NULL) {
			/* It is a leaf */
			if (max_height == -1) {
				max_height = height_got;
				num_of_max_height++;
			} else if (height_got == max_height) {
				num_of_max_height++;
			} else {
				break; /* we encounter the leaf node but not at depthest level */
			}
		}
		
		if (node_got->right != NULL) {
			s_node.push(node_got->right);
			s_height.push(height_got + 1);
		}
		
		if (node_got->left != NULL) {
			s_node.push(node_got->left);
			s_height.push(height_got + 1);
		}
	}
	
	if (max_height == 0) {
		return 1;
	} else if (max_height > 0) {
		/* answer = 2^(max_height) - 1 + num_of_max_height */
		int answer = 1;
		for (int i = 0; i < max_height; i++) {
			answer *= 2;
		}
		answer = answer - 1 + num_of_max_height;
		return answer;
	} else {
		return -1;
	}	 
}

int main()
{
	TreeNode n_1(1); TreeNode n_2(2); TreeNode n_3(3); TreeNode n_4(4);
	TreeNode n_5(5); TreeNode n_6(6); TreeNode n_7(7); TreeNode n_8(8);
	TreeNode *root = &n_1;
	cout << countNodes(root) << endl;
	n_1.left = &n_2;
	cout << countNodes(root) << endl;
	n_1.right = &n_3;
	cout << countNodes(root) << endl;
	n_2.left = &n_4;
	n_2.right = &n_5;	
	cout << countNodes(root) << endl;
	n_3.left = &n_6;
	n_3.right = &n_7;
	cout << countNodes(root) << endl;
	n_4.left = &n_8;
	cout << countNodes(root) << endl;
	return 0;
}
