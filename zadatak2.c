#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct _osoba;
typedef struct _osoba* pozicija;

typedef struct _osoba {
    char ime[30];
    char prezime[30];
    int godinaRodenja;
    pozicija next;
} osoba;

void unesiPodatke(pozicija);
int unesi(pozicija);
int unosNaKrajListe(pozicija);
int ispisListe(pozicija);
pozicija pronadiPrezime(pozicija, char*);
int brisanjeIzListe(pozicija, char*);

int main()
{
    pozicija head = NULL;
    head = (pozicija)malloc(sizeof(osoba));
    head->next = NULL;

    int x, y = 0;
    char prezime[30];

    do {
        printf("Odaberi broj:\n1 - unos\n2 - ispis liste\n"
            "3 - pronadi po prezimenu\n4 - brisanje iz liste\n0 - kraj\n\n");
        scanf("%d", &x);

        switch (x)
        {
        case 1:
            do {
                printf("\nOdaberi broj:\n1 - unos na pocetak liste\n2 - unos na kraj liste\n\n");
                scanf("%d", &y);
                puts("");
                switch (y)
                {
                case 1:
                    unesi(head);
                    break;
                case 2:
                    unosNaKrajListe(head);
                    break;
                default:
                    printf("Pokusaj ponovo!\n");
                    y = 0;
                    break;
                }
            } while (y != 1 && y != 2);
            break;
        case 2:
            puts("");
            ispisListe(head->next);
            break;
        case 3:
            printf("\nUnesi prezime osobe koju zelis pronaci: ");
            scanf(" %s", prezime);
            if (pronadiPrezime(head->next, prezime))
                printf("\nPrezime pronadeno.\n");
            break;
        case 4:
            printf("\nUnesi prezime osobe koju zelis izbrisati: ");
            scanf(" %s", prezime);
            brisanjeIzListe(head, prezime);
            break;
        default:
            if (x != 0)
            {
                printf("\nKrivi unos.\n");
                break;
            }
        }
        puts("");
    } while (x != 0);

    return 0;
}

int unesi(pozicija p)
{
    pozicija q = NULL;
    q = (pozicija)malloc(sizeof(osoba));
    if (q == NULL)
        return -1;
    unesiPodatke(q);
    q->next = p->next;
    p->next = q;

    return 0;
}

int unosNaKrajListe(pozicija p)
{
    while (p->next != NULL)
        p = p->next;
    unesi(p);

    return 0;
}

int ispisListe(pozicija p)
{
    if (p == NULL)
    {
        printf("Nema elemeanta, lista je prazna!\n");
        return -1;
    }
    else
    {
        while (p != NULL)
        {
            printf("%s ", p->ime);
            printf("%s ", p->prezime);
            printf("%d\n", p->godinaRodenja);
            p = p->next;
        }
    }
    return 0;
}

pozicija pronadiPrezime(pozicija p, char* prezime)
{
    while (p != NULL && strcmp(p->prezime, prezime) != NULL)
        p = p->next;

    if (p == NULL)
        printf("Osoba s tim prezimenom nije upisana\n");

    return p;
}

int brisanjeIzListe(pozicija p, char* prezime)
{
    pozicija q = NULL;
    q = pronadiPrezime(p, prezime);

    while (p->next != q)
        p = p->next;
    if (q == NULL)
        return 0;

    p->next = q->next;
    free(q);
    printf("\nOsoba izbrisana iz liste!\n");

    return 0;
}

void unesiPodatke(pozicija q)
{
    printf("Ime: ");
    scanf(" %s", q->ime);
    printf("Prezime: ");
    scanf(" %s", q->prezime);
    printf("Godina rodenja: ");
    scanf("%d", &q->godinaRodenja);
}