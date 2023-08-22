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
#include <libxml/HTMLparser.h>

struct MemoryStruct {
	char *memory;
	size_t size;
};

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
  gtk_grid_attach(GTK_GRID(grid), button, 8,0,1,1);;

  gtk_widget_set_visible(window, 1);
}

void traverse_dom_trees(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next)
    {
        if (cur_node->type == XML_TEXT_NODE)
        {
            printf("Node type: Text, content: %s\n", cur_node->content);
        }
        else if (cur_node->type == XML_ELEMENT_NODE)
        {
            printf("Node type: Element, name: %s\n", cur_node->name);
        }

        traverse_dom_trees(cur_node->children);
    }
}

static size_t write_callback(void *contents, size_t size, size_t nmemb, char *output) {
    size_t total_size = size * nmemb;
    strcat(output, (char *)contents);
    return total_size;
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

CURLcode http_request(const char *url) {
	CURL *curl;
	CURLcode res;

	chunk.memory = malloc(1);
	chunk.size = 0;
	
	curl = curl_easy_init();
	

		curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
               curl_easy_setopt(curl, CURLOPT_URL, "open.spotify.com");

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

		return res;
		curl_easy_cleanup(curl);
}

int
main (int    argc,
      char **argv)
{

    int status, valread, client_fd;
    htmlDocPtr doc;
    xmlNode *roo_element = NULL;
    CURLcode res;

  doc = htmlReadMemory(chunk.memory, chunk.size, "noname.html", NULL, 0);
  if(doc != NULL) {
	  xmlFreeDoc(doc);
  }


  GtkApplication *app;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  
  res = http_request("https:\\\\www.youtube.com");
  
  printf("%s\n", chunk.memory);

  status = g_application_run (G_APPLICATION (app), argc, argv);
 
  // printf("%s\n", res);

  g_object_unref (app);

  return status;
}


