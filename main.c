#include <stdio.h>
#include <stdlib.h>

// A Linked List Node
struct Node
{
	int data;
	struct Node* next;
};

// Helper function to print a given linked list
void printList(struct Node* head)
{
	struct Node* ptr = head;
	while (ptr)
	{
		printf("%d —> ", ptr->data);
		ptr = ptr->next;
	}

	printf("NULL\n");
}

// Helper function to insert a new node at the beginning of the linked list
void push(struct Node** head, int data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = *head;
	*head = newNode;
}

// Function takes the node from the front of the source and move it
// to the front of the destination
void moveNode(struct Node** destRef, struct Node** sourceRef)
{
	// if the source list empty, do nothing
	if (*sourceRef == NULL) {
		return;
	}

	struct Node* newNode = *sourceRef;  // the front source node
	*sourceRef = (*sourceRef)->next;	// advance the source pointer
	newNode->next = *destRef;   		// link the old dest off the new node
	*destRef = newNode; 				// move dest to point to the new node
}

int main(void)
{
	// input keys
	int keys[] = { 1, 2, 3 };
	int n = sizeof(keys)/sizeof(keys[0]);

	// construct the first linked list
	struct Node* a = NULL;
	for (int i = n-1; i >= 0; i--) {
		push(&a, keys[i]);
	}

	// construct the second linked list
	struct Node* b = NULL;
	for (int i = 0; i < n; i++) {
		push(&b, 2*keys[i]);
	}

	// move the front node of the list `b` to the front of the list `a`
	moveNode(&a, &b);

	// print both lists
	printf("First List: ");
	printList(a);

	printf("Second List: ");
	printList(b);

	return 0;
}