#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX 1024

struct _osoba;
typedef struct _osoba* pozicija;

typedef struct _osoba{
    char ime[MAX];
    char prezime[MAX];
    int godinaRodenja;
    pozicija next;
} osoba;

int unosNaPocetakListe(pozicija);
int ispisListe(pozicija);
int unosNaKrajListe(pozicija);
int pronadiPoPrezimenu(pozicija);
int brisanjeIzListe(pozicija);
int main()
{
    osoba head;
    head.next == NULL;
    char c;

    do {
        printf("Odaberi slovo:\na - unos na pocetak liste\nb - ispis liste\n"
            "c - unos na kraj liste\nd - pronadi po prezimenu\ne - brisanje iz liste\nk - kraj");
        scanf(" %c", &c);
        puts("");

        switch (c)
        {
            case 'a':
            {
                unosNaPocetakListe(&head);
                break;
            }
            case 'b':
            {
                ispisListe(head.next);
                break;
            }
            case 'c':
            {
                unosNaKrajListe(&head);
                break;
            }
            case 'd':
            {
                pronadiPoPrezimenu(head.next);
                break;
            }
            case 'e':
            {
                brisanjeIzListe(&head);
                break;
            }
            default:
            {
                if (c != 'k')
                {
                    printf("Krivi unos.\n");
                    break;
                }
            }
        }
        puts("");
    } while (c != 'k');

    return 0;
}

int unosNaPocetakListe(pozicija p)
{
    pozicija q = NULL;
    q = (pozicija)malloc(sizeof(osoba));

    printf("Ime: ");
    scanf(" %s", q->ime);

    printf("\nPrezime: ");
    scanf(" %s", q->prezime);

    printf("\nGodina roðenja: ");
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

    printf("\nGodina roðenja: ");
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