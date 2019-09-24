#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
	struct ListNode* head = NULL;
	struct ListNode* tail = NULL;
	struct ListNode* l1_itr = l1;
	struct ListNode* l2_itr = l2;
	int carry = 0;
	while (l1_itr != NULL || l2_itr != NULL || carry != 0) {
		int sum = carry;
		struct ListNode* new_digit = malloc(sizeof(struct ListNode));	

		if (l1_itr != NULL) {
			sum += l1_itr->val;
			l1_itr = l1_itr->next;
		}
		if (l2_itr != NULL) {
			sum += l2_itr->val;
			l2_itr = l2_itr->next;
		}

		carry = sum / 10;
		new_digit->val = sum % 10;
		new_digit->next = NULL;
		
		if (head == NULL) {
			head = new_digit;
			tail = new_digit;
		} else {
			tail->next = new_digit;
			tail = new_digit;
		}		
	}
	return head;
}

void add_list(struct ListNode** head, int val)
{
	struct ListNode* node = malloc(sizeof(struct ListNode));
	node->val = val;
	node->next = NULL;
	if (*head == NULL) {
		*head = node;
	} else {
		struct ListNode* iter = *head;
		while(iter->next != NULL) {
			iter = iter->next;
		}
		iter->next = node;
	}
}

void print_list(struct ListNode* list)
{
	struct ListNode* iter = list;
	while(iter != NULL) {
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");
}

int main()
{
	struct ListNode* list_1 = NULL;
	struct ListNode* list_2 = NULL;
	
	add_list(&list_1, 5);
	add_list(&list_2, 5);
	print_list(addTwoNumbers(list_1, list_2));	
	
	add_list(&list_1, 2); add_list(&list_1, 4); add_list(&list_1, 3);
	add_list(&list_2, 5); add_list(&list_2, 6); add_list(&list_2, 4);
	print_list(addTwoNumbers(list_1, list_2));
	return 0;
}

