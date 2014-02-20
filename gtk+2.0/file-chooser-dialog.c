#include <gtk/gtk.h>


void select_file(GtkWidget *widget, gpointer window)
{
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new ("Open File",
			window,
			GTK_FILE_CHOOSER_ACTION_OPEN,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
			NULL);
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
		char *filename;

		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		/*open_file (filename);*/
		g_printf("%s\n",filename);
		g_free(filename);
	}
	gtk_widget_destroy (dialog);
}


int main( int argc, char *argv[])
{

	GtkWidget *window;
	GtkWidget *label;
	GtkWidget *vbox;

	GtkWidget *toolbar;
	GtkToolItem *file;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 280, 200);
	gtk_window_set_title(GTK_WINDOW(window), "Font Selection Dialog");

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);


	toolbar = gtk_toolbar_new();
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

	gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2);

	file = gtk_tool_button_new_from_stock(GTK_STOCK_SELECT_FONT);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), file, -1);

	gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

	label = gtk_label_new("ZetCode");
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
	gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, FALSE, 5);


	g_signal_connect(G_OBJECT(file), "clicked", 
			G_CALLBACK(select_file), window);

	g_signal_connect_swapped(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	printf("sizeof(gchar)\t= %lu\n",sizeof(gchar));



	gtk_main();

	return 0;
}
