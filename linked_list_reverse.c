#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* next;
} Node;

void InsertHead(Node **head, Node *new) {
	new->next = *head;
	*head = new;
}

void Insert(Node **head, int data) {
	Node *new_node = malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;
	if (*head == NULL) {
		*head = new_node;
	} else {
		Node *iter = *head;
		while(iter->next != NULL) {
			iter = iter->next;
		}
		iter->next = new_node;
	}	
}

void Print(Node *head) {
	Node *iter = head;
	while(iter != NULL) {
		printf("%d ", iter->data);
		iter = iter->next;
	}
	printf("\n");	
}

int main() {
	Node *head = NULL;
	Insert(&head, 1);
	Insert(&head, 2);
	Insert(&head, 3);
	Insert(&head, 4);
	Insert(&head, 5);
	Print(head);
	
	Node *head_new = NULL;
	Node *iter = head;
	while (iter != NULL) {
		Node *next_backup = iter->next;
		InsertHead(&head_new, iter);
		iter = next_backup;
	}
	Print(head_new);
  return 0;
}
