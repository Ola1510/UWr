#include "funkcje.h"
#include "menu.h"
#include <gtk/gtk.h>

struct pomocnicza_zamykanie_okien
{
    GtkWidget *main_window;
    GtkWidget *info_window;
    Dane *G;
};

void strona_startowa(struct pomocnicza_zamykanie_okien *ZO);
void pomocnicza_inicjalizacja_gry(GtkWidget *widget, struct pomocnicza_zamykanie_okien *ZO);
void inicjalizacja_gry (struct pomocnicza_zamykanie_okien *ZO);
void graj(GtkWidget *button,  struct pomocnicza_zamykanie_okien *ZO);

struct pomocnicza_strona_startowa
{
    Dane *G;
    GtkWidget *guziki_opcji[5];
    //GdkColor color;
};
void guziki_opcji (GtkWidget *widget, struct pomocnicza_strona_startowa *SS);

void plik_kolory();
GdkColor color;
GdkColor color_bg;
void nowa_gra(GtkWidget *widget, struct pomocnicza_zamykanie_okien *ZO);


int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    if(argc<1)
    {
        printf("Blad: niepoprawna liczba argumentow!");
        exit(1);
    }

    GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),650,500);
    gtk_window_set_title(GTK_WINDOW(window),"Kółko i krzyżyk");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    g_signal_connect(G_OBJECT(window),"destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *menu;
    menu=gtk_menu_bar_new();

    GtkWidget *ustawienia_menu;
    ustawienia_menu=gtk_menu_new();

    GtkWidget *menu_item;
    menu_item=gtk_menu_item_new_with_label("Ustawienia");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),ustawienia_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),menu_item);

    menu_item=gtk_menu_item_new_with_label("Kolory");
    gdk_color_parse("teal",&color);
    gtk_menu_shell_append(GTK_MENU_SHELL(ustawienia_menu),menu_item);
    g_signal_connect(menu_item,"activate",G_CALLBACK(kolory),&color);

    menu_item=gtk_menu_item_new_with_label("Znaki");
    gtk_menu_shell_append(GTK_MENU_SHELL(ustawienia_menu),menu_item);

    menu_item=gtk_menu_item_new_with_label("Zasady gry");
    gtk_menu_shell_append(GTK_MENU_SHELL(ustawienia_menu),menu_item);
    g_signal_connect(menu_item,"activate",G_CALLBACK(zasady_gry),NULL);

    GtkWidget *start_box;
    start_box=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_container_add(GTK_WINDOW(window),start_box);
    gtk_box_pack_start(GTK_BOX(start_box),menu,0,0,0);

    static struct pomocnicza_zamykanie_okien ZO;
    ZO.main_window=window;
    ZO.info_window=start_box;

    strona_startowa(&ZO);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

void strona_startowa(struct pomocnicza_zamykanie_okien *ZO)
{
    GtkWidget *box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(ZO->info_window), box, TRUE, TRUE, 0);
    GtkWidget *grid;
    grid=gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_box_pack_start(GTK_BOX(box), grid, TRUE, TRUE, 0);

    plik_kolory();

    //------------------ustawianie strony startowej-------------------------//

    for (int i=1; i<9; i++)
    {
        for (int j=0; j<5; j++)
        {
            GtkWidget *label0= gtk_label_new(" ");
            gtk_grid_attach(GTK_GRID(grid),label0, i,j,1,1);
        }
    }

    GtkWidget *frame1=gtk_frame_new(NULL);
    gtk_grid_attach(GTK_GRID(grid), frame1,0,0,10,2);

    GtkWidget *frame2=gtk_frame_new(NULL);
    gtk_grid_attach(GTK_GRID(grid), frame2,0,2,10,2);

    //--------------------------------------------------------------------//
    static struct pomocnicza_strona_startowa SS;

    GtkWidget *label1=gtk_label_new("Proszę wybrać rozmiar planszy");
    gtk_grid_attach(GTK_GRID(grid),label1,0,0,10,1);
    gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_CENTER);

    GtkWidget *button11= gtk_button_new_with_label("5x5");
    //gtk_widget_set_name(button11,klikniety);
    gtk_grid_attach(GTK_GRID(grid),button11, 1,1,2,1);
    SS.guziki_opcji[0]=button11;

    GtkWidget *button12= gtk_button_new_with_label("7x7");
    gtk_grid_attach(GTK_GRID(grid),button12, 4,1,2,1);
    SS.guziki_opcji[1]=button12;


    GtkWidget *button13= gtk_button_new_with_label("10x10");
    gtk_grid_attach(GTK_GRID(grid),button13, 7,1,2,1);
    SS.guziki_opcji[2]=button13;


    //--------------------------------------------------------------------//

    GtkWidget *label2=gtk_label_new("Proszę wybrać poziom tudności");
    gtk_grid_attach(GTK_GRID(grid),label2,0,2,10,1);
    gtk_label_set_justify(GTK_LABEL(label2), GTK_JUSTIFY_CENTER);

    GtkWidget *button21= gtk_button_new_with_label("klasyczny: 4");
    gtk_grid_attach(GTK_GRID(grid),button21, 1,3,3,1);
    SS.guziki_opcji[3]=button21;


    GtkWidget *button22= gtk_button_new_with_label("expert: 5");
    gtk_grid_attach(GTK_GRID(grid),button22, 6,3,3,1);
    SS.guziki_opcji[4]=button22;


    //-------------------------------wybor opcji gry-------------------------------------//

    static Dane G;
    G.ile_znakow=4;
    G.rozmiar_planszy=5;
    SS.G=&G;

    g_signal_connect(button11, "clicked", G_CALLBACK(guziki_opcji), &SS);
    g_signal_connect(button12, "clicked", G_CALLBACK(guziki_opcji), &SS);
    g_signal_connect(button13, "clicked", G_CALLBACK(guziki_opcji), &SS);
    g_signal_connect(button21, "clicked", G_CALLBACK(guziki_opcji), &SS);
    g_signal_connect(button22, "clicked", G_CALLBACK(guziki_opcji), &SS);

    //--------------------------------------------------------------------//

    ZO->G=&G;
    GtkWidget *button_start=gtk_button_new_with_label("Start");
    gtk_grid_attach(GTK_GRID(grid),button_start,0,4,10,1);
    g_signal_connect(button_start, "clicked", G_CALLBACK(pomocnicza_inicjalizacja_gry), ZO);
}

