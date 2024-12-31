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
//	printf("%s clicked!", user_data);

	url = user_data;

	webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webView), user_data);

}

/*static void initializeCookieManager(WebKitWebView* webView) {
    // Create a SoupCookieJar
    //SoupCookieJar* cookieJar = soup_cookie_jar_text_new("cookies.txt", 0);
    gchar* cachePath = nullptr;
    gchar* dataPath = nullptr;

    WebKitWebsiteDataManager* data_manager = webkit_website_data_manager_new(
                "base-cache-directory", cachePath,
                "base-data-directory", dataPath,
                nullptr);
    
    // Set the cookie jar for the WebKit WebView
    WebKitCookieManager* cookieManager = webkit_website_data_manager_get_cookie_manager();
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

//  SoupCookieJar* cookieJar = soup_cookie_jar_text_new("cookies.txt",  0);

  webView  = (WebKitWebView*)webkit_web_view_new();
  
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "MusicMix");
  gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1080);

  GtkWidget *mainbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//  gtk_container_add(GTK_CONTAINER(window), mainbox);

  GtkWidget *headerbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
//  gtk_box_pack_start(GTK_BOX(mainbox), headerbox, FALSE, FALSE, 0);

//  gtk_box_pack_start(GTK_BOX(mainbox), (GtkWidget*)webView, TRUE, TRUE, 
  
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(vbox, 10);
    gtk_widget_set_margin_bottom(vbox, 10);
    gtk_widget_set_margin_start(vbox, 10);
    gtk_widget_set_margin_end(vbox, 10);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // Create buttons
    GtkWidget *button1 = gtk_button_new_with_label("Button 1");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button_clicked), "Button 1");
    gtk_box_append(GTK_BOX(vbox), button1);

    GtkWidget *button2 = gtk_button_new_with_label("Button 2");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), "Button 2");
    gtk_box_append(GTK_BOX(vbox), button2);

    // Show the window
    gtk_window_present(GTK_WINDOW(window));



  webkit_web_view_load_uri(webView, url);;

//  initializeCookieManager(webView);

 // gtk_widget_show_all(window);
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


