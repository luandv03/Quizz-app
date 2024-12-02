#include "routes.h"
#include "../controllers/controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080
#define BACKLOG 10

void setup_routes(int server_fd) {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int new_socket;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, BACKLOG) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);

        if (strstr(buffer, "POST /signup") != NULL) {
            char email[256], password[256], username[256];
            sscanf(buffer, "POST /signup email=%s password=%s username=%s", email, password, username);
            handle_signup(new_socket, email, password, username);
        } else if (strstr(buffer, "POST /signin") != NULL) {
            char email[256], password[256];
            sscanf(buffer, "POST /signin email=%s password=%s", email, password);
            handle_signin(new_socket, email, password);
        } else {
            handle_request(new_socket);
        }
    }
}