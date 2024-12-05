#include "../message_types/index.h"
#include "../controllers/controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080
#define BACKLOG 10

void handle_control_message(int socket, ControlMessage *msg)
{
    if (strcmp(msg->type, LOGIN) == 0)
    {
        handle_login(socket, msg);
    }
    else if (strcmp(msg->type, GET_ROOM_LIST) == 0)
    {
    }
    else if (strcmp(msg->type, CREATE_ROOM) == 0)
    {
    }
}

void handle_data_message(int socket, DataMessage *msg)
{
    if (strcmp(msg->type, ANSWER_SUBMISSION) == 0)
    {
        // Handle ANSWER_SUBMISSION
    }
    else if (strcmp(msg->type, EXAM_QUESTION) == 0)
    {
        // Handle EXAM_QUESTION
    }
    else if (strcmp(msg->type, PRACTICE_QUESTION) == 0)
    {
        // Handle PRACTICE_QUESTION
    }
}

void handle_notification_message(int socket, NotificationMessage *msg)
{
    if (strcmp(msg->type, ERROR_MESSAGE) == 0)
    {
        // Handle ERROR_MESSAGE
    }
}

void setup_routes(int server_fd)
{
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int new_socket;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, BACKLOG) < 0)
    {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        char buffer[2048];
        memset(buffer, 0, sizeof(buffer));
        read(new_socket, buffer, 2048);
        // printf("Received: %s\n", buffer);

        char msg_type[50];
        sscanf(buffer, "%s", msg_type);

        if (strcmp(msg_type, "CONTROL") == 0)
        {
            ControlMessage msg;
            sscanf(buffer, "%s %s\n%[^\n]", msg_type, msg.type, msg.body);
            handle_control_message(new_socket, &msg);
        }
        else if (strcmp(msg_type, "DATA") == 0)
        {
            DataMessage msg;
            sscanf(buffer, "DATA %s %s %d\n%[^\n]", msg.type, msg.data_type, &msg.data_size, msg.body);
            handle_data_message(new_socket, &msg);
        }
        else if (strcmp(msg_type, "NOTIFICATION") == 0)
        {
            NotificationMessage msg;
            sscanf(buffer, "NOTIFICATION %s %s\n%[^\n]", msg.type, msg.timestamp, msg.body);
            handle_notification_message(new_socket, &msg);
        }

        close(new_socket);
    }
}