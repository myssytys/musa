#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <webkit/webkit.h>
#include <libsoup/soup.h>
//#include <glib.h>

struct MemoryStruct {
	char *memory;
	size_t size;
};

WebKitWebView* webView;

//WebKitWebsiteDataManager* wDataMng;

const gchar *url ="https:////music.youtube.com";

static void on_button_clicked(GtkWidget *button, gpointer user_data) {
    // Your code here
	printf("%s clicked!", user_data);

	url = user_data;

	webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webView), user_data);

}

/*static void initializeCookieManager(WebKitWebView* webView) {
    // Create a SoupCookieJar
    //SoupCookieJar* cookieJar = soup_cookie_jar_text_new("cookies.txt", 0);
    gchar* cachePath = NULL;
    gchar* dataPath = NULL;

    WebKitWebsiteDataManager* data_manager = webkit_website_data_manager_new(
                "base-cache-directory", cachePath,
                "base-data-directory", dataPath,
                NULL);
    
    // Set the cookie jar for the WebKit WebView
    WebKitCookieManager* cookieManager = (WebKitCookieManager*)webkit_website_data_manager_get_cookie_manager(data_manager);
    webkit_cookie_manager_set_persistent_storage(cookieManager, "cookies.txt", WEBKIT_COOKIE_PERSISTENT_STORAGE_TEXT);
    webkit_cookie_manager_set_accept_policy(cookieManager, WEBKIT_COOKIE_POLICY_ACCEPT_ALWAYS);
}
*/

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;

  GtkWidget *webView = webkit_web_view_new();

//  SoupCookieJar* cookieJar = soup_cookie_jar_text_new("cookies.txt",  0);
  
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "MusicMix");
  gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1080);

  GtkWidget *mainbox = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
//  gtk_container_add(GTK_CONTAINER(window), mainbox);
//
  gtk_window_set_child(GTK_WINDOW(window), mainbox);

  GtkWidget *headerbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  gtk_paned_set_start_child(GTK_PANED(mainbox), headerbox);
//  gtk_box_pack_start(GTK_BOX(mainbox), headerbox, FALSE, FALSE, 0);

//  gtk_box_pack_start(GTK_BOX(mainbox), (GtkWidget*)webView, TRUE, TRUE, 
  ;
//    gtk_window_set_child(GTK_WINDOW(window), headerbox);

    // Create buttons
    GtkWidget *button1 = gtk_button_new_with_label("Button 1");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button_clicked), (gpointer)(url));
    gtk_box_append(GTK_BOX(headerbox), button1);

    GtkWidget *button2 = gtk_button_new_with_label("Button 2");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), "Button 2");
    gtk_box_append(GTK_BOX(headerbox), button2);

    GtkWidget *button3 = gtk_button_new_with_label("Button 3");
    g_signal_connect(button2, "clicked",G_CALLBACK(on_button_clicked), "Button 3");
    gtk_box_append(GTK_BOX(headerbox), button3);

    GtkWidget *button4 = gtk_button_new_with_label("Button 4");
    g_signal_connect(button4, "clicked", G_CALLBACK(on_button_clicked), "Button 4");
    gtk_box_append(GTK_BOX(headerbox), button4);

    gtk_paned_set_end_child(GTK_PANED(mainbox), webView);

    // Show the window
    gtk_window_present(GTK_WINDOW(window));



  webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webView), url);;

//  initializeCookieManager(webView);

  gtk_window_present (GTK_WINDOW (window));
}

int
main (int    argc,
      char **argv)
{

    int status;

  GtkApplication *app;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

  status = g_application_run (G_APPLICATION (app), argc, argv);

  g_object_unref (app);

  return status;
}


