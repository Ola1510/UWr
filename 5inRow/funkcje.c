#include "funkcje.h"

void przygotuj_plansze(Dane *G)
{
    int n=G->rozmiar_planszy;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            G->plansza[i][j]=2;
        }
    }
}

bool wykonaj_ruch(int x, int y, Dane *G)
{
    int znak=G->czyj_ruch;
    if(x==G->rozmiar_planszy-1)
    {
        if(G->plansza[x][y]==znak)
        {
            zabierz(x,y,znak,G);
            return wygrana(x,y,"zabierz",G);
        }
        else if(G->plansza[x][y]==2)
        {
            doloz(x,y,znak,G);
            return wygrana(x,y,"doloz",G);
        }
        else
        {
            GtkWidget *info=gtk_window_new(GTK_WINDOW_TOPLEVEL);
            gtk_window_set_default_size(GTK_WINDOW(info),300,150);
            gtk_window_set_title(GTK_WINDOW(info),"Niedozwolony ruch");
            gtk_window_set_position(GTK_WINDOW(info), GTK_WIN_POS_CENTER);
            gtk_container_set_border_width(GTK_CONTAINER(info), 0);
            g_signal_connect(G_OBJECT(info),"destroy", G_CALLBACK(gtk_window_close), info);
            GtkLabel *komunikat;
            komunikat=gtk_label_new("W tym miejscu znajduje się znak przeciwnika!");
            gtk_container_add(GTK_CONTAINER(info),komunikat);
            gtk_widget_show_all(info);
            G->czyj_ruch=(G->czyj_ruch+1)%2;//w main po zakonczeniu tej funkcji ruch dostaje przeciwnik a chcemy zeby po zlym klikneciu gracz mial szanse wybrac poprawne miejsce
            return false;
        }
    }
    else if(G->plansza[x+1][y]!=2)
    {
        if(G->plansza[x][y]==2)
        {
            doloz(x,y,znak,G);
            stan_gry(G);
            return wygrana(x,y,"doloz",G);
        }
        else
        {
            GtkWidget *info=gtk_window_new(GTK_WINDOW_TOPLEVEL);
            gtk_window_set_default_size(GTK_WINDOW(info),300,150);
            gtk_window_set_title(GTK_WINDOW(info),"Niedozwolony ruch");
            gtk_window_set_position(GTK_WINDOW(info), GTK_WIN_POS_CENTER);
            gtk_container_set_border_width(GTK_CONTAINER(info), 0);
            g_signal_connect(G_OBJECT(info),"destroy", G_CALLBACK(gtk_window_close), info);
            GtkLabel *komunikat;
            komunikat=gtk_label_new("Nie mozna postawić tu znaku, ruch niegodny z zasadami gry!");
            gtk_container_add(GTK_CONTAINER(info),komunikat);
            gtk_widget_show_all(info);
            G->czyj_ruch=(G->czyj_ruch+1)%2;//w main po zakonczeniu tej funkcji ruch dostaje przeciwnik a chcemy zeby po zlym klikneciu gracz mial szanse wybrac poprawne miejsce
            stan_gry(G);
            return false;
        }
    }
    else
    {
        //printf("mysli ze to nie jest dol planszy\n");
        GtkWidget *info=gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(info),300,150);
        gtk_window_set_title(GTK_WINDOW(info),"Niedozwolony ruch");
        gtk_window_set_position(GTK_WINDOW(info), GTK_WIN_POS_CENTER);
        gtk_container_set_border_width(GTK_CONTAINER(info), 0);
        g_signal_connect(G_OBJECT(info),"destroy", G_CALLBACK(gtk_window_close), info);
        GtkLabel *komunikat;
        komunikat=gtk_label_new("W tym miejscu nie mozna postawic znaku!");
        gtk_container_add(GTK_CONTAINER(info),komunikat);
        gtk_widget_show_all(info);
        G->czyj_ruch=(G->czyj_ruch+1)%2;
        stan_gry(G);
        return false;
    }
}

bool doloz(int x, int y, int znak,Dane *G)
{
    G->plansza[x][y]=znak;
    if(G->plansza[x][y]==0)
    {
        gtk_button_set_label(GTK_BUTTON(G->gra[x][y]), "o");
    }
    if(G->plansza[x][y]==1)
    {
        gtk_button_set_label(GTK_BUTTON(G->gra[x][y]), "x");
    }
    return false;
}

bool zabierz(int x, int y, int znak, Dane *G)
{
    //stan_gry(G);
    int i=G->rozmiar_planszy-1;
    while(G->plansza[i][y]!=2 && i>0)
    {
        G->plansza[i][y]=G->plansza[i-1][y];
        i--;
    }
    G->plansza[i+1][y]=G->plansza[i][y]=znak;//bo przekladamy ten znak z dolu i dokladamy jeszcze jeden

    //+
    stan_gry(G);
    for( ; i<G->rozmiar_planszy; i++)
    {
        if(G->plansza[i][y]==0)
        {
            gtk_button_set_label(GTK_BUTTON(G->gra[i][y]), "o");
        }
        if(G->plansza[i][y]==1)
        {
            gtk_button_set_label(GTK_BUTTON(G->gra[i][y]), "x");
        }
    }

    return false;
}

