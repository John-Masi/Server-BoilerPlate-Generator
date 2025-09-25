#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <netdb.h>
#include <pthread.h>
#include <string.h>

#define PORT 9000

int main() {
    int server_fd,fd_max;
    const int opt = 1;

    fd_set master;
    fd_set readfds;

    struct sockaddr_in address,clientAddress;

    ssize_t bytes;
    socklen_t t; // Length of client address for accepting connections

    FD_ZERO(&master); // Zeroes out fds
    FD_ZERO(&readfds);

    server_fd = socket(AF_INET,SOCK_STREAM,0);

    setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0) {
        perror("");
        exit(1);
        return 1;
    }

    if (listen(server_fd,10) < 0) {
        perror("");
        exit(1);
        return 1;
    }

    FD_SET(server_fd,&master);
    fd_max = server_fd;
    while (1) {

    }

}