#include "room_controller.h"
#include "../../data_structures/index.h"
#include "../../services/service.h"
#include "../../utils/json_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

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

void handle_get_exam_result_of_room(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 1);

    int room_id = -1;
    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "room_id") == 0)
        {
            room_id = atoi(pairs[i].value);
        }
    }

    char *result = get_exam_result_of_room(room_id);
    char response[8192];
    memset(response, 0, sizeof(response));

    if (result == NULL)
    {
        snprintf(response, sizeof(response), "DATA JSON 0 EXAM_RESULT_OF_ROOM\n{\"data\": []}");
    }
    else
    {
        snprintf(response, sizeof(response), "DATA JSON %ld EXAM_RESULT_OF_ROOM\n{\"data\": %s}", strlen(result), result);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);

    if (result != NULL)
    {
        free(result);
    }
}

void handle_get_room_by_id(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 1);

    int room_id = -1;
    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "room_id") == 0)
        {
            room_id = atoi(pairs[i].value);
        }
    }

    char response[8192];
    memset(response, 0, sizeof(response));

    char *result = get_room_detail(room_id);
    if (result == NULL)
    {
        snprintf(response, sizeof(response), "DATA JSON 0 ROOM_DETAIL\n{}");
    }
    else
    {
        snprintf(response, sizeof(response), "DATA JSON %ld ROOM_DETAIL\n%s", strlen(result), result);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);

    if (result != NULL)
    {
        free(result);
    }
}

void handle_start_exam(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 1);

    int room_id = -1;
    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "room_id") == 0)
        {
            room_id = atoi(pairs[i].value);
        }
    }

    int result = start_exam(room_id);

    char response[1024];
    char timestamp[50];
    memset(response, 0, sizeof(response));

    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", localtime(&now));

    if (result == 0)
    {
        snprintf(response, sizeof(response), "NOTIFICATION START_EXAM_FAIL %s", timestamp);
    }
    else
    {
        snprintf(response, sizeof(response), "NOTIFICATION START_EXAM_SUCCESS %s", timestamp);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);
}
