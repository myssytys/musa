#include <gtk/gtk.h>

// Callback for a button in one of the screens
static void on_button_clicked(GtkButton *button, gpointer user_data) {
    const char *label = gtk_button_get_label(button);
    g_print("Button '%s' clicked in %s\n", label, (char *)user_data);
}

// Callback for application activation
static void on_activate(GtkApplication *app, gpointer user_data) {
    // Create the main window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Two Screens in One Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Create a horizontal paned container
    GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_window_set_child(GTK_WINDOW(window), paned);

    // Create the first screen (left pane)
    GtkWidget *left_screen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *label1 = gtk_label_new("Screen 1");
    GtkWidget *button1 = gtk_button_new_with_label("Click Me");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button_clicked), "Screen 1");
    gtk_box_append(GTK_BOX(left_screen), label1);
    gtk_box_append(GTK_BOX(left_screen), button1);

    // Add the first screen to the left pane
    gtk_paned_set_start_child(GTK_PANED(paned), left_screen);

    // Create the second screen (right pane)
    GtkWidget *right_screen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *label2 = gtk_label_new("Screen 2");
    GtkWidget *button2 = gtk_button_new_with_label("Click Me Too");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), "Screen 2");
    gtk_box_append(GTK_BOX(right_screen), label2);
    gtk_box_append(GTK_BOX(right_screen), button2);

    // Add the second screen to the right pane
    gtk_paned_set_end_child(GTK_PANED(paned), right_screen);

    // Show the window
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    // Create a new GTK application
    GtkApplication *app = gtk_application_new("com.example.TwoScreens", G_APPLICATION_FLAGS_NONE);

    // Connect the activate signal to the callback
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    // Run the application
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    // Cleanup
    g_object_unref(app);

    return status;
}
