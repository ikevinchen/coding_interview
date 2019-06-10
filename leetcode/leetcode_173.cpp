#include <iostream>
#include <stack>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
struct node_record {
	TreeNode* tree_node;
	bool need_expand;
};
 
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        if (root != NULL) {
			node_record new_record;
			new_record.tree_node = root;
			new_record.need_expand = true;
			_stack.push(new_record);
		}
    }
    
    /** @return the next smallest number */
    int next() {
        if (_stack.empty()) {
			return -1;
		} else {
			/* expand the top one recursively */
			while (_stack.top().need_expand == true) {				
				TreeNode* expand_node = _stack.top().tree_node;
				_stack.pop();	
				
				/* push rihgt */
				node_record new_record;
				if (expand_node->right != NULL) {
					new_record.tree_node = expand_node->right;
					new_record.need_expand = true;
					_stack.push(new_record);
				}
					
				/* push self */
				new_record.tree_node = expand_node;
				new_record.need_expand = false;
				_stack.push(new_record);
				
				/* push left */				
				if (expand_node->left != NULL) {
					new_record.tree_node = expand_node->left;
					new_record.need_expand = true;
					_stack.push(new_record);
				}
				
				
			}
			int answer = _stack.top().tree_node->val;
			_stack.pop();
			return answer;
		}		
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !_stack.empty();
    }
private:
	stack<node_record> _stack;
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
 
int main()
{
	TreeNode node_4(4), node_3(3), node_10(10), node_6(6), node_5(5), node_7(7), node_11(11);
	TreeNode* root = &node_4;
	node_4.left  = &node_3; node_4.right  = &node_10;
	node_10.left = &node_6; node_10.right = &node_11;
	node_6.left  = &node_5; node_6.right  = &node_7;
	
	BSTIterator* obj = new BSTIterator(root);
	while (obj->hasNext()) {
		cout << obj->next() << " ";
	}
	cout << endl;
	
	return 0;
}
