#include <gtk/gtk.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>

GtkEntry* g_entryPlayer1;
GtkEntry* g_entryPlayer2;
GtkWidget* g_checkFullScreen;
GtkWidget* g_buttonPlay;
GtkWidget* g_dialog;

bool g_fullScreen = false;

void free_memory(void);

/**
\mainpage ShipDuel Launcher Documentation

Welcome to the documentation of Ship Duel Launcher. This program is a simple Gtk interface program written in C which aims to launch
a game called Ship Duel.

*/

/*!
Main function
@param argc The number of the arguments + 1
@param args The array containing the arguments (as strings)
*/
int main(int argc, char *args[])
{
    GtkBuilder *builder;
    GtkWidget *window;

    gtk_init(&argc, &args);

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../GUI/window.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    // Get components
    g_entryPlayer1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry_p1"));
    g_entryPlayer2 = GTK_ENTRY(gtk_builder_get_object(builder, "entry_p2"));
    g_checkFullScreen = GTK_WIDGET(gtk_builder_get_object(builder, "checkbutton_fullscreen"));
    g_buttonPlay = GTK_WIDGET(gtk_builder_get_object(builder, "button_play"));

    g_object_unref(builder);

    gtk_widget_show(window);

    gtk_main();

    return 0;
}

/*!
Called when the Play button is clicked
*/
extern "C" void on_button_play_clicked()
{
    char p1Name[50];
    char p2Name[50];
    char command[100];

    sprintf(p1Name, "%s", gtk_entry_get_text(g_entryPlayer1));
    sprintf(p2Name, "%s", gtk_entry_get_text(g_entryPlayer2));
    sprintf(command, "cd ../../Game/src/; ./ShipDuel %s %s %d", p1Name, p2Name, g_fullScreen);

    if (strcmp(p1Name, "") != 0 && strcmp(p2Name, "") != 0 && strcmp(p1Name, p2Name) != 0)
    {
        std::system(command);

        gtk_main_quit();
    }
}

/*!
Called once if full screen mode checkbutton is toggled
*/
extern "C" void on_checkbutton_fullscreen_toggled()
{
    g_fullScreen = !g_fullScreen;
}

/*!
Called when window is closed
*/
extern "C" void on_window_main_destroy()
{
    free_memory();

    gtk_main_quit();    
}

void free_memory()
{
    delete g_entryPlayer1;
    delete g_entryPlayer2;
    delete g_checkFullScreen;
    delete g_buttonPlay;
}