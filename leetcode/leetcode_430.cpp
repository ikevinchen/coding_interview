#include <iostream>
#include <stack>
using namespace std;

typedef struct Node_s {
    int val;
    struct Node_s* prev;
    struct Node_s* next;
    struct Node_s* child;
} Node;

stack<Node*> node_stack;

void print(Node* head) {
	Node* node_iter = head;
	
	while (node_iter != NULL) {
		cout << "val = " << node_iter->val << " ,";
		if (node_iter->prev) {
			cout << "prev = " << node_iter->prev->val << " ,"; }
		if (node_iter->next) {
			cout << "next = " << node_iter->next->val << " ,"; }
		if (node_iter->child) {
			cout << "child = " << node_iter->child->val << " ,"; }
		cout << endl;
		node_iter = node_iter->next;	
	}
}

Node* flatten(Node* head) {
	if (head == NULL) {
		return NULL;
	}
	
	Node* node_iter = head;
	
	while(1) {
		Node* node_next;
		if (node_iter->child != NULL) {
			node_next = node_iter->child;
			if (node_iter->next != NULL) {
				node_stack.push(node_iter->next);
			}
			node_iter->child = NULL;
		} else if (node_iter->next != NULL) {
			node_next = node_iter->next;
		} else if (!node_stack.empty()){
			node_next = node_stack.top();
			node_stack.pop();
		} else {
			break;
		}
		node_iter->next = node_next;
		node_next->prev = node_iter;
		node_iter = node_next;
	}
	return head;
}

int main()
{
	Node n1, n2, n3, n4, n5;
	n1.val = 1; n1.prev = NULL; n1.next = &n2; n1.child = &n3;
	n2.val = 2; n2.prev = &n1; n2.next = NULL; n2.child = NULL;
	n3.val = 3; n3.prev = NULL; n3.next = &n4; n3.child = &n5;
	n4.val = 4; n4.prev = &n3; n4.next = NULL; n4.child = NULL;
	n5.val = 5; n5.prev = NULL; n5.next = NULL; n5.child = NULL;
	flatten(&n1);
	print(&n1);
	return 0;
}

