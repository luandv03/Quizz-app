#include "user_controller.h"
#include "../../data_structures/index.h"
#include "../../services/service.h"
#include "../../utils/json_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

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
        snprintf(response, sizeof(response), "DATA JSON USER_EXAM_RESULT\n{\"data\": []}");
    }
    else
    {
        snprintf(response, sizeof(response), "DATA JSON USER_EXAM_RESULT\n{\"data\": %s}", result);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);

    if (result != NULL)
    {
        free(result);
    }
}

void handle_get_user_practice_result(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 10);

    int room_id = -1;
    int user_id = -1;

    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "room_id") == 0)
        {
            room_id = atoi(pairs[i].value);
            // printf("room_id: %d\n", room_id);
        }
        else if (strcmp(pairs[i].key, "user_id") == 0)
        {
            user_id = atoi(pairs[i].value);
            // printf("user_id: %d\n", user_id);
        }
    }

    char *result = get_user_practice_result(user_id, room_id);
    char response[8192];
    memset(response, 0, sizeof(response));

    if (result == NULL)
    {
        snprintf(response, sizeof(response), "DATA JSON 0 USER_PRACTICE_RESULT\n{\"data\": []}");
    }
    else
    {
        snprintf(response, sizeof(response), "DATA JSON %ld USER_PRACTICE_RESULT\n{\"data\": %s}", strlen(result), result);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);

    if (result != NULL)
    {
        free(result);
    }
}

void handle_get_user_profile(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 10);

    int user_id = -1;

    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "user_id") == 0)
        {
            user_id = atoi(pairs[i].value);
        }
    }

    char *user_profile = get_user_profile_by_id(user_id);
    char response[2048];
    char timestamp[50];
    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", localtime(&now));

    if (user_profile == NULL)
    {
        snprintf(response, sizeof(response), "NOTIFICATION GET_USER_PROFILE_FAILURE %s\n{\"message\": \"Failed to get user profile\"}", timestamp);
    }
    else
    {
        snprintf(response, sizeof(response), "DATA JSON GET_PROFILE_BY_ID\n%s", user_profile);
        free(user_profile);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);
}