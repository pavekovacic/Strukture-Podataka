#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MIN 11
#define MAX 89

struct _tree;
typedef struct _tree* position;
typedef struct _tree {
	int element;
	position left;
	position right;
}tree;

struct _list;
typedef struct _list* listPosition;
typedef struct _list {
	int element;
	listPosition next;
}list;

position insert(position current, int el);
position createTreeElement(int el);
int inorderInsertInList(position current, listPosition head);
int insertInList(int el, listPosition current);
position createListElement(int el);
int replace(position current);
int printInFile(listPosition current);

int main()
{
	position root = NULL;
	list head = { .element = 0, .next = NULL };
	int array[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	int i, n;
	srand((unsigned)time(NULL));

	do
	{
		printf("\nOdaberi broj:\n"
			"1 - Unos unaprijed definiranih brojva\n"
			"2 - Unos nasumicno generiranih brojeva\n\n"); 
		scanf(" %d", &n);

		switch (n)
		{
		case 1:
			for (i = 0; i < 10; i++) 
				root = insert(root, array[i]);
			break;
		case 2:
			for (i = 0; i < 10; i++) 
				root = insert(root, rand() % (MAX - MIN + 1) + MIN);
			break;
		default:
			printf("\nKrivi odabir. Pokusajte ponovo!\n");
			break;
		}
	} while (n != 1 && n != 2);

	inorderInsertInList(root, &head);
	replace(root);
	inorderInsertInList(root, &head);
	printInFile(&head);

	return EXIT_SUCCESS;
}

position insert(position current, int el)
{
	if (!current)
		current = createTreeElement(el);
	else if (el >= current->element)
		current->left = insert(current->left, el);
	else //if (el < current->element)
		current->right = insert(current->right, el);

	return current;
}

position createTreeElement(int el)
{
	position newElement = NULL;

	newElement = (position)malloc(sizeof(tree));
	if (!newElement) {
		perror("Greska prilikom alokacije memorije!\n");
		return NULL;
	}

	newElement->element = el;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

int inorderInsertInList(position current, listPosition head)
{
	if (current)
	{
		inorderInsertInList(current->left, head);
		if (insertInList(current->element, head))
			return EXIT_FAILURE;
		inorderInsertInList(current->right, head);
	}

	return EXIT_SUCCESS;
}

int insertInList(int el, listPosition current)
{
	listPosition newElement = createListElement(el);

	if (!newElement)
		return EXIT_FAILURE;
	
	while (current->next)
		current = current->next;

	newElement->next = current->next;
	current->next = newElement;

	return EXIT_SUCCESS;
}

position createListElement(int el)
{
	listPosition newElement = NULL;
		
	newElement = (listPosition)malloc(sizeof(list));

	if (!newElement) {
		perror("Greska prilikom alokacije memorije!\n");
		return NULL;
	}

	newElement->element = el;

	return newElement;
}

int replace(position current)
{
	int el;

	if (!current)
		return NULL;
	
	el = current->element;
	current->element = replace(current->left) + replace(current->right);
	
	return el + current->element;
}

int printInFile(listPosition current)
{
	FILE* file = NULL;
	char fileName[30] = { 0 };

	printf("\nUnesite ime datoteke: ");
	scanf(" %s", fileName);

	file = fopen(fileName, "w");

	if (!file) {
		printf("Greska prilikom otvaranja datoteke!\n");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			current = current->next;
			fprintf(file, "%5d", current->element);
		}
		fprintf(file, "\n");
	}

	fclose(file);

	return EXIT_SUCCESS;
}