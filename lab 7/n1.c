#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node * next;
} node_t;

void display(node_t *n);
node_t *popFirstLinkedList(node_t *n);
node_t *pushToLinkedList(node_t *n, int value);
main () {
	node_t *root, *first, *second = 0;

	root = (node_t *)malloc(sizeof(node_t));
	root->val = 1;

	first = (node_t *)malloc(sizeof(node_t));
	first->val = 2;

	second = (node_t *)malloc(sizeof(node_t));
	second->val = 3;

	root->next = first;
	first->next = second;

	printf("Linked List:\n");
	display(root);
	printf("\n");
	printf("After popping linked list:\n");
	node_t *topList = popFirstLinkedList(root);
	display(topList);
	printf("\nAfter pushing the values 8, 7 & 13 in that order to linked list:\n");
	node_t *pushedList = pushToLinkedList(root,8);
	display(pushedList);

	node_t *pushedList2 = pushToLinkedList(pushedList,7);
        display(pushedList2);

	node_t *pushedList3 = pushToLinkedList(pushedList2,13);
        display(pushedList3);
}

void display(node_t *n) {
        while (n != 0) {
                printf("%d => ", n->val);
                n = n->next;
        }
        printf("NULL\n");
}

node_t *popFirstLinkedList(node_t *n) {
	if (n) {
		n = n->next;
	}
	return n;
}

node_t *pushToLinkedList(node_t *n, int value) {
	node_t *temp = malloc(sizeof(node_t));
	temp->val = value;
	temp->next = n;
	n = temp;
	return n;
}
