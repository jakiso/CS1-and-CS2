// 11-2020 Code CS1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ListyFib.h"

ListyInt *create_list(void)
{
	// Allocate space for a new listyint
	ListyInt *newlist = malloc(sizeof(ListyInt));
	// Set values to start values
	newlist->length = 0;
	newlist->head = NULL;
	return newlist;
}

Node *createnode(int data)
{
	// Allocate space for a new node
	Node *newnode = malloc(sizeof(Node));
	newnode->digit = data;
	newnode->next = NULL;
	return newnode;
}

Node *head_insert(Node *head,int data)
{
	Node *newhead = createnode(data);
	newhead->next = head;
	return newhead;
}

Node *destroy_list(Node *head)
{
	if (head == NULL)
	{
		return NULL;
	}
	destroy_list(head->next);
	free(head);
	return NULL;
}

ListyInt *destroyListyInt(ListyInt *listy)
{
	if (listy == NULL)
	{
		return NULL;
	}
	destroy_list(listy->head);
	free(listy);
	return NULL;
}

ListyInt *listyAdd(ListyInt *p, ListyInt *q)
{
	ListyInt *temp;
	Node *ptemp;
	Node *qtemp;
	Node *lastnode;
	int addition = 0;
	int addten = 0;
	int i = 1;
	long long unsigned int plength;
	long long unsigned int qlength;
	// Check if pointers are NULL
	if (p == NULL || q == NULL)
	{
		return NULL;
	}
	// Create a new blank list
	temp = create_list();
	// Grab lengths of each list
	plength = p->length;
	qlength = q->length;
	// Set node pointers to head of given listyints
	ptemp = p->head;
	qtemp = q->head;
	// Set node pointer to point to new list head
	lastnode = temp->head;
	// Add the digits in the nodes
	addition += ptemp->digit;
	addition += qtemp->digit;
	// Make sure that addition is not bigger than ten
	// if so it will go to new node
	addten = addition / 10;
	addition = addition % 10;
	// Create the first head of temp
	temp->head = head_insert(temp->head, addition);
	// Add to length everytime there is new node
	temp->length += 1;
	// Set pointers to next digit
	ptemp = ptemp->next;
	qtemp = qtemp->next;
	lastnode = temp->head;
	if(addten != 0 && plength == 1 && qlength == 1)
	{
		lastnode->next = createnode(addten);
		temp->length += 1;
		addten--;
	}
	if (plength == 1 && qlength == 1)
	{
		return temp;
	}
	// Loop to the biggest length
	while (i < plength || i < qlength)
	{
		addition = 0;
		// Checks if temp variables are at the end of list
		if(i < plength)
		{
			addition += ptemp->digit;
		}
		if(i < qlength)
		{
			addition += qtemp->digit;
		}
		addition += addten;
		addten = addition / 10;
		addition = addition % 10;
		// Manual Tail insert
		lastnode->next = createnode(addition);
		temp->length += 1;
		lastnode = lastnode->next;
		// Makes sure that the next node will not be Null
		// Set pointers to next digit
		if(i < plength)
		{
			ptemp = ptemp->next;
		}
		if(i < qlength)
		{
			qtemp = qtemp->next;
		}
		// Increment the i till the biggest length
		i++;
	}
	if(addten != 0)
	{
		lastnode->next = createnode(addten);
		temp->length += 1;
		addten--;
	}
	return temp;
}

ListyInt *stringToListyInt(char *str)
{
	ListyInt *temp;
	int slength;
	char parse[1];
	int i;
	if (str == NULL)
	{
		return NULL;
	}
	// Create a empty list
	temp = create_list();
	// Get the string length
	slength = strlen(str);
	// If empty string, set the digit to 0
	if(slength == 0)
	{
		temp->head = head_insert(temp->head,0);
		temp->length += 1;
		return temp;
	}
	// Iterates through the string
	for(i = 0; i < slength ; i++)
	{
		parse[0] = str[i];
		// Inserts to the front of the list
		// Set a integer to a char
		temp->head = head_insert(temp->head, atoi(parse));
		temp->length +=1;
	}
	return temp;
}

