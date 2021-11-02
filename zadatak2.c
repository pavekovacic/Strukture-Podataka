#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct _osoba;
typedef struct _osoba* pozicija;

typedef struct _osoba {
    char ime[50];
    char prezime[50];
    int godinaRodenja;
    pozicija next;
} osoba;

int umetni(pozicija);
int ispisListe(pozicija);
int unosNaKrajListe(pozicija);
int pronadiPoPrezimenu(pozicija);
int brisanjeIzListe(pozicija);
int main()
{
    osoba head;
    head.next = NULL;

    int x;

    do {
        printf("Odaberi broj:\n1 - unos na pocetak liste\n2 - ispis liste\n"
            "3 - unos na kraj liste\n4 - pronadi po prezimenu\n5 - brisanje iz liste\n0 - kraj\n");
        scanf("%d", &x);

        switch (x)
        {
            case 1:
            {
                umetni(&head);
                break;
            }
            case 2:
            {
                ispisListe(head.next);
                break;
            }
            case 3:
            {
                unosNaKrajListe(&head);
                break;
            }
            case 4:
            {
                pronadiPoPrezimenu(head.next);
                break;
            }   
            case 5:
            {
                brisanjeIzListe(&head);
                break;
            }
            default:
            {
                if (x != 0)
                {
                    printf("Krivi unos.\n");
                    break;
                }
            }
        }
        puts("");
    } while (x != 0);

    return 0;
}

int umetni(pozicija p)
{
    pozicija q = NULL;
    q = (pozicija)malloc(sizeof(osoba));

    printf("Ime: ");
    scanf(" %s", q->ime);

    printf("\nPrezime: ");
    scanf(" %s", q->prezime);

    printf("\nGodina rodenja: ");
    scanf("%d", q->godinaRodenja);

    q->next = p->next;
    p->next = q;

    return 0;
}
int ispisListe(pozicija p)
{
    while (p != NULL)
    {
        printf("%s %s, %d\n", p->ime, p->prezime, p->godinaRodenja);
        p = p->next;
    }

    return 0;
}
int unosNaKrajListe(pozicija p)
{
    while (p->next != NULL)
    {
        p = p->next;
    }

    pozicija q = NULL;
    q = (pozicija)malloc(sizeof(osoba));

    printf("Ime: ");
    scanf(" %s", q->ime);

    printf("\nPrezime: ");
    scanf(" %s", q->prezime);

    printf("\nGodina rodenja: ");
    scanf("%d", q->godinaRodenja);

    q->next = p->next;
    p->next = q;
    return 0;
}
int pronadiPoPrezimenu(pozicija p)
{
    char prez[80];
    printf("Unesi prezime: ");
    scanf(" %s", &prez);

    while (p != NULL && strcmp(prez, p->prezime) != 0)
    {
        p = p->next;
    }

    if (p == NULL)
        printf("Nema trazenog prezimena.\n");
    else
        printf("Adresa trazene osobe: %p\n", p);
    return 0;
}
int brisanjeIzListe(pozicija p)
{
    pozicija prethodni = NULL;
    char prez[80];
    printf("Unesi prezime osobe koju zelis izbrisati: ");
    scanf(" %s", &prez);
    while (p->next != NULL && strcmp(prez, p->prezime) != 0)
    {
        prethodni = p;
        p = p->next;
    }
    if (prethodni != NULL && strcmp(prez, p->prezime) == 0)
    {
        p = prethodni->next;
        prethodni->next = p->next;
    }
    return 0;
}