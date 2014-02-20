#include <gtk/gtk.h>

int main( int argc, char *argv[])
{
	GtkWidget *window;

	gtk_init(&argc, &argv);

	printf("GTK_WINDOW_TOPLEVEL=%d\n",GTK_WINDOW_TOPLEVEL);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(window);

	gtk_main();

	return 0;
}
