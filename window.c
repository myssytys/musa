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

#define PORT 80
#define SERVER_PORT 80
#define SERVER_ADDRESS "216.58.210.174"

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

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
  gtk_widget_set_name(button, "spotify");

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

void http_get_request() {
    struct sockaddr_in server_addr;
    int sockfd;
    char request[] = "GET / HTTP/1.1\r\nHost: www.example.com\r\nConnection: close\r\n\r\n";
    char buffer[1024];

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Socket creation failed");
        return;
    }

    // Set up the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_ADDRESS, &(server_addr.sin_addr));

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Connection to the server failed");
        close(sockfd);
        return;
    }

    // Send the HTTP request
    if (send(sockfd, request, strlen(request), 0) < 0) {
        printf("Send failed");
        close(sockfd);
        return;
    }

    // Receive and print the server's response
    int bytes_received;
    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    // Close the socket
    close(sockfd);
}

int
main (int    argc,
      char **argv)
{

    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
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
  
  http_get_request();
  status = g_application_run (G_APPLICATION (app), argc, argv);

  g_object_unref (app);

  return status;
}


