#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
    int data;
    struct node_s* left;
    struct node_s* right;
    int left_rank;
    int right_rank;
} Node_t;

void insert(int insert_value, Node_t **node) {
    if (*node == NULL) {
        *node = malloc(sizeof(Node_t));
        (*node)->data = insert_value;
        (*node)->left = (*node)->right = NULL;
        (*node)->left_rank = (*node)->right_rank = 0;
    } else {
        int next_insert_value;

        if (insert_value < (*node)->data) {
            next_insert_value = (*node)->data;
            (*node)->data = insert_value;
        } else {
            next_insert_value = insert_value;
        }

        if ((*node)->left_rank < (*node)->right_rank) {
            (*node)->left_rank++;
            insert(next_insert_value, &((*node)->left));
        } else {
            (*node)->right_rank++;
            insert(next_insert_value, &((*node)->right));
        }
    }
}

void pop_recusive(Node_t **node) {

    if ((*node)->left == NULL && (*node)->right == NULL) {
        free(*node);
        *node = NULL;
        return;
    }

    Node_t **next_pop_node;
    int replace_value;

    if ((*node)->left == NULL) {
        next_pop_node = &((*node)->right);
        replace_value = (*node)->right->data;
        (*node)->right_rank--;
    } else if ((*node)->right == NULL) {
        next_pop_node = &((*node)->left);
        replace_value = (*node)->left->data;
        (*node)->left_rank--;
    } else if ((*node)->left->data < (*node)->right->data) {
        next_pop_node = &((*node)->left);
        replace_value = (*node)->left->data;
        (*node)->left_rank--;
    } else {
        next_pop_node = &((*node)->right);
        replace_value = (*node)->right->data;
        (*node)->right_rank--;
    }

    (*node)->data = replace_value;
    pop_recusive(next_pop_node);
}

void pop(Node_t **root) {

    if (*root == NULL) {
        printf("empty\n");
    } else {
        printf("pop %d\n", (*root)->data);
        pop_recusive(root);
    }

}

int main() {
    Node_t *heap_root= NULL;

    insert(3,&heap_root);
    insert(1,&heap_root);
    insert(5,&heap_root);
    insert(2,&heap_root);
    insert(6,&heap_root);
    insert(7,&heap_root);
    insert(4,&heap_root);

    pop(&heap_root);
    pop(&heap_root);
    pop(&heap_root);
    pop(&heap_root);
    pop(&heap_root);
    pop(&heap_root);
    pop(&heap_root);
    pop(&heap_root);

    return 0;
}