#include "room_controller.h"
#include "../../data_structures/index.h"
#include "../../services/service.h"
#include "../../utils/json_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>

void handle_get_room_list(int client_socket, ControlMessage *msg)
{
    char response[8192];
    memset(response, 0, sizeof(response));

    char *result = get_all_room();
    if (result == NULL)
    {
        snprintf(response, sizeof(response), "DATA JSON GET_ROOM_LIST\n{\n\"data\": []\n}");
    }
    else
    {
        snprintf(response, sizeof(response), "DATA JSON GET_ROOM_LIST\n{\n\"data\": %s\n}", result);
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
    int pair_count = parse_json(msg->body, pairs, 10);

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
        snprintf(response, sizeof(response), "DATA JSON EXAM_RESULT_OF_ROOM\n{\"data\": []}");
    }
    else
    {
        snprintf(response, sizeof(response), "DATA JSON EXAM_RESULT_OF_ROOM\n{\"data\": %s}", result);
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
        snprintf(response, sizeof(response), "DATA JSON GET_ROOM_BY_ID\n{}");
    }
    else
    {
        snprintf(response, sizeof(response), "DATA JSON GET_ROOM_BY_ID\n%s", result);
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

void handle_create_room(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 10);

    char subject[256] = "", description[256] = "", start[256] = "", end[256] = "";
    int number_of_easy_question = 0, number_of_medium_question = 0, number_of_hard_question = 0, time_limit = 0;

    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "subject") == 0)
        {
            strncpy(subject, pairs[i].value, sizeof(subject) - 1);
        }
        else if (strcmp(pairs[i].key, "description") == 0)
        {
            strncpy(description, pairs[i].value, sizeof(description) - 1);
        }
        else if (strcmp(pairs[i].key, "number_of_easy_question") == 0)
        {
            number_of_easy_question = atoi(pairs[i].value);
        }
        else if (strcmp(pairs[i].key, "number_of_medium_question") == 0)
        {
            number_of_medium_question = atoi(pairs[i].value);
        }
        else if (strcmp(pairs[i].key, "number_of_hard_question") == 0)
        {
            number_of_hard_question = atoi(pairs[i].value);
        }
        else if (strcmp(pairs[i].key, "time_limit") == 0)
        {
            time_limit = atoi(pairs[i].value);
        }
        else if (strcmp(pairs[i].key, "start") == 0)
        {
            strncpy(start, pairs[i].value, sizeof(start) - 1);
        }
        else if (strcmp(pairs[i].key, "end") == 0)
        {
            strncpy(end, pairs[i].value, sizeof(end) - 1);
        }
    }

    int result = create_room(subject, description, number_of_easy_question, number_of_medium_question, number_of_hard_question, time_limit, start, end);
    char response[2048];
    char timestamp[50];
    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", localtime(&now));

    if (result == 0)
    {
        snprintf(response, sizeof(response), "NOTIFICATION ADD_ROOM_FAILURE %s\n{\"message\": \"Failed to create room\"}", timestamp);
    }
    else
    {
        snprintf(response, sizeof(response), "NOTIFICATION ADD_ROOM_SUCCESS %s\n{\"message\": \"Room created successfully\"}", timestamp);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);
}

void send_large_response(int client_socket, const char *response)
{
    size_t total_length = strlen(response);
    size_t sent = 0;
    size_t chunk_size = 1024; // Kích thước mỗi khối dữ liệu

    while (sent < total_length)
    {
        size_t to_send = chunk_size;
        if (sent + chunk_size > total_length)
        {
            to_send = total_length - sent; // Gửi phần còn lại nếu nhỏ hơn chunk_size
        }

        ssize_t written = write(client_socket, response + sent, to_send);
        if (written < 0)
        {
            perror("Error sending response");
            break;
        }

        sent += written;
    }
}

void handle_get_room_question(int client_socket, ControlMessage *msg)
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

    char *result = get_room_question(room_id);
    char *response;
    if (result == NULL)
    {
        response = strdup("DATA JSON ROOM_QUESTION\n{\n\"data\": []\n}");
    }
    else
    {
        size_t response_size = strlen(result) + 64;
        response = (char *)malloc(response_size);
        snprintf(response, response_size, "DATA JSON ROOM_QUESTION\n{\n\"data\": %s\n}", result);
    }

    ssize_t total_sent = 0;
    ssize_t len = strlen(response);
    while (total_sent < len)
    {
        ssize_t sent = write(client_socket, response + total_sent, len - total_sent);
        if (sent <= 0)
        {
            perror("write");
            break;
        }
        total_sent += sent;
    }

    shutdown(client_socket, SHUT_WR);
    close(client_socket);

    free(response);
    if (result != NULL)
    {
        free(result);
    }
}

void handle_get_user_in_room(int client_socket, ControlMessage *msg)
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

    char *result = get_user_in_room(room_id);
    if (result == NULL)
    {
        snprintf(response, sizeof(response), "DATA JSON USER_IN_ROOM\n{\n\"data\": []\n}");
    }
    else
    {
        snprintf(response, sizeof(response), "DATA JSON USER_IN_ROOM\n{\n\"data\": %s\n}", result);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);

    if (result != NULL)
    {
        free(result);
    }
}

void handle_get_user_not_in_room(int client_socket, ControlMessage *msg)
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

    char *result = get_user_not_in_room(room_id);
    if (result == NULL)
    {
        snprintf(response, sizeof(response), "DATA JSON USER_NOT_IN_ROOM\n{\n\"data\": []\n}");
    }
    else
    {
        snprintf(response, sizeof(response), "DATA JSON USER_NOT_IN_ROOM\n{\n\"data\": %s\n}", result);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);

    if (result != NULL)
    {
        free(result);
    }
}

void handle_get_statistic_by_room_id(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 10);

    int room_id = -1;
    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "room_id") == 0)
        {
            room_id = atoi(pairs[i].value);
        }
    }

    char *result = get_statistic_by_room_id(room_id);
    char response[8192];
    memset(response, 0, sizeof(response));

    if (result == NULL)
    {
        snprintf(response, sizeof(response), "DATA JSON STATISTIC_BY_ROOM_ID\n{\"data\": {}}");
    }
    else
    {
        snprintf(response, sizeof(response), "DATA JSON STATISTIC_BY_ROOM_ID\n{\"data\": %s}", result);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);

    if (result != NULL)
    {
        free(result);
    }
}

void handle_end_exam(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 10);

    int room_id = -1;
    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "room_id") == 0)
        {
            room_id = atoi(pairs[i].value);
        }
    }

    int result = end_exam(room_id);
    char response[2048];
    char timestamp[50];
    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", localtime(&now));

    if (result == 0)
    {
        snprintf(response, sizeof(response), "NOTIFICATION END_EXAM_FAILURE %s\n{\"message\": \"Failed to end exam\"}", timestamp);
    }
    else
    {
        snprintf(response, sizeof(response), "NOTIFICATION END_EXAM_SUCCESS %s\n{\"message\": \"Exam ended successfully\"}", timestamp);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);
}