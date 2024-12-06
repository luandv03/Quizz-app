#include "controller.h"
#include "../data_structures/index.h"
#include "../services/service.h"
#include "../utils/json_utils.h"
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

void  handle_login(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 2);

    char email[256] = "", password[256] = "";
    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "email") == 0)
        {
            strncpy(email, pairs[i].value, sizeof(email) - 1);
        }
        else if (strcmp(pairs[i].key, "password") == 0)
        {
            strncpy(password, pairs[i].value, sizeof(password) - 1);
        }
    }

    int user_id = login(email, password);
    char response[2048];
    char timestamp[50];

    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", localtime(&now));

    if (user_id != -1)
    {
        snprintf(response, sizeof(response), "NOTIFICATION LOGIN_SUCCESS%s\n{\"user_id\": %d}", timestamp, user_id);
    }
    // {\" \": \" \"}
    else
    {
        snprintf(response, sizeof(response), "NOTIFICATION LOGIN_FAILURE %s\n{\"message\": \"User not found or wrong password\"}", timestamp);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);
}

void handle_signup(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 4);

    char email[256] = "", password[256] = "", username[256] = "", dob[256] = "";
    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "email") == 0)
        {
            strncpy(email, pairs[i].value, sizeof(email) - 1);
        }
        else if (strcmp(pairs[i].key, "password") == 0)
        {
            strncpy(password, pairs[i].value, sizeof(password) - 1);
        }
        else if (strcmp(pairs[i].key, "name") == 0)
        {
            strncpy(username, pairs[i].value, sizeof(username) - 1);
        }
        else if (strcmp(pairs[i].key, "dob") == 0)
        {
            strncpy(dob, pairs[i].value, sizeof(dob) - 1);
        }
    }

    printf("email: %s, password: %s, username: %s, dob: %s\n", email, password, username, dob);

    int result = signup(email, password, username, dob);

    char response[2048];
    char timestamp[50];
    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", localtime(&now));

    if (result)
    {
        snprintf(response, sizeof(response), "NOTIFICATION SIGN_UP_SUCCESS");
    }
    else
    {
        snprintf(response, sizeof(response), "NOTIFICATION SIGN_UP_FAILURE");
    }

    write(client_socket, response, strlen(response));
    close(client_socket);
}

void handle_get_room_list(int client_socket, ControlMessage *msg)
{
    char response[8192];
    memset(response, 0, sizeof(response));

    char *result = get_all_room();
    if (result == NULL)
    {
        snprintf(response, sizeof(response), "DATA JSON 0 ALL_ROOM\n{\"data\": []}");
    }
    else
    {
        snprintf(response, sizeof(response), "DATA JSON %ld ALL_ROOM\n{\"data\": %s}", strlen(result), result);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);

    if (result != NULL)
    {
        free(result);
    }
}

void handle_user_enter_room(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 2);

    char user_id[256] = "", room_id[256] = "";
    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "user_id") == 0)
        {
            strncpy(user_id, pairs[i].value, sizeof(user_id) - 1);
        }
        else if (strcmp(pairs[i].key, "room_id") == 0)
        {
            strncpy(room_id, pairs[i].value, sizeof(room_id) - 1);
        }
    }

    int result = user_enter_room(atoi(user_id), atoi(room_id));
    char response[2048];
    char timestamp[50];
    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", localtime(&now));

    if (result == 0)
    {
        snprintf(response, sizeof(response), "NOTIFICATION USER_ENTER_ROOM_FAILURE %s\n{\"message\": \"Failed to enter room\"}", timestamp);
    }
    else
    {
        snprintf(response, sizeof(response), "NOTIFICATION USER_ENTER_ROOM_SUCCESS %s\n{\"message\": \"Success\"}", timestamp);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);
}

void handle_get_user_exam_result(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 10);

    int user_id = -1;
    int room_id = -1;
    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "user_id") == 0)
        {

            user_id = atoi(pairs[i].value);
        }
        else if (strcmp(pairs[i].key, "room_id") == 0)
        {
            room_id = atoi(pairs[i].value);
        }
    }

    char *result = get_user_exam_result(user_id, room_id);
    printf("Result: %s\n", result);
    char response[8192];
    memset(response, 0, sizeof(response));

    if (result == NULL)
    {
        snprintf(response, sizeof(response), "DATA JSON 0 USER_EXAM_RESULT\n{\"data\": []}");
    }
    else
    {
        snprintf(response, sizeof(response), "DATA JSON %ld USER_EXAM_RESULT\n{\"data\": %s}", strlen(result), result);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);

    if (result != NULL)
    {
        free(result);
    }
}

