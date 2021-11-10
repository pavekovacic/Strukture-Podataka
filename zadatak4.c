#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX 1024

struct _polinom;
typedef struct _polinom* position;

typedef struct _polinom {
	int koef;
	int eks;
	position next;
}polinom;

int otvoriDatoteku(position, position, char*);
int ucitajIzDatoteke(position, char*);
position unosNovogElementa(position, int, int);
void unesiSortirano(position, position);
int zbroji(position, position, position);
int pomnozi(position, position, position);
void ispis(position);

int main()
{
	polinom head1 = { .koef = 0, .eks = 0, .next = NULL };
	polinom head2 = { .koef = 0, .eks = 0, .next = NULL };
	polinom headZbr = { .koef = 0, .eks = 0, .next = NULL };
	polinom headUmn = { .koef = 0, .eks = 0, .next = NULL };

	char imeDatoteke[30] = { 0 };

	printf("Unesite ime datoteke: ");
	scanf(" %s", imeDatoteke);

	if (otvoriDatoteku(&head1, &head2, imeDatoteke))
		return -1;

	ispis(head1.next);
	ispis(head2.next);

	zbroji(&head1, &head2, &headZbr);
	printf("\nZbroj: ");
	ispis(headZbr.next);

	pomnozi(&head1, &head2, &headUmn);
	printf("\nUmnozak: ");
	ispis(headUmn.next);
	
	return 0;
}

int otvoriDatoteku(position head1, position head2, char* imeDatoteke)
{
	FILE* file = NULL;
	char buffer[MAX] = { 0 };

	file = fopen(imeDatoteke, "r");
	if (!file) {
		printf("Greska prilikom otvaranja datoteke!\n");
		return -1;
	}

	fgets(buffer, MAX, file);
	if (ucitajIzDatoteke(head1, buffer) != 0)
		return -1;

	fgets(buffer, MAX, file);
	if (ucitajIzDatoteke(head2, buffer) != 0)
		return -1;

	fclose(file);

	return 0;
}

int ucitajIzDatoteke(position head, char* buffer)
{
	char *temp = buffer;
	int koef = 0, eks = 0, n = 0;
	position element = NULL;

	while (strlen(temp) > 0) {
		if (sscanf(temp, "%d %d %n", &koef, &eks, &n) == 2) {
			element = unosNovogElementa(head, koef, eks);
			temp += n;
		}
		else {
			printf("Greska u datoteci!\n");
			return -1;
		}

		if (!element)
			return -1;
	}

	return 0;
}

position unosNovogElementa(position head, int koef, int eks)
{
	position el = NULL;
	el = (position)malloc(sizeof(polinom));

	if (el == NULL) {
		printf("Greska prilikom alokacije mamorije!");
		return -1;
	}

	el->koef = koef;
	el->eks = eks;
	el->next = NULL;

	unesiSortirano(head, el);

	return el;
}

void unesiSortirano(position p, position el)
{
	while (p->next != NULL && p->next->eks > el->eks)
		p = p->next;

	if (p->next == NULL || p->next->eks < el->eks) {
		el->next = p->next;
		p->next = el;
	}
	else {
		if (p->next->koef + el->koef)
			p->next->koef += el->koef;
		else {
			position izbrisi = NULL;
			izbrisi = p->next;
			p->next = izbrisi->next;
			free(izbrisi);
		}
		free(el);
	}
}

int zbroji(position p1, position p2, position zbr)
{
	position temp = NULL;

	while (p1 != NULL && p2 != NULL)
	{
		if (p1->eks == p2->eks){
			unosNovogElementa(zbr, p1->koef + p2->koef, p1->eks);
			p1 = p1->next;
			p2 = p2->next;
		}
		else if (p1->eks > p2->eks){
			unosNovogElementa(zbr, p1->koef, p1->eks);
			p1 = p1->next;
		}
		else{
			unosNovogElementa(zbr, p2->koef, p2->eks);
			p2 = p2->next;
		}
	}

	if (p1 == NULL){
		temp = p2;
	}
	else{
		temp = p1;
	}

	while (temp != NULL){
		unosNovogElementa(zbr, temp->koef, temp->eks);
		temp = temp->next;
	}
	free(temp);

	return 0;
}

int pomnozi(position p1, position p2, position umn)
{
	position pocetak = p2;

	while (p1 != NULL) {
		while (p2 != NULL) {
			unosNovogElementa(umn, p1->koef * p2->koef, p1->eks + p2->eks);
			p2 = p2->next;
		}
		p2 = pocetak;
		p1 = p1->next;
	}

	return 0;
}

void ispis(position p)
{
	while (p != NULL) {
		printf("%dx^%d", p->koef, p->eks);
		if (p->next != NULL && p->next->koef >= 0)
			printf("+");
		p = p->next;
	}
	puts("");
}