#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>

/*
    gracz'o' na planszy 0
    gracz 'x' na planszy 1
    puste pole na planszy 2
*/

typedef struct elementy_gry
{
    int rozmiar_planszy;
    int ile_znakow;//ile znakow w linii trzeba miec aby wygrac;
    int czyj_ruch;
    GtkWidget *znak;
    int plansza[10][10];
    GtkWidget *gra[10][10];

}Dane;

typedef struct pomocnicza_do_czasu
{
    long long int sekundy;
    GtkWidget *label_czas2;
};

struct elementy_ruchu
{
    struct elementy_gry G;
    int x;
    int y;
};

void przygotuj_plansze(Dane *G);
bool wykonaj_ruch(int x, int y, Dane *G);//czyj_ruch jest jednoznaczne z reprezentacja znaku gracza na planszy
bool wiersze(int x, int y, Dane *G);
bool kolumny(int x, int y, Dane *G);
bool skosy(int x, int y, Dane *G);
bool wygrana(int x, int y, char *opcja, Dane *G);
bool doloz(int x, int y, int znak, Dane *G);//znak w postaci 0/1
bool zabierz(int x, int y, int znak, Dane *G);
void stan_gry(Dane *G);
void wyswietl_czas(struct pomocnicza_do_czasu *Czas);

