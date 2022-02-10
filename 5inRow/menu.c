#include "menu.h"


void zasady_gry(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *info=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(info),300,150);
    gtk_window_set_title(GTK_WINDOW(info),"Zasady gry");
    gtk_window_set_position(GTK_WINDOW(info), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(info), 0);
    g_signal_connect(G_OBJECT(info),"destroy", G_CALLBACK(gtk_window_close), info);
    GtkLabel *komunikat;
    komunikat=gtk_label_new(" Kółko i krzyżyk\n\n To gra dla dwuch graczy.\n Jej celem jest ustawienie 4/5 swoich znakow jeden po drugim w jednym rzedzie, kolumnie czy przekatnej.\n Zanki mozesz kłaść jedynie na sam dół planszy, toż nad znak wczesniej położony\n lub zdjąć swoj znak jeśli jest na samym dole planszy, wowczas przeskoczy on na wszystkie inne znak, ktore zkolei spadna na dół kolumny,\n i znow na samam gore zostanie polozony jeszcze jeden twoj znak.\n\n Na poczatku wybierz rozmiar planszy i ilość znaków potrzebnych do wygrania gry.\n\n Możesz spersonalizować swoją rozgrywkę zmieniając w ustawieniach kolor planszy czy znak, jakiego uzywasz (wyjściowo biały, o/x).\n\n Miłej zabawy i powodzenia!\n ");
    gtk_container_add(GTK_CONTAINER(info),komunikat);
    gtk_widget_show_all(info);
}

void kolory(GtkWidget *widget, GdkColor *color)
{
    GtkWidget *kolory=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(kolory),320,150);
    gtk_window_set_title(GTK_WINDOW(kolory),"Personalizacja koloru planszy    ");
    gtk_window_set_position(GTK_WINDOW(kolory), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(kolory), 0);
    g_signal_connect(G_OBJECT(kolory),"destroy", G_CALLBACK(gtk_window_close), kolory);
    GtkWidget *box;
    box=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_container_add(GTK_CONTAINER(kolory),box);
    GtkLabel *komunikat;
    komunikat=gtk_label_new("Prosze nacisnąć guzik poniżej");
    gtk_container_add(GTK_CONTAINER(box),komunikat);
    GtkWidget *color_button=gtk_color_button_new();
    gtk_box_pack_end(GTK_BOX(box),color_button,1,1,1);
    gtk_widget_show_all(kolory);
    gtk_color_button_get_color(color_button,color);
}
