#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345
#define BUFFER_SIZE 1024

typedef struct {
    int socket;
    struct sockaddr_in address;
} client_t;

client_t *clients[10];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast_message(const char *message, int exclude_socket) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < client_count; ++i) {
        if (clients[i]->socket != exclude_socket) {
            send(clients[i]->socket, message, strlen(message), 0);
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    client_t *client = (client_t *)arg;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = recv(client->socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[bytes_read] = '\0';
        printf("Received: %s", buffer);
        broadcast_message(buffer, client->socket);
    }

    close(client->socket);

    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < client_count; ++i) {
        if (clients[i]->socket == client->socket) {
            for (int j = i; j < client_count - 1; ++j) {
                clients[j] = clients[j + 1];
            }
            break;
        }
    }

    client_count--;

    pthread_mutex_unlock(&clients_mutex);

    free(client);
    pthread_exit(NULL);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t tid;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) == -1) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }

        client_t *client = (client_t *)malloc(sizeof(client_t));
        client->socket = client_socket;
        client->address = client_addr;

        pthread_mutex_lock(&clients_mutex);
        clients[client_count++] = client;
        pthread_mutex_unlock(&clients_mutex);

        pthread_create(&tid, NULL, handle_client, (void *)client);
        pthread_detach(tid);
    }

    close(server_socket);
    return 0;
}