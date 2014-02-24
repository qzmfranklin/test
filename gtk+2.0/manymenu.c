#include <gtk/gtk.h>


int main( int argc, char *argv[])
{

	GtkWidget *window;
	GtkWidget *vbox;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
	gtk_window_set_title(GTK_WINDOW(window), "manymenu");

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	GtkWidget *menubar;
	GtkWidget *filemenu;
	GtkWidget *file;
	GtkWidget *new;
	GtkWidget *openmenu;
	GtkWidget *open;
	GtkWidget *browse;
	GtkWidget *recent;
	GtkWidget *save;
	GtkWidget *saveas;
	GtkWidget *quit;

	menubar  = gtk_menu_bar_new();
	filemenu = gtk_menu_new();
	openmenu = gtk_menu_new();
	file     = gtk_menu_item_new_with_label("File");
	quit     = gtk_menu_item_new_with_label("Quit");
	new      = gtk_menu_item_new_with_label("New");
	open     = gtk_menu_item_new_with_label("Open");
	browse   = gtk_menu_item_new_with_label("Browse");
	recent   = gtk_menu_item_new_with_label("Recent");
	save     = gtk_menu_item_new_with_label("Save");
	saveas   = gtk_menu_item_new_with_label("SaveAs");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), new);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(open), openmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open); 
	gtk_menu_shell_append(GTK_MENU_SHELL(openmenu), browse);
	gtk_menu_shell_append(GTK_MENU_SHELL(openmenu), recent);

	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), saveas);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);

	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);

	g_signal_connect_swapped(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	g_signal_connect(G_OBJECT(quit), "activate",
			G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
