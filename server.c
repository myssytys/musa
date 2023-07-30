#include "server.h"

#define PORT 8080

int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[1024] = { 0 };

bool socket_init() {
	   if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
         return 0;

if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) 
	return 0;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("192.168.198.138");
    address.sin_port = htons(PORT);

    return 1;
}

bool bind_socket() {
// Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        return 0;
    }
    return 1;
}

bool take_contact() {
	if (listen(server_fd, 3) < 0) {
        return 0;
    }
    if ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        return 0;
    }
return 1;
}

bool close_socket() {

      	close(new_socket);
    
	shutdown(server_fd, SHUT_RDWR);

	return 1;
}
