#include "../data_structures/index.h"
#include "../controllers/controller.h"
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define BACKLOG 10

typedef struct pthread_arg_t {
    int new_socket_fd;
    struct sockaddr_in client_address;
    /* TODO: Put arguments passed to threads here. See lines 116 and 139. */
} pthread_arg_t;

/* Thread routine to serve connection to client. */
void *pthread_routine(void *arg);

/* Signal handler to handle SIGTERM and SIGINT signals. */
void signal_handler(int signal_number);

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
        handle_get_room_list(socket, msg);
    }
    else if (strcmp(msg->type, USER_ENTER_ROOM) == 0)
    {
        handle_user_enter_room(socket, msg);
    }
    else if (strcmp(msg->type, CREATE_ROOM) == 0)
    {
    }
    else if (strcmp(msg->type, GET_USER_EXAM_RESULT) == 0)
    {
        handle_get_user_exam_result(socket, msg);
    }
    else if (strcmp(msg->type, GET_EXAM_RESULT_OF_ROOM) == 0)
    {
        handle_get_exam_result_of_room(socket, msg);
    }
    else if (strcmp(msg->type, GET_USER_PRACTICE_RESULT) == 0)
    {
        handle_get_user_practice_result(socket, msg);
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
    int new_socket;
    pthread_attr_t pthread_attr;
    pthread_arg_t *pthread_arg;
    pthread_t pthread;
    socklen_t client_address_len;

    /* Initialise IPv4 address. */
    memset(&address, 0, sizeof address);
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

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

    /* Assign signal handlers to signals. */
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("signal");
        exit(1);
    }
    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    /* Initialise pthread attribute to create detached threads. */
    if (pthread_attr_init(&pthread_attr) != 0) {
        perror("pthread_attr_init");
        exit(1);
    }
    if (pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED) != 0) {
        perror("pthread_attr_setdetachstate");
        exit(1);
    }

    printf("Server listening on port %d\n", PORT);

    while (1)
    {
        /* Tạo tham số pthread cho mỗi kết nối đến client. */
        pthread_arg = (pthread_arg_t *)malloc(sizeof *pthread_arg);
        if (!pthread_arg) {
            perror("malloc");
            continue;
        }

        /* Chấp nhận kết nối đến client. */
        client_address_len = sizeof pthread_arg->client_address;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&pthread_arg->client_address, &client_address_len )) < 0)
        {
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        /* Khởi tạo tham số pthread. */
        pthread_arg->new_socket_fd = new_socket;

        /* Tạo luồng để phục vụ kết nối đến client. */
        if (pthread_create(&pthread, &pthread_attr, pthread_routine, (void *)pthread_arg) != 0) {
            perror("pthread_create");
            free(pthread_arg);  // Giải phóng bộ nhớ nếu không thể tạo luồng
            continue;
        }
       
        // Không đóng new_socket ở đây, để nó sẽ được đóng trong pthread_routine.
    }
}

void *pthread_routine(void *arg) {
    pthread_arg_t *pthread_arg = (pthread_arg_t *)arg;
    int new_socket_fd = pthread_arg->new_socket_fd;
    struct sockaddr_in client_address = pthread_arg->client_address;

    /* TODO: Put client interaction code here. */
    char buffer[2048];
    memset(buffer, 0, sizeof(buffer));
    read(new_socket_fd, buffer, 2048);

    printf("Received:\n%s\n", buffer);

    char *header = strtok(buffer, "\n");
    char *body = header + strlen(header) + 1; // Move the pointer to the position after the newline

    printf("header: %s - body: %s\n", header, body);

    if (strncmp(header, "CONTROL", 7) == 0)
    {
        ControlMessage msg;
        sscanf(header, "CONTROL %s", msg.type);
        strncpy(msg.body, body, sizeof(msg.body) - 1);
        printf("msg.type: %s\n", msg.type);
        handle_control_message(new_socket_fd, &msg);
    }
    else if (strncmp(header, "DATA", 4) == 0)
    {
        DataMessage msg;
        sscanf(header, "DATA %s %s %d", msg.type, msg.data_type, &msg.data_size);
        strncpy(msg.body, body, sizeof(msg.body) - 1);
        handle_data_message(new_socket_fd, &msg);
    }
    else if (strncmp(header, "NOTIFICATION", 12) == 0)
    {
        NotificationMessage msg;
        sscanf(header, "NOTIFICATION %s %s", msg.type, msg.timestamp);
        strncpy(msg.body, body, sizeof(msg.body) - 1);
        handle_notification_message(new_socket_fd, &msg);
    }

    close(new_socket_fd);

    // Giải phóng bộ nhớ khi luồng kết thúc
    free(pthread_arg);
    return NULL;
}

void signal_handler(int signal_number) {
    /* TODO: Put exit cleanup code here. */
    exit(0);
}