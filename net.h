#include <netinet/in.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h> 

#define PORT 8080

bool socket_init();
bool bind_socket();
bool take_contact();