char *listyIntToString(ListyInt *listy)
{
	Node *temp;
	char *string;
	char *nonreversed;
	long long unsigned int length;
	long long unsigned int i = 0;
	long long unsigned int j = 0;
	// Checks if listy is null
	if (listy == NULL)
	{
		return NULL;
	}
	// Points temp to listy head
	temp = listy->head;
	// Grab length of listy
	length = listy->length;
	// Allocates length of string plus 1 to account for end null
	string = (char*)malloc(length + 1);
	nonreversed = (char*)malloc(length + 1);
	// Sets digit to char and put it into a char array
	while (i < length)
	{
		nonreversed[i] = temp->digit + '0';
		i++;
		// Sets temp to next node
		temp = temp->next;
	}
	// To account for the extra plus 1 when doing for loop
	i = length - 1;
	// Reverses string
	for (j = 0; j < length; j++)
	{
		string[j] = nonreversed[i];
		i--;
	}
	free(nonreversed);
	nonreversed = NULL;
	// Sets end of string to null
	string[length] = '\0';
	return string;
}
// Count K (number of digits)
int Countplaces(unsigned int n)
{
	int counter = 0;
	while(n > 10)
	{
		n /= 10;
		counter ++;
	}
	return counter;
}
ListyInt *uintToListyInt(unsigned int n)
{
	// Create a empty list
	ListyInt *temp = create_list();
	int i;
	int counter;
	long long unsigned int reverse = 0;
	unsigned int modulus;
	int length;
	// Checks of integer is a simple 0 to prevent extra work
	if (n == 0)
	{
		temp->head = head_insert(temp->head, 0);
		temp->length += 1;
		return temp;
	}
	// Count number of digits
	counter = Countplaces(n);
	// Create a reverse integer
	while(n > 0)
	{
		modulus = n % 10;
		reverse = reverse * 10 + modulus;
		n /= 10;
	}
	// Put reverse integer to listy int by each integer
	for(i = 0; i <= counter; i++)
	{
		temp->head = head_insert(temp->head, reverse % 10);
		temp->length +=1;
		reverse /= 10;
	}
	return temp;
}

unsigned int *listyIntToUint(ListyInt *listy)
{
	Node *temp;
	long long unsigned int length;
	long long unsigned int i = 0;
	long long unsigned int n = 1;
	long long unsigned int j = 1;
	unsigned int conversion = 0;
	// Allocate memory for a unsigned int pointer
	unsigned int *ptr = malloc(sizeof(unsigned int));
	long long unsigned int listunit = 0;
	// Checks if listy is valid
	if(listy == NULL)
	{
		free(ptr);
		return NULL;
	}
	// Grabs length
	length = listy->length;
	// Points temp to point to head
	temp = listy->head;
	while (i < length)
	{
		j = 1;
		if(i > 0)
		{
			// Calculates the place of number
			for(n = 1; n <= i; n++)
			{
				j *= 10;
			}
		}
		// Add each number place
		listunit += (temp->digit * j);
		i++;
		// Iterate to the next node
		temp = temp->next;
	}
	// If listunit is greater than maz deallocate pointer and return null
	if(listunit > UINT_MAX)
	{
		free(ptr);
		return NULL;
	}
	// Make list unit to a unsigned int
	conversion = listunit;
	*ptr = conversion;
	return ptr;
}

void plusPlus(ListyInt *listy)
{
	Node *temp;
	if(listy == NULL)
	{
		return;
	}
	// Point to first node and add 1 to digit
	temp = listy->head;
	temp->digit += 1;
}

ListyInt *fib(unsigned int n)
{
	ListyInt *addPrev;
	ListyInt *addCurrent;
	ListyInt *result;
	unsigned int i = 2;
	// Checks if number doesn't need to be added
	if(n < 2)
	{
		result = uintToListyInt(n);
		return result;
	}
	// Sets first numbers
	addPrev = uintToListyInt(0);
	addCurrent = uintToListyInt(1);
	for(i = 2; i <= n; i++)
	{
		// Adds the last two numbers on list
		result = listyAdd(addCurrent, addPrev);
		// Updates new last numbers
		addPrev = addCurrent;
		addCurrent = result;
	}
	destroyListyInt(addPrev);
	return result;
}
