#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1024

struct _list;
typedef struct _list* listPosition;
typedef struct _list {
	char grad[MAX];
	int brStanovnika;
	listPosition next;
}list;
                                              //     NE RADI!
struct _tree;
typedef struct _tree* treePosition;
typedef struct _tree {
	char drzava[MAX];
	listPosition gradovi;
	treePosition left;
	treePosition right;
}tree;

treePosition openFile(treePosition root);
treePosition insertInTree(char* imeDrzave, char* gradoviDatoteka, treePosition root);
treePosition createTreeElement(char* imeDrzave, char* gradoviDatoteka);
listPosition openCititesFile(char* gradoviDatoteka, listPosition head);
listPosition insertInList(listPosition temp, char* imeGrada, int brojStan);
listPosition createListElement(char* imeGrada, int brojStan);
void printInOrder(treePosition current);
void printCities(listPosition head);

int main()
{
	treePosition root = NULL;

	root = openFile(root);

	printInOrder(root);

	return EXIT_SUCCESS;
}

treePosition openFile(treePosition root)
{
	FILE* file = NULL;
	char buffer[MAX] = { 0 };
	char imeDrzave[MAX] = { 0 };
	char gradoviDatoteka[MAX] = { 0 };

	file = fopen("drzave.txt", "r");

	if (!file) {
		printf("Greska prilikom otvaranja datoteke!\n");
		return EXIT_FAILURE;
	}

	while (!feof(file))
	{
		fgets(buffer, MAX, file);
		if (sscanf(buffer, " %s %s", imeDrzave, gradoviDatoteka) == 2)
		{
			root = insertInTree(imeDrzave, gradoviDatoteka, root);
		}
	}

	fclose(file);

	return root;
}

treePosition insertInTree(char* imeDrzave, char* gradoviDatoteka, treePosition current)
{
	if (!current)
	{
		current = createTreeElement(imeDrzave, gradoviDatoteka);
	}
	else if (strcmp(imeDrzave, current->drzava) < 0)
	{
		current->left = insertInTree(imeDrzave, gradoviDatoteka, current->left);
	}
	else
	{
		current->right = insertInTree(imeDrzave, gradoviDatoteka, current->right);
	}

	return current;
}

treePosition createTreeElement(char* imeDrzave, char* gradoviDatoteka)
{
	treePosition novaDrzava = NULL;
	list head = { .grad = { 0 }, .brStanovnika = NULL, .next = NULL };

	novaDrzava = (treePosition)malloc(sizeof(tree));

	if (!novaDrzava)
	{
		perror("Greska prilikom alokacije memorije!\n");
		return NULL;
	}

	strcpy(novaDrzava->drzava, imeDrzave);
	novaDrzava->gradovi = NULL;
	novaDrzava->left = NULL;
	novaDrzava->right = NULL;

	novaDrzava->gradovi = openCititesFile(gradoviDatoteka, &head);    

	return novaDrzava;
}

listPosition openCititesFile(char* gradoviDatoteka, listPosition head)
{
	FILE* file = NULL;
	char buffer[MAX] = { 0 };
	char imeGrada[MAX] = { 0 };
	int brojStan;

	file = fopen(gradoviDatoteka, "r");

	if (!file) {
		printf("Greska prilikom otvaranja datoteke!\n");
		return EXIT_FAILURE;
	}

	while (!feof(file))
	{
		fgets(buffer, MAX, file);
		if (sscanf(buffer, " %s %d", imeGrada, &brojStan) == 2)
		{
			insertInList(head, imeGrada, brojStan);
		}
	}

	fclose(file);

	return head;
}

listPosition insertInList(listPosition temp, char* imeGrada, int brojStan)
{
	listPosition noviGrad = createListElement(imeGrada, brojStan);

	if (!noviGrad)
		return EXIT_FAILURE;

	while (temp->next != NULL && temp->next->brStanovnika < brojStan)
		temp = temp->next;

	if (temp->next != NULL && temp->next->brStanovnika == brojStan)
	{
		while (strcmp(imeGrada, temp->next->grad) > 0)
			temp = temp->next;
	}

	noviGrad->next = temp->next;
	temp->next = noviGrad;

	return noviGrad;
}

listPosition createListElement(char* imeGrada, int brojStan)
{
	listPosition noviGrad = NULL;

	noviGrad = (listPosition)malloc(sizeof(list));

	if (!noviGrad)
	{
		perror("Greska prilikom alokacije memorije!\n");
		return NULL;
	}

	strcpy(noviGrad->grad, imeGrada);
	noviGrad->brStanovnika = brojStan;
	noviGrad->next = NULL;

	return noviGrad;
}

void printInOrder(treePosition current)
{
	if (current)
	{
		printInOrder(current->left);
		printf("\n%s:\n", current->drzava);
		printCities(current->gradovi);
		printInOrder(current->right);
	}
}

void printCities(listPosition head)
{
	listPosition current = head->next;

	while (current)
	{
		printf("%s\t\t%d\n", current->grad, current->brStanovnika);
		current = current->next;
	}
}