#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} Node;

void Print(Node *root) {
    if (root != NULL) {
        printf("              %d              \n", root->data);
        
        if (root->left == NULL) {
        printf("                ");
        } else {
        printf("       %d       ", root->left->data);
        }
        
        if (root->right == NULL) {
        printf(                 "              \n");
        } else {
        printf(                 "    %d     \n", root->right->data);
        }
        
        if (root->left == NULL) {
        printf("               ");
        } else {
        
        if (root->left->left == NULL) {
        printf("       ");
        }else {
        printf("  %d   ", root->left->left->data);
        }
        
        if (root->left->right == NULL) {
        printf(        "        ");
        }else {
        printf(        "    %d  ", root->left->right->data);
        }            
        }
        
        if (root->right == NULL) {
        printf("                \n");
        } else {
        
        if (root->right->left == NULL) {
        printf(                  "       ");
        }else {
        printf(                  "  %d   ", root->right->left->data);
        }
        
        if (root->right->right == NULL) {
        printf(                          "        \n");
        }else {
        printf(                          "    %d  \n", root->right->right->data);
        }            
        }        
    }
    printf("----------------------------------\n");
}

void Insert(Node **root, int new_data) {
    Node **iter = root;
    while (*iter != NULL) {
        if (new_data <= (*iter)->data) {
            iter = &((*iter)->left);
        } else {
            iter = &((*iter)->right);
        }
    }
    *iter = malloc(sizeof(Node));
    (*iter)->data = new_data;
    (*iter)->left = (*iter)->right = NULL;
}

int FindMax(Node *iter) {
    while (iter->right != NULL) {
        iter = iter->right;
    }
    return iter->data;
}

Node* NewRootAfterDelete(Node *cur_node, int target) {
    if (cur_node == NULL) {
        return NULL;
    }
    if (target < cur_node->data) {
        cur_node->left = NewRootAfterDelete(cur_node->left, target);
        return cur_node;
    } else if (target > cur_node->data) {
        cur_node->right = NewRootAfterDelete(cur_node->right, target);
        return cur_node;
    } else {
        if (cur_node->left == NULL && cur_node->right == NULL) {
            free(cur_node);
            return NULL;
        } else if (cur_node->left == NULL) {
            Node *backup_ptr = cur_node->right;
            free(cur_node);
            return backup_ptr;
        } else if (cur_node->right == NULL) {
            Node *backup_ptr = cur_node->left;
            free(cur_node);
            return backup_ptr;
        } else {
            int left_max = FindMax(cur_node->left);
            cur_node->data = left_max;
            cur_node->left = NewRootAfterDelete(cur_node->left, left_max);
            return cur_node;
        }
    }
}

void Delete(Node **root, int target) {
    *root = NewRootAfterDelete(*root, target);
}

int main() {
    Node *root = NULL;
    
    Insert(&root, 4);
    Insert(&root, 2);
    Insert(&root, 6);
    Insert(&root, 1);
    Insert(&root, 3);
    Insert(&root, 5);
    Insert(&root, 7);
    Print(root);
    
    Delete(&root, 4); Print(root);
    Delete(&root, 2); Print(root);
    Delete(&root, 1); Print(root);
    Delete(&root, 3); Print(root);
    Delete(&root, 6); Print(root);
    Delete(&root, 5); Print(root);
    Delete(&root, 7); Print(root);

    return 0;
}
