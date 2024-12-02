#include "controller.h"
#include "../services/service.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void handle_request(int client_socket) {
    char *json_data = fetch_questions_json();
    if (json_data == NULL) {
        const char *error_message = "{\"error\": \"Failed to fetch questions\"}";
        write(client_socket, error_message, strlen(error_message));
    } else {
        write(client_socket, json_data, strlen(json_data));
        free(json_data);
    }
    close(client_socket);
}

void handle_signup(int client_socket, const char* email, const char* password, const char* username) {
    int result = signup(email, password, username);
    if (result) {
        const char *response = "{\"message\": \"Signup successful\"}";
        write(client_socket, response, strlen(response));
    } else {
        const char *response = "{\"error\": \"Signup failed\"}";
        write(client_socket, response, strlen(response));
    }
    close(client_socket);
}

void handle_signin(int client_socket, const char* email, const char* password) {
    int result = signin(email, password);
    if (result) {
        const char *response = "{\"message\": \"Signin successful\"}";
        write(client_socket, response, strlen(response));
    } else {
        const char *response = "{\"error\": \"Signin failed\"}";
        write(client_socket, response, strlen(response));
    }
    close(client_socket);
}