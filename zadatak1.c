#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 1024

typedef struct _student{
	char ime[MAX];
	char prezime[MAX];
	int bodovi;
}student;

int brojStudenata();
int unosStudenata(student*, int);
int maxBrojBodova(student*, int);
int ispisStudenata(student*, int, int);

int main()
{
	int br_stud = 0, max_br_bodova = 0;
	student* studenti;

	br_stud = brojStudenata();

	studenti = (student*)malloc(br_stud * sizeof(student));

	unosStudenata(studenti, br_stud);

	max_br_bodova = maxBrojBodova(studenti, br_stud);

	ispisStudenata(studenti, br_stud, max_br_bodova);

	return 0;
}

int brojStudenata()
{
	int br_stud = 0;
	char buf[MAX];
	FILE* file;
	
	file = fopen("studenti.txt", "r");
	if (file == NULL)
		return -1;

	while (fgets(buf, MAX, file))
		br_stud++;

	fclose(file);

	return br_stud;
}

int unosStudenata(student* studenti, int br_stud)
{
	int i;
	FILE* file;

	file = fopen("studenti.txt", "r");
	if (file == NULL)
		return -1;

	for (i = 0; i < br_stud; i++)
		fscanf(file, "%s %s %d", studenti[i].ime, studenti[i].prezime, &(studenti[i].bodovi));

	fclose(file);

	return 0;
}

int maxBrojBodova(student* studenti, int br_stud)
{
	int i, max_br_bodova = 0;

	for (i = 0; i < br_stud; i++)
		if (studenti[i].bodovi > max_br_bodova)
			max_br_bodova = studenti[i].bodovi;

	return max_br_bodova;
}

int ispisStudenata(student* studenti, int br_stud, int max_br_bodova)
{
	int i;

	printf("IME\t\tPREZIME\t\tAPSOLUTNI BROJ BODOVA\t\tRELATIVNI BROJ BODOVA\n");
	for (i = 0; i < br_stud; i++)
	{
		double rel_br_bodova = (double)studenti[i].bodovi / max_br_bodova * 100;
		printf("%-15s %-15s %-31d %.2lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, rel_br_bodova);
	}
	
	return 0;
}
