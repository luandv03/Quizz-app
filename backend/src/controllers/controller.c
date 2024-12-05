#include "controller.h"
#include "../message_types/index.h"
#include "../services/service.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void handle_request(int client_socket)
{
    char *json_data = fetch_questions_json();
    if (json_data == NULL)
    {
        const char *error_message = "{\"error\": \"Failed to fetch questions\"}";
        write(client_socket, error_message, strlen(error_message));
    }
    else
    {
        write(client_socket, json_data, strlen(json_data));
        free(json_data);
    }
    close(client_socket);
}

void handle_login(int client_socket, ControlMessage *msg)
{
    char email[256], password[256];
    // printf("msg->body: %s\n", msg->body);
    sscanf(msg->body, "%s %s", email, password);

    int user_id = login(email, password);
    char response[2048];
    char timestamp[50];

    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", localtime(&now));

    if (user_id != -1)
    {
        snprintf(response, sizeof(response), "NOTIFICATION LOGIN_SUCCESS%s\n%d", timestamp, user_id);
    }
    else
    {
        snprintf(response, sizeof(response), "NOTIFICATION LOGIN_FAILURE %s\nUser not found or wrong password", timestamp);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);
}

void handle_signup(int client_socket, const char *email, const char *password, const char *username)
{
    int result = signup(email, password, username);
    if (result)
    {
        const char *response = "{\"message\": \"Signup successful\"}";
        write(client_socket, response, strlen(response));
    }
    else
    {
        const char *response = "{\"error\": \"Signup failed\"}";
        write(client_socket, response, strlen(response));
    }
    close(client_socket);
}