void pomocnicza_inicjalizacja_gry(GtkWidget *widget, struct pomocnicza_zamykanie_okien *ZO)
{
    inicjalizacja_gry(ZO);
}

void inicjalizacja_gry (struct pomocnicza_zamykanie_okien *ZO)
{
    przygotuj_plansze(ZO->G);

    //otworz widok gry
    GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),650,500);
    gtk_window_set_title(GTK_WINDOW(window),"Kolko i krzyzyk");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    g_signal_connect(G_OBJECT(window),"destroy", G_CALLBACK(gtk_main_quit), NULL);
    gdk_color_parse("#ADD8E6",&color_bg);
    gtk_widget_modify_bg(window,GTK_STATE_NORMAL,&color_bg);
    ZO->main_window=window;

    GtkWidget *box;
    box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *grid;
    grid=gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_box_pack_start(GTK_BOX(box), grid, TRUE, TRUE, 0);

    ///dlaczego nie dziala czas
    GtkWidget *label_czas1=gtk_label_new("Czas gry: ");
    gtk_grid_attach(GTK_GRID(grid),label_czas1,0,0,1,1);
    GtkWidget *label_czas2=gtk_label_new("00:00");
    gtk_grid_attach(GTK_GRID(grid),label_czas2,1,0,1,1);
    static struct pomocnicza_do_czasu Czas;
    Czas.label_czas2=label_czas2;
    Czas.sekundy=0;
    //g_timeout_add (10000,wyswietl_czas, &Czas);

    GtkWidget *label_ruch1=gtk_label_new("Ruch gracza: ");
    gtk_grid_attach(GTK_GRID(grid),label_ruch1,3,0,1,1);
    GtkWidget *label_ruch2=gtk_label_new("o");
    gtk_grid_attach(GTK_GRID(grid),label_ruch2,4,0,1,1);
    ZO->G->znak=label_ruch2;

    ZO->G->czyj_ruch=0;//ruch x-1,   ruch o-0
    for(int i=0; i<ZO->G->rozmiar_planszy; i++)
    {
        for(int j=0; j<ZO->G->rozmiar_planszy; j++)
        {
            GtkWidget *button=gtk_button_new_with_label(" ");
            ZO->G->gra[j][i]=button;
            gtk_grid_attach(GTK_GRID(grid),button, i,j+1,1,1);
            g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(graj), ZO);

            GtkWidget *frame=gtk_frame_new(NULL);
            gtk_grid_attach(GTK_GRID(grid), frame,i,j+1,1,1);
        }
    }

    gtk_widget_show_all(window);
    gtk_main();
}

