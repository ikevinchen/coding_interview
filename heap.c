#include <stdio.h>
#include <stdlib.h>


#define MAX (100000)

typedef struct node {
    int data;
    int left_rank;
    int right_rank;
    struct node* left_node;
    struct node* right_node;
} Node;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(Node** root, int insert_data) {
    if (*root == NULL) {
        Node *new_node = malloc(sizeof(Node));
        new_node->data = insert_data;
        new_node->left_rank = new_node->right_rank = 0;
        new_node->left_node = new_node->right_node = NULL;
        *root = new_node;
    } else {
        Node *node = *root;
        if (insert_data < node->data) {
            swap(&insert_data, &(node->data));
        }
        if (node->left_rank < node->right_rank) {
            node->left_rank++;
            insert(&node->left_node, insert_data);
        } else {
            node->right_rank++;
            insert(&node->right_node, insert_data);
        }
    }
}

int pop(Node **root) {
    if (*root == NULL) {
        return -1;
    }

    Node* node = *root;
    int answer = node->data;
    if (node->left_node == NULL && node->right_node == NULL) {
        answer = node->data;
        free(node);
        *root = NULL;
        return answer;
    }

    /* find the smaller child to swap */
    node->data = MAX;
    while(1) {
        Node *swap_child = NULL;
        int swap_dir; /* 0:left 1:right */

        if (node->left_node == NULL) {
            swap_dir = 1;
        } else if (node->right_node == NULL) {
            swap_dir = 0;
        } else if (node->left_node->data < node->right_node->data) {
            swap_dir = 0;
        } else {
            swap_dir = 1;
        }

        if (swap_dir == 0) {
            swap_child = node->left_node;
        } else {
            swap_child = node->right_node;
        }
        swap(&node->data, &swap_child->data);

        if (swap_child->left_node == NULL && swap_child->right_node == NULL) {
            if (swap_dir == 0) {
                node->left_rank = 0;
                node->left_node = NULL;
            } else {
                node->right_rank = 0;
                node->right_node = NULL;
            }
            free(swap_child);
            break;
        }

        node = swap_child;
    }
    return answer;
}

int main() {
    Node *root = NULL;
    insert(&root, 4);
    insert(&root, 9);
    insert(&root, 8);
    insert(&root, 5);
    insert(&root, 10);
    insert(&root, 2);

    int min;
    while((min = pop(&root)) != -1) {
        printf("%d ", min);
    }
    printf("\n");
}
















