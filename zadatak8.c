#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

struct _tree;
typedef struct _tree* position;
typedef struct _tree {
	int element;
	position left;
	position right;
}tree;

position insertElement(position current, int el);
position createTreeElement(int el);
void inorder(position current);
void preorder(position current);
void postorder(position current);
void levelOrder(position current);
void printLevel(position current, int level);
int depth(position current);
position deleteElement(position current, int el);
position findMin(position current);
position findElement(position current, int el);

int main() 
{
	position root = NULL, current = NULL;
	int n, el;

	do {
		printf("\nOdaberi broj:\n"
			"1 - Unos novog elementa\n"
			"2 - Inorder ispis\n"
			"3 - Preorder ispis\n"
			"4 - Postorder ispis\n"
			"5 - Level order ispis\n"
			"6 - Brisanje elementa\n"
			"7 - Pronadi element\n"
			"8 - Izlaz\n\n");
		scanf(" %d", &n);
		puts("");

		switch (n)
		{
		case 1:
			printf("Novi element: ");
			scanf(" %d", &el);
			if (root == NULL)
			{
				root = insertElement(root, el);
				if (!root)
					return EXIT_FAILURE;
			}
			else
			{
				current = insertElement(root, el);
				if (!current)
					return EXIT_FAILURE;
			}
			break;
		case 2:
			inorder(root);
			break;
		case 3:
			preorder(root);
			break;
		case 4:
			postorder(root);
			break;
		case 5:
			levelOrder(root);
			break;
		case 6:
			printf("Element koji zelite izbrisat: ");
			scanf("%d", &el);
			current = deleteElement(root, el);
			break;
		case 7:
			printf("Element koji zelite pronaci: ");
			scanf("%d", &el);
			current = findElement(root, el);
			if (!current)
				printf("\nElement nije pronaden.\n");
			else
				printf("\nElement je pronaden.\n");
			break;
		case 8:
			break;
		default:
			printf("Krivi odabir. Pokusajte ponovo!\n");
			break;
		}
	} while (n != 8);

	return EXIT_SUCCESS;
}

position insertElement(position current, int el)
{
	if (!current)
		current = createTreeElement(el);
	else if (el < current->element)
		current->left = insertElement(current->left, el);
	else if (el > current->element)
		current->right = insertElement(current->right, el);
	else
		printf("\nElement je vec upisan.\n");

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

void inorder(position current)
{
	if (current)
	{
		inorder(current->left);
		printf("%d\n", current->element);
		inorder(current->right);
	}
}

void preorder(position current)
{
	if (current)
	{
		printf("%d\n", current->element);
		preorder(current->left);
		preorder(current->right);
	}
}

void postorder(position current)
{
	if (current)
	{
		postorder(current->left);
		postorder(current->right);
		printf("%d\n", current->element);
	}
}

void levelOrder(position current)
{
	int d = depth(current);

	for (int i = 0; i <= d; i++)
	{
		printLevel(current, i);
		printf("\n");
	}
}

void printLevel(position current, int level)
{
	if (!current)
		return;
	else if (level == 0)
		printf("%d ", current->element);
	else if (level > 0)
	{
		printLevel(current->left, level - 1);
		printLevel(current->right, level - 1);
	}
}

int depth(position current)
{
	if (!current)
		return -1;
	else
	{
		int leftDepth = depth(current->left);
		int rightDepth = depth(current->right);

		if (leftDepth > rightDepth)
			return (leftDepth + 1);
		else
			return (rightDepth + 1);
	}
}

position deleteElement(position current, int el)
{
	position temp = NULL;

	if (!current)
	{
		printf("\nElement koji zelite izbrisati nije pronaden!\n");
		return current;
	}
	else if(el < current->element)
	{
		current->left = deleteElement(current->left, el);
	}
	else if (el > current->element)
	{
		current->right = deleteElement(current->right, el);
	}
	else
	{
		if (current->left && current->right)
		{
			temp = findMin(current->right);
			current->element = temp->element;
			current->right = deleteElement(current->right, current->element);
		}
		else
		{
			temp = current;
			if (!current->left)
				current = current->right;
			else
				current = current->left;
			free(temp);
		}
	}

	return current;
}

position findMin(position current)
{
	while (current->left)
		current = current->left;

	return current;
}

position findElement(position current, int el)
{
	if (!current)
		return current;
	else if (el < current->element)
			return findElement(current->left, el);
	else if(el > current->element)
		return findElement(current->right, el);

	return current;
}