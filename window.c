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

WebKitWebsiteDataManager* wDataMng;

const gchar *url ="https:////music.youtube.com";

static void button_clicked_callback(GtkWidget *button, gpointer user_data) {
    // Your code here
//	printf("%s clicked!", user_data);

	url = user_data;

	webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webView), user_data);

}

static void initializeCookieManager(WebKitWebView* webView) {
    // Create a SoupCookieJar
    //SoupCookieJar* cookieJar = soup_cookie_jar_text_new("cookies.txt", 0);


    wDataMng* = webkit_website_data_manager_new("base-data-directory", webkit_website_data_manager_get_base_data_directory(&wDataMng), "base-cache-directory",webkit_website_data_manager_get_base_cache_directory(&wDataMng), "local-storage-directory", webkit_website_data_manager_get_local_storage_directory(&wDataMng), "offline-application-cache-directory", webkit_website_data_manager_get_offline_application_cache_directory(&wDataMng), "indexddb_directory", webkit_website_data_manager_get_indexeddb_directory(&wDataMng), "websql-directory", webkit_website_data_manager_get_websql_directory(&wDataMng) );
    
    // Set the cookie jar for the WebKit WebView
    WebKitCookieManager* cookieManager = webkit_website_data_manager_get_cookie_manager();
    webkit_cookie_manager_set_persistent_storage(cookieManager, "cookies.txt", WEBKIT_COOKIE_PERSISTENT_STORAGE_TEXT);
    webkit_cookie_manager_set_accept_policy(cookieManager, WEBKIT_COOKIE_POLICY_ACCEPT_ALWAYS);
}




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
  gtk_container_add(GTK_CONTAINER(window), mainbox);

  GtkWidget *headerbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(mainbox), headerbox, FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(mainbox), (GtkWidget*)webView, TRUE, TRUE, 0);


  button = gtk_button_new_with_label("Spotify");
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), "https:////spotify.com");
  gtk_box_pack_start(GTK_BOX(headerbox), button, FALSE, FALSE, 0);
  g_object_set_data(G_OBJECT(button), "url", (gpointer)"https:////spotify.com");
  
  
  button = gtk_button_new_with_label("YouTube");
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), "https:////www.youtube.com");
  gtk_box_pack_start(GTK_BOX(headerbox), button, FALSE, FALSE, 0);
  g_object_set_data(G_OBJECT(button), "url", (gpointer)"https:////www.youtube.com");
 
  button = gtk_button_new_with_label("YouTube Music"); 
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), "https:////music.youtube.com");
  gtk_box_pack_start(GTK_BOX(headerbox), button, FALSE, FALSE, 0);
  g_object_set_data(G_OBJECT(button), "url", (gpointer)"https:////music.youtube.com");
 

  button = gtk_button_new_with_label("SoundCloud");
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), "https:////soundcloud.com");
  gtk_box_pack_start(GTK_BOX(headerbox), button, FALSE, FALSE, 0);
  g_object_set_data(G_OBJECT(button), "url", (gpointer)"https:////soundcloud.com");


/*  button = gtk_button_new_with_label("MixCloud");
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), "https:////www.mixcloud.com");
  gtk_box_pack_start(GTK_BOX(headerbox), button, FALSE, FALSE, 0);
*/
  button = gtk_button_new_with_label("Vimeo");
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), "https:////vimeo.com");
  gtk_box_pack_start(GTK_BOX(headerbox), button, FALSE, FALSE, 0);

  button = gtk_button_new_with_label("Deezer");
  gtk_box_pack_start(GTK_BOX(headerbox), button, FALSE, FALSE, 0);
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), "http:////www.deezer.com");

  webkit_web_view_load_uri(webView, url);;

  initializeCookieManager(webView);

  //SoupMessage *msg;

  //msg = soup_message_new("POST", url);


  gtk_widget_show_all(window);
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


