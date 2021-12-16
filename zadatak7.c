#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 50

struct _directory;
	typedef struct _directory* position;
	typedef struct _directory {
		char name[MAX];
		position sibling;
		position child;
	}Directory;

	struct _stack;
	typedef struct _stack* stackPosition;
	typedef struct _stack {
		position directory;
		stackPosition next;
	}Stack;

	int push(position current, stackPosition head);
	position createStackElement(position current);
	void path(position current, stackPosition stackCurrent);
	int cmd(position current, stackPosition head);
	position makeDirectory(position current, char* directoryName);
	position createDirectoryElement(char* directoryName);
	position changeDirectory(position current, stackPosition head, char* directoryName);
	position pop(stackPosition head);


	int main()
	{
		Directory root = { .name = "C:", .sibling = NULL, .child = NULL };
		Stack head = { .directory = NULL, .next = NULL };

		if (push(&root, &head))
			return EXIT_FAILURE; 

		cmd(&root, &head);

		return EXIT_SUCCESS;
	}

	int push(position current, stackPosition head)
	{
		stackPosition newElement = createStackElement(current);
		stackPosition temp = head;

		if (!newElement)
			return EXIT_FAILURE;

		while (temp->next != NULL)
			temp = temp->next;

		newElement->next = temp->next;
		temp->next = newElement;

		return EXIT_SUCCESS;
	}

	position createStackElement(position current)
	{
		stackPosition newElement = NULL;

		newElement = (stackPosition)malloc(sizeof(Stack));
		if (!newElement) {
			perror("Greska prilikom alokacije memorije!\n");
			return NULL;
		}

		newElement->directory = current;

		return newElement;
	}

	void path(position current, stackPosition head)
	{
		stackPosition stackCurrent = head->next;
		
		printf("%s", stackCurrent->directory->name);

		while (stackCurrent->directory->name != current){
			stackCurrent = stackCurrent->next;
			printf("\\%s", stackCurrent->directory->name);
		}

		printf(">");
	}
	
	int cmd(position current, stackPosition head)
	{
		char buffer[MAX] = { 0 };
		char command[10] = { 0 };
		char directoryName[MAX] = { 0 };

		do {
			path(current, head);
	
			fgets(buffer, MAX, stdin);
			sscanf(buffer, "%s %s", command, directoryName);

			if (!strcmp(command, "md"))
			{
				current = makeDirectory(current, directoryName);
			}
			else if (!strcmp(command, "cd"))
			{
				current = changeDirectory(current, head, directoryName);
			}
			else if (!strcmp(command, "cd.."))
			{
				current = pop(head);
			}
			else if (!strcmp(command, "dir"))
			{
				printDirectory(current);
			}
			else if (!strcmp(command, "exit"))
			{
				return EXIT_SUCCESS;
			}
			else
			{
				printf("Komanda '%s' ne postoji.\n", command);
			}
		} while (strcmp(command, "exit"));
	}

	position makeDirectory(position current, char* directoryName)
	{
		position newDirEl = NULL;
		position temp = NULL;

		newDirEl = createDirectoryElement(directoryName);

		if (!newDirEl)
			return EXIT_FAILURE;

		if (!current->child) 
		{
			current->child = newDirEl;
		}
		else 
		{
			temp = current->child;

			while (temp->sibling)
				temp = temp->sibling;

			temp->sibling = newDirEl;
		}

		return current;
	}

	position createDirectoryElement(char* directoryName)
	{
		position newDirEl = NULL;

		newDirEl = (position)malloc(sizeof(Directory));
		if (!newDirEl) {
			perror("Greska prilikom alokacije memorije!\n");
			return NULL;
		}

		strcpy(newDirEl->name, directoryName);

		newDirEl->sibling = NULL;
		newDirEl->child = NULL;

		return newDirEl;
	}

	position changeDirectory(position current, stackPosition head, char* directoryName)
	{
		position temp = NULL;

		if (!current->child)
		{
			printf("Direktorij je prazan.\n");
			return current;
		}
		else
		{
			temp = current->child;

			while (temp)
			{
				if (!strcmp(temp->name, directoryName))
				{
					push(temp, head);
					return temp;
				}
				temp = temp->sibling;
			}
			printf("Sistem ne moze pronaci put do tog direktorija.\n");
		}

		return current;
	}

	position pop(stackPosition head)
	{
		stackPosition temp = head->next;
		stackPosition prev = NULL;
		position dir = temp->directory;

		if (!temp->next)
			return dir;

		while (temp->next)
		{
			prev = temp;
			temp = temp->next;
		}

		dir = prev->directory;
		prev->next = temp->next;
		free(temp);

		return dir;
	}

	int printDirectory(position current)
	{
		if (!current->child)
		{
			printf("Direktorij je prazan.\n");
		}
		else
		{
			current = current->child;

			while (current)
			{
				printf("%s\n", current->name);
				current = current->sibling;
			}
		}

		return EXIT_SUCCESS;
	}