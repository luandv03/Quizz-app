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
    else if (strcmp(msg->type, SIGN_UP) == 0)
    {
        handle_signup(socket, msg);
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

        printf("Received:\n%s\n", buffer);

        char *msg_type = strtok(buffer, "\n");
        char *body = msg_type + strlen(msg_type) + 1; // Move the pointer to the position after the newline

        printf("msg_type: %s - body: %s\n", msg_type, body);

        if (strncmp(msg_type, "CONTROL", 7) == 0)
        {
            ControlMessage msg;
            sscanf(msg_type, "CONTROL %s", msg.type);
            strncpy(msg.body, body, sizeof(msg.body) - 1);
            printf("msg.type: %s\n", msg.type);
            handle_control_message(new_socket, &msg);
        }
        else if (strncmp(msg_type, "DATA", 4) == 0)
        {
            DataMessage msg;
            sscanf(msg_type, "DATA %s %s %d", msg.type, msg.data_type, &msg.data_size);
            strncpy(msg.body, body, sizeof(msg.body) - 1);
            handle_data_message(new_socket, &msg);
        }
        else if (strncmp(msg_type, "NOTIFICATION", 12) == 0)
        {
            NotificationMessage msg;
            sscanf(msg_type, "NOTIFICATION %s %s", msg.type, msg.timestamp);
            strncpy(msg.body, body, sizeof(msg.body) - 1);
            handle_notification_message(new_socket, &msg);
        }

        close(new_socket);
    }
}