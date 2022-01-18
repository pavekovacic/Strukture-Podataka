#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1024
#define TABLE_SIZE 11

struct _tree;
typedef struct _tree* treePosition;
typedef struct _tree {
	char grad[MAX];
	int brStanovnika;
	treePosition left;
	treePosition right;
}tree;

struct _list;
typedef struct _list* listPosition;
typedef struct _list {
	char drzava[MAX];
	treePosition gradovi;
	listPosition next;
}list;

void createHashTable(list hashTable[]);
int openFile(list hashTable[]);
int hash(char* imeDrzave);
int insertInList(char* imeDrzave, char* gradoviDatoteka, listPosition temp);
listPosition createListElement(char* imeDrzave, char* gradoviDatoteka);
treePosition insertInTree(char* gradoviDatoteka, treePosition root);
treePosition insert(treePosition current, char* imeGrada, int brojStan);
treePosition createTreeElement(char* imeGrada, int brojStan);
void print(listPosition head);
void inorder(treePosition current);
int findCountry(list head[]);
void printCities(treePosition curr, int brojStan);

int main()
{
	list hashTable[TABLE_SIZE];
	
	createHashTable(&hashTable);

	openFile(&hashTable);

	for (int i = 0; i < TABLE_SIZE; i++)
		print(&hashTable[i]);

	findCountry(&hashTable);

	return EXIT_SUCCESS;
}

void createHashTable(list hashTable[])
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		hashTable[i].gradovi = NULL;
		hashTable[i].next = NULL;
		strcpy(hashTable[i].drzava, "");
	}
}

int openFile(list hashTable[])
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
			insertInList(imeDrzave, gradoviDatoteka, &hashTable[hash(imeDrzave)]);
		}
	}

	fclose(file);

	return EXIT_SUCCESS;
}

int hash(char* imeDrzave)
{
	int i, hashV = 0;

	for(i = 0; i < 5; i++)
		hashV += *imeDrzave++;

	return hashV % TABLE_SIZE;
}

int insertInList(char* imeDrzave, char* gradoviDatoteka, listPosition temp)
{
	listPosition novaDrzava = createListElement(imeDrzave, gradoviDatoteka);

	if (!novaDrzava)
		return EXIT_FAILURE;

	novaDrzava->gradovi = insertInTree(gradoviDatoteka, novaDrzava->gradovi);

	while (temp->next != NULL && strcmp(imeDrzave, temp->next->drzava) > 0)
		temp = temp->next;

	novaDrzava->next = temp->next;
	temp->next = novaDrzava;

	return EXIT_SUCCESS;
}

listPosition createListElement(char* imeDrzave, char* gradoviDatoteka)
{
	listPosition novaDrzava = NULL;

	novaDrzava = (listPosition)malloc(sizeof(list));

	if (!novaDrzava)
	{
		perror("Greska prilikom alokacije memorije!\n");
		return NULL;
	}

	strcpy(novaDrzava->drzava, imeDrzave);
	novaDrzava->gradovi = NULL;
	novaDrzava->next = NULL;

	return novaDrzava;
}

treePosition insertInTree(char* gradoviDatoteka, treePosition root)
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
			root = insert(root, imeGrada, brojStan);
		}
	}

	fclose(file);

	return root;
}

treePosition insert(treePosition current, char* imeGrada, int brojStan)
{
	if (!current)
	{
		current = createTreeElement(imeGrada, brojStan);
	}
	else if (brojStan < current->brStanovnika)
	{
		current->left = insert(current->left, imeGrada, brojStan);
	}
	else if (brojStan > current->brStanovnika)
	{
		current->right = insert(current->right, imeGrada, brojStan);
	}
	else if (strcmp(imeGrada, current->grad) < 0)
	{
		current->left = insert(current->left, imeGrada, brojStan);
	}
	else
	{
		current->right = insert(current->right, imeGrada, brojStan);
	}


	return current;
}

treePosition createTreeElement(char* imeGrada, int brojStan)
{
	treePosition noviGrad = NULL;

	noviGrad = (treePosition)malloc(sizeof(tree));

	if (!noviGrad)
	{
		perror("Greska prilikom alokacije memorije!\n");
		return NULL;
	}

	strcpy(noviGrad->grad, imeGrada);
	noviGrad->brStanovnika = brojStan;
	noviGrad->left = NULL;
	noviGrad->right = NULL;

	return noviGrad;
}

void print(listPosition head)
{
	listPosition current = head->next;

	while (current)
	{
		printf("\n%s:\n", current->drzava);
		inorder(current->gradovi);
		current = current->next;
	}
}

void inorder(treePosition curr)
{
	if (curr)
	{
		inorder(curr->left);
		printf("%s\t\t%d\n", curr->grad, curr->brStanovnika);
		inorder(curr->right);
	}
}

int findCountry(list hashTable[])
{
	listPosition current = NULL;
	char imeDrzave[MAX] = { 0 };
	int brojStan;

	printf("\nUnesi ime drzave: ");
	scanf(" %s", imeDrzave);

	printf("\nUnesi broj stanovnika: ");
	scanf(" %d", &brojStan);

	current = &hashTable[hash(imeDrzave)];

	while (current && strcmp(current->drzava, imeDrzave))
		current = current->next;

	if (current)
		printCities(current->gradovi, brojStan);
	else if (current == NULL)
		printf("\nDrzava '%s' nije pronadena!\n", imeDrzave);

	return EXIT_SUCCESS;
}

void printCities(treePosition curr, int brojStan)
{
	if (curr)
	{
		printCities(curr->left, brojStan);
		if (brojStan < curr->brStanovnika)
		{
			printf("%s\t\t%d\n", curr->grad, curr->brStanovnika);
		}
		printCities(curr->right, brojStan);
	}
}
