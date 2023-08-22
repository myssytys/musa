#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <curl/curl.h>
#include <webkit2/webkit2.h>

struct MemoryStruct {
	char *memory;
	size_t size;
};

WebKitWebView *webView;


static void button_clicked_callback(GtkWidget *button, gpointer user_data) {
    // Your code here
	printf("%s clicked!", user_data);

	const gchar *url = user_data;

	webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webView), user_data);

}

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *image;

  webView = webkit_web_view_new();

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Music App");
  gtk_window_set_default_size (GTK_WINDOW (window), 1600, 868);

  GtkWidget *mainbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), mainbox);

  GtkWidget *headerbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(mainbox), headerbox, FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(mainbox), webView, TRUE, TRUE, 0);


  button = gtk_button_new_with_label("Spotify");
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), "https:////spotify.com");
  gtk_box_pack_start(GTK_BOX(headerbox), button, FALSE, FALSE, 0);
  g_object_set_data(G_OBJECT(button), "url", (gpointer)"http:////spotify.com");
  
  
  button = gtk_button_new_with_label("YouTube Music"); 
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), "https:////music.youtube.com");
  gtk_box_pack_start(GTK_BOX(headerbox), button, FALSE, FALSE, 0);
  g_object_set_data(G_OBJECT(button), "url", (gpointer)"https:////music.youtube.com");
 

  button = gtk_button_new_with_label("SoundCloud");
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), "https:////soundcloud.com");
  gtk_box_pack_start(GTK_BOX(headerbox), button, FALSE, FALSE, 0);
  g_object_set_data(G_OBJECT(button), "url", (gpointer)"https:////soundcloud.com");


  button = gtk_button_new_with_label("MixCloud");
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), "https:////www.mixcloud.com");
  gtk_box_pack_start(GTK_BOX(headerbox), button, FALSE, FALSE, 0);

  button = gtk_button_new_with_label("Vimeo");
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), "https:////vimeo.com");
  gtk_box_pack_start(GTK_BOX(headerbox), button, FALSE, FALSE, 0);

  button = gtk_button_new_with_label("Deezer");
  gtk_box_pack_start(GTK_BOX(headerbox), button, FALSE, FALSE, 0);
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), webView);


  webkit_web_view_load_uri(webView, "https:////music.youtube.com");

  

  gtk_widget_show_all(window);

//  gtk_widget_set_visible(window, 1);
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if (!ptr) {
    printf("Not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

struct MemoryStruct chunk;

void http_request() {
	CURL *curl;
	CURLcode res;

	chunk.memory = malloc(1);
	chunk.size = 0;
	
	curl = curl_easy_init();
	

		curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
               curl_easy_setopt(curl, CURLOPT_URL, "soundcloud.com");

	       curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	       curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		// PERFORM THE HTTPS REQUEST
		res = curl_easy_perform(curl);

		if(res != CURLE_OK) {
			printf("curl failed!\n");
		}

		if(res != CURLE_OK)
		      fprintf(stderr, "curl_easy_perform() failed: %s\n",
             		 curl_easy_strerror(res));

		curl_easy_cleanup(curl);
}

int
main (int    argc,
      char **argv)
{

    int status, valread, client_fd;

//    http_request();


  GtkApplication *app;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

  status = g_application_run (G_APPLICATION (app), argc, argv);

  g_object_unref (app);

  return status;
}


