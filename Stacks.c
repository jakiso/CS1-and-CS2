#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "KindredSpirits.h"

#define EMPTY_STACK_ERR INT_MIN

// Data structure to store preorder and postorder
typedef struct Stack
{
	int *array;
	int size;
	int capacity;
} Stack;

Stack *createStack(int capacity)
{
	Stack *s;
	if ((s = malloc(sizeof(Stack))) == NULL)
	{
		return NULL;
	}
	if ((s->array = malloc(sizeof(int) * capacity)) == NULL)
	{
		// Checks to see of capacity is valid
		free(s);
		return NULL;
	}
	// Creates blank stack
	s->size = 0;
	s->capacity = capacity;
	return s;
}

Stack *destroyStack(Stack *s)
{
	if (s == NULL)
	{
		return NULL;
	}
	free(s->array);
	free(s);
	return NULL;
}

int isEmpty(Stack *s)
{
	return (s == NULL || s->size == 0);
}

int isFull(Stack *s)
{
	return (s == NULL || s->size == s->capacity);
}

void push(Stack *s, int data)
{
	if (isFull(s))
	{
		fprintf(stderr, "\n   Error: Stack is full in push().\n");
		return;
	}
	 s->array[ s->size++ ] = data;
}

// Subtracts from top of stack
int pop(Stack *s)
{
	if (isEmpty(s))
	{
		fprintf(stderr, "\n   Error: Stack is empty in pop().\n");
		return EMPTY_STACK_ERR;
	}
	return s->array[ --s->size ];
}

// Checks value on top of stack
int peek(Stack *s)
{
	if (isEmpty(s))
	{
		fprintf(stderr, "\n   Error: Stack is empty in peek().\n");
		return EMPTY_STACK_ERR;
	}
	return s->array[ s->size-1 ];
}

node *createnode(int data)
{
	node *n = malloc(sizeof(node));

	n->data = data;
	n->left = n->right = NULL;

	return n;
}
int isReflection(node *a, node *b)
{
	// Returns 1 if they go through all nodes and are
	// reflections
	if (a == NULL && b == NULL)
	{
		return 1;
	}
	// Checks if nodes are uneven
	if (a == NULL && b != NULL)
	{
		return 0;
	}
	if (a != NULL && b == NULL)
	{
		return 0;
	}
	// Checks if the data are the same
	if (a->data != b->data)
	{
		return 0;
	}
	// Recursive call to check all nodes
	return isReflection(a->left, b->right) && isReflection(a->right, b->left);
}
int isIdentical(Stack *a, Stack *b)
{
	// Since the number of nodes is already checked to be even,
	// program needs only one parameter
	while (!isEmpty(a))
	{
		// Checks if top value is equal then pop them to check next node
		if(peek(a) == peek(b))
		{
			pop(a);
			pop(b);
		}
		// If value is not same the nodes are not identical
		if(peek(a) != peek(b))
		{
			return 0;
		}
	}
	return 1;
}
void swapChildren(node *left , node *right, node *reflection)
{
	// Checks for end of trees
	if(left == NULL && right == NULL)
	{
		return;
	}
	// Creates new right child based on left child data
	if(left != NULL)
	{
		reflection->right = createnode(left->data);
	}
	// Creates new left child based on right child data
	if(right != NULL)
	{
		reflection->left = createnode(right->data);
	}
	// Recursive call to swap children of each parent
	swapChildren(left->left, left->right, reflection->right);
	swapChildren(right->left, right->right, reflection->left);
}
node *makeReflection(node *root)
{
	node *reflection;
	// Checks if root is valid
	if (root == NULL)
	{
		return NULL;
	}
	// Creates root
	reflection = createnode(root->data);
	swapChildren(root->left, root->right, reflection);
	return reflection;
}

int count_nodes(node *root)
{
	if (root == NULL)
	{
		return 0;
	}
	return 1 + count_nodes(root->left) + count_nodes(root->right);
}

void preorder_recursive(node *root, Stack *preorder)
{
	if (root == NULL)
	{
		return;
	}
	// Adds root data to stack
	push(preorder, root->data);
	preorder_recursive(root->left, preorder);
	preorder_recursive(root->right, preorder);
}0

void postorder_recursive(node *root, Stack *postorder)
{
	if (root == NULL)
	{
		return;
	}
	postorder_recursive(root->left, postorder);
	postorder_recursive(root->right, postorder);
	// Adds root data to stack
	push(postorder, root->data);
}
int kindredSpirits(node *a, node *b)
{
	int lengthA;
	int lengthB;
	int isKindred;
	Stack *preorderA;
	Stack *postorderA;
	Stack *preorderB;
	Stack *postorderB;
	if (a == NULL && b == NULL)
	{
		return 1;
	}
	// Makes sure amount of nodes is identical
	// If not there is no possible way for it to be
	// kindred
	lengthA = count_nodes(a);
	lengthB = count_nodes(b);
	if (lengthA != lengthB)
	{
		return 0;
	}
	// Creates blank stack
	postorderA = createStack(lengthA);
	// Fills blank stack
	postorder_recursive(a, postorderA);
	preorderA = createStack(lengthA);
	preorder_recursive(a, preorderA);
	preorderB = createStack(lengthB);
	preorder_recursive(b, preorderB);
	postorderB = createStack(lengthB);
	postorder_recursive(b, postorderB);
	// Checks if preorderA and postorderB are identical
	isKindred = isIdentical(preorderB, postorderA);
	// If identical, free stacks and return 1
	if(isKindred == 1)
	{
		destroyStack(postorderA);
		destroyStack(preorderA);
		destroyStack(preorderB);
		destroyStack(postorderB);
		return 1;
	}
	// If not identical, checks if postorderB
	// and preorderA are identical
	isKindred = isIdentical(postorderB, preorderA);
	// Free stacks
	destroyStack(postorderA);
	destroyStack(preorderA);
	destroyStack(preorderB);
	destroyStack(postorderB);
	return isKindred;
}