bool wiersze(int x, int y, Dane *G)
{
    int znak=G->plansza[x][y];
    if(znak==2)
    {
        return false;
    }
    int ile=0;
    for (int j=1; j<G->rozmiar_planszy; j++)
    {
        if(G->plansza[x][j]==znak)
        {
            ile++;
        }
        else
        {
            ile=0;
        }
        if(ile>=G->ile_znakow)
        {
            return true;
        }
    }
    return false;
}

bool kolumny(int x, int y, Dane *G)
{
    int znak=G->plansza[x][y];
    if(znak==2)
    {
        return false;
    }
    int ile=0;
    for (int i=1; i<G->rozmiar_planszy; i++)
    {
        if(G->plansza[i][y]==znak)
        {
            ile++;
        }
        else
        {
            ile=0;
        }
        if(ile>=G->ile_znakow)
        {
            return true;
        }
    }
    return false;
}

bool skosy(int x, int y, Dane *G)
{
    int z=G->plansza[x][y];//znak gracza ktory wlasnie wykonal ruch
    if(z==2)
    {
        return false;
    }
    int i=x;//numery wierszy
    int j=y;//numery kolumn
    int ile=0;

    //pierwsza przekatna
    while(i>=0 && j>=0)
    {
        if(G->plansza[i--][j--]==z)
        {
            if(ile>=G->ile_znakow)
            {
                return true;
            }
            ile++;
        }
        else break;
    }
    i=x+1;
    j=y+1;
    while(i<G->rozmiar_planszy && j<G->rozmiar_planszy)
    {
        if(G->plansza[i++][j++]==z)
        {
            if(ile>=G->ile_znakow)
            {
                return true;
            }
            ile++;
        }
        else break;
    }

    //druga przekatna
    i=x;
    j=y;
    ile=0;
    while(i<G->rozmiar_planszy && j>=0)
    {
        if(G->plansza[i++][j--]==z)
        {
            if(ile>=G->ile_znakow)
            {
                return true;
            }
            ile++;
        }
        else break;
    }
    i=x+1;
    j=j+1;
    while(i<G->rozmiar_planszy && i<G->rozmiar_planszy)
    {
        if(G->plansza[i--][j++]==z)
        {
            if(i>=G->ile_znakow)
            {
                return true;
            }
            i++;
        }
        else break;
    }
    return false;
}

bool wygrana(int x, int y, char *opcja, Dane *G)//czy znak byl tylk odokladany czy zaierany i rzesuwamy cala kolumne
{
    if(strcmp(opcja,"doloz")==0)
    {
        if(kolumny(x,y,G)) return true;
        if(wiersze(x,y,G)) return true;
        if(skosy(x,y,G)) return true;
        return false;
    }
    else if (strcmp(opcja, "zabierz")==0)
    {
        //sprawdzenie dla gracza ktory wykonal ruch
        int j=G->rozmiar_planszy-1;
        while(G->plansza[j][y]!=2)
        {
            if(skosy(x,y,G)) return true;
            if(wiersze(x,j,G)) return true;
            j--;
        }
        if(kolumny(x,y,G)) return true;

        //sprawdzenie czy ruch gracza nie spowodowal wygranej jego przeciwnika
        //G->czyj_ruch=(G->czyj_ruch+1)%2;
        for(int i=G->rozmiar_planszy-1; G->plansza[i][y]!=2; i--)
        {
            if(skosy(x,y,G)) return true;
            if(wiersze(x,y,G)) return true;
        }

        //powrot do gracza ktory wykonywal wlasnie ruch
        //G->czyj_ruch=(G->czyj_ruch+1)%2;
        return false;
    }
    printf("Blad funkcji wygrana!\n");
    return false;//to sie nie powinno nigdy zdarzyc ale na wszelki wypadek

}

void stan_gry(Dane *G)
{
    putchar('\n');
    for(int i=0; i<G->rozmiar_planszy; i++)
    {
        for(int j=0; j<G->rozmiar_planszy; j++)
        {
            printf("%d",G->plansza[i][j]);
        }
        putchar('\n');
    }
}

void wyswietl_czas(struct pomocnicza_do_czasu *Czas)
{
    Czas->sekundy+=1;
    //printf("wyswietl_czas: %d",Czas->sekundy);
    int min=Czas->sekundy/60;
    int s=Czas->sekundy%60;
    char czas_text[5];
    czas_text[0]=(char)(min/10);
    czas_text[1]=(char)(min%10);
    czas_text[2]=':';
    czas_text[3]=(char)(s/10);
    czas_text[4]=(char)(s%10);
    gtk_label_set_text(Czas->label_czas2,czas_text);
    gtk_widget_show(Czas->label_czas2);
}