void graj(GtkWidget *button, struct pomocnicza_zamykanie_okien *ZO)
{
    int x,y;
    bool stop=false;
    for(int i=0; i<ZO->G->rozmiar_planszy; i++)
    {
        if(stop) break;
        for(int j=0; j<ZO->G->rozmiar_planszy; j++)
        {
            if(stop) break;
            if(button==ZO->G->gra[i][j])
            {
                x=i;
                y=j;
                stop=true;
            }
        }
    }

    if(wykonaj_ruch(x,y,ZO->G))
    {
        GtkWidget *info=gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(info),300,150);
        gtk_window_set_title(GTK_WINDOW(info),"Koniec gry");
        gtk_window_set_position(GTK_WINDOW(info), GTK_WIN_POS_CENTER);
        gtk_container_set_border_width(GTK_CONTAINER(info), 0);
        g_signal_connect(G_OBJECT(info),"destroy", G_CALLBACK(gtk_main_quit), NULL);

        GtkWidget *box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(info),box);

        GtkWidget *grid;
        grid=gtk_grid_new();
        gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
        gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
        gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
        gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
        gtk_box_pack_start(GTK_BOX(box), grid, TRUE, TRUE, 0);

        GtkLabel *komunikat;
        if(ZO->G->czyj_ruch==1)komunikat=gtk_label_new("Wygrywa gracz x!");
        else komunikat=gtk_label_new("Wygrywa gracz o!");
        gtk_grid_attach(GTK_GRID(grid),komunikat,0,0,6,2);

        GtkWidget *button_exit=gtk_button_new_with_label("Zakończ");
        gtk_grid_attach(GTK_GRID(grid),button_exit,0,2,3,1);
        g_signal_connect(button_exit,"clicked",G_CALLBACK(gtk_main_quit),NULL);

        GtkWidget *button_nowa_gra=gtk_button_new_with_label("Nowa gra");
        gtk_grid_attach(GTK_GRID(grid),button_nowa_gra,3,2,3,1);
        //struct pomocnicza_zamykanie_okien NG;
        //NG.G=ZO->G;
        //NG.main_window=ZO->main_window;
        //NG.info_window=info;
        ZO->info_window=info;
        gtk_widget_show_all(info);
        g_signal_connect(button_nowa_gra,"clicked",G_CALLBACK(nowa_gra),ZO);

        for(int i=0; i<ZO->G->rozmiar_planszy; i++)
        {
            for(int j=0; j<ZO->G->rozmiar_planszy; j++)
            {
                gtk_widget_set_sensitive(ZO->G->gra[i][j],false);
            }
        }

    }
    ZO->G->czyj_ruch=(ZO->G->czyj_ruch+1)%2;//bo w kolejnej rundzie ruch ma drugi gracz
    if(ZO->G->czyj_ruch==0)gtk_label_set_text(GTK_LABEL(ZO->G->znak),"o");
    else gtk_label_set_text(GTK_LABEL(ZO->G->znak),"x");
}
//--------------------funkcje pomocnicze do strony startowej-------------------------//

void guziki_opcji (GtkWidget *widget, struct pomocnicza_strona_startowa *SS)
{
    GdkColor basic;
    gdk_color_parse("gray",&basic);

    if(widget==SS->guziki_opcji[0])
    {
        SS->G->rozmiar_planszy=5;
        gtk_widget_modify_fg(GTK_WIDGET(SS->guziki_opcji[0]),GTK_STATE_NORMAL,&color);
        gtk_widget_modify_fg(SS->guziki_opcji[1],GTK_STATE_NORMAL,&basic);
        gtk_widget_modify_fg(SS->guziki_opcji[2],GTK_STATE_NORMAL,&basic);
    }
    if(widget==SS->guziki_opcji[1])
    {
        SS->G->rozmiar_planszy=7;
        gtk_widget_modify_fg(SS->guziki_opcji[1],GTK_STATE_NORMAL,&color);
        gtk_widget_modify_fg(SS->guziki_opcji[0],GTK_STATE_NORMAL,&basic);
        gtk_widget_modify_fg(SS->guziki_opcji[2],GTK_STATE_NORMAL,&basic);
    }
    if(widget==SS->guziki_opcji[2])
    {
        SS->G->rozmiar_planszy=10;
        gtk_widget_modify_fg(SS->guziki_opcji[2],GTK_STATE_NORMAL,&color);
        gtk_widget_modify_fg(SS->guziki_opcji[1],GTK_STATE_NORMAL,&basic);
        gtk_widget_modify_fg(SS->guziki_opcji[0],GTK_STATE_NORMAL,&basic);
    }
    if(widget==SS->guziki_opcji[3])
    {
        SS->G->ile_znakow=4;
        gtk_widget_modify_fg(SS->guziki_opcji[3],GTK_STATE_NORMAL,&color);
        gtk_widget_modify_fg(SS->guziki_opcji[4],GTK_STATE_NORMAL,&basic);
    }
    if(widget==SS->guziki_opcji[4])
    {
        SS->G->ile_znakow=5;
        gtk_widget_modify_fg(SS->guziki_opcji[4],GTK_STATE_NORMAL,&color);
        gtk_widget_modify_fg(SS->guziki_opcji[3],GTK_STATE_NORMAL,&basic);
    }
}


//--------------------funkcje pomocnicze do menu, kolorow i nowej gry-------------------------//

void plik_kolory()
{
    GtkCssProvider *css_provider=css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "plik_kolory.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),GTK_STYLE_PROVIDER(css_provider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void nowa_gra(GtkWidget *widget, struct pomocnicza_zamykanie_okien *ZO)
{
    gtk_widget_destroy(ZO->info_window);
    gtk_widget_destroy(ZO->main_window);
    ZO->info_window=NULL;
    ZO->main_window=NULL;
    inicjalizacja_gry(ZO);
}


