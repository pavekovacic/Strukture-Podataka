#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct _stackElement;
typedef struct _stackElement* position;
typedef struct _stackElement{
	double number;
	position next;
}stackElement;

int insertFileName(char* fileName);
position createStackElement(double number);
int insertAfter(position p, position newElement);
int push(position head, double number);
int deleteAfter(position head);
int pop(double* number, position head);
int performOperation(position head, char operation);
int calculatePostFixFromFile(double* result, char* fileName);

int main()
{
	char fileName[30];
	double result = 0;

	insertFileName(fileName);

	if (calculatePostFixFromFile(&result, fileName) == 0)
		printf("Rezultat je: %.2lf\n", result);

	return 0;
}

int insertFileName(char* fileName)
{
	printf("Unesi ime datoteke: ");
	scanf(" %s", fileName);

	return 0;
}

position createStackElement(double number)
{
	position newElement = NULL;

	newElement = (position)malloc(sizeof(stackElement));
	if (!newElement) {
		perror("Greska prilikom alokacije memorije!\n");
		return NULL;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}

int insertAfter(position p, position newElement)
{
	newElement->next = p->next;
	p->next = newElement;

	return 0;
}

int push(position head, double number)
{
	position newElement = NULL;

	newElement = createStackElement(number);
	if (!newElement)
		return -1;

	insertAfter(head, newElement);

	return 0;
}

int deleteAfter(position head)
{
	position temp = head->next;

	if (!temp)
		return 0;

	head->next = temp->next;

	free(temp);

	return 0;
}

int pop(double* number, position head)
{
	position first = head->next;

	if (!first)
	{
		printf("Greska!\n");
		return -1;
	}

	*number = first->number;

	deleteAfter(head);

	return 0;
}

int performOperation(position head, char operation)
{
	double operand1 = 0;
	double operand2 = 0;
	double result = 0;

	if(pop(&operand2, head))
		return -1;

	if(pop(&operand1, head))
		return -1;

	switch (operation)
	{
		case '+':
			result = operand1 + operand2;
			break;
		case '-':
			result = operand1 - operand2;
			break;
		case '*':
			result = operand1 * operand2;
			break;
		case '/':
			if (operand2 == 0){
				printf("Ne mozemo dijeliti s 0!\n");
				return -1;
			}
			result = operand1 / operand2;
			break;
		default:
			printf("Operacija nije podrzana!\n");
			return -1;
	}

	if(push(head, result))
		return -1;

	return 0;
}

int calculatePostFixFromFile(double* result, char* fileName)
{
	FILE* file = NULL;
	int fileLength = 0;
	int numBytes = 0;
	int status = 0;
	double number = 0;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	char operation = 0;
	stackElement head = { .number = 0, .next = NULL };

	if((file = fopen(fileName, "rb")) == NULL)
	{
		printf("Greska prilikom otvaranja datoteke!\n");
		return -1;
	}

	fseek(file, 0, SEEK_END);
	fileLength = ftell(file);

	buffer = (char*)calloc(fileLength + 1, sizeof(char));
	if (!buffer)
	{
		printf("Greska prilikom alokacije memorije!\n");
		return -1;
	}

	rewind(file);
	fread(buffer, sizeof(char), fileLength, file);
	printf("|%s|\n", buffer);
	fclose(file);

	currentBuffer = buffer;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
		if (status == 1)
		{
			push(&head, number);
			currentBuffer += numBytes;
		}
		else
		{
			sscanf(currentBuffer, " %c %n", &operation, &numBytes);
			status = performOperation(&head, operation);
			if (status != 0)
			{
				free(buffer);
				while (head.next != NULL)
					deleteAfter(&head);

				return -1;
			}
			currentBuffer += numBytes;
		}
	}

	free(buffer);

	if(pop(result, &head)){
		while (head.next != NULL)
			deleteAfter(&head);
		return -1;
	}

	if (head.next != NULL){
		printf("Greska!\n");
		return -1;
	}

	return 0;
}