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

#define PORT 80
#define SERVER_PORT 80
#define SERVER_ADDRESS "216.58.209.206"

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *image;

  grid = gtk_grid_new();

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Youtube App");
  gtk_window_set_default_size (GTK_WINDOW (window), 1024, 768);

  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  
  gtk_window_set_child(GTK_WINDOW (window), grid);

  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_file(cssProvider, g_file_new_for_path("styles.css"));

  gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);


  button = gtk_button_new_with_label("Spotify");
//  gtk_widget_set_name(button, "spotify");
  gtk_widget_set_name(button, "Spotify");

  g_signal_connect(button, "clicked", NULL, NULL);
  gtk_grid_attach(GTK_GRID(grid), button, 3,0,1,1);
  
  button = gtk_button_new_with_label("YouTube");
  gtk_widget_set_name(button, "youtube");

  g_signal_connect(button, "clicked", NULL, NULL);
  gtk_grid_attach(GTK_GRID(grid), button, 4,0,1,1);

  button = gtk_button_new_with_label("SoundCloud");
  g_signal_connect(button, "clicked", NULL, NULL);
  gtk_grid_attach(GTK_GRID(grid), button, 5,0,1,1);

  button = gtk_button_new_with_label("MixCloud");
  g_signal_connect(button, "clicked", NULL, NULL);
  gtk_grid_attach(GTK_GRID(grid), button, 6,0,1,1);

  button = gtk_button_new_with_label("Vimeo");
  g_signal_connect(button, "clicked", NULL, NULL);
  gtk_grid_attach(GTK_GRID(grid), button, 7,0,1,1);

  button = gtk_button_new_with_label("Deezer");
  g_signal_connect(button, "clicked", NULL, NULL);
  gtk_grid_attach(GTK_GRID(grid), button, 8,0,1,1);

  gtk_widget_set_visible(window, 1);
}

static size_t write_callback(void *contents, size_t size, size_t nmemb, char *output) {
    size_t total_size = size * nmemb;
    strcat(output, (char *)contents);
    return total_size;
}

void http_request(const char *url) {
	CURL *curl;
	CURLcode res;
	char output[4096] = {0};
	
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);

curl_version();

		// PERFORM THE HTTPS REQUEST
		res = curl_easy_perform(curl);

		if(res != CURLE_OK) {
			printf("curl failed!\n");
		}

		curl_easy_cleanup(curl);

		printf("%s\n", output);
	}


}

int
main (int    argc,
      char **argv)
{

    int status, valread, client_fd;
  /*  struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "192.168.198.138", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }

     /*if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }^**/

 // http_get_request();

  GtkApplication *app;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  
  http_request("www.youtube.com");
  status = g_application_run (G_APPLICATION (app), argc, argv);

  g_object_unref (app);

  return status;
}


