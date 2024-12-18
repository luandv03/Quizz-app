#include "exam_controller.h"
#include "../../data_structures/index.h"
#include "../../services/service.h"
#include "../../utils/json_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void handle_submit_exam_question(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 10);

    int exam_question_id = -1, answer_id = -1;

    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "exam_question_id") == 0)
        {
            exam_question_id = atoi(pairs[i].value);
        }
        else if (strcmp(pairs[i].key, "answer_id") == 0)
        {
            answer_id = atoi(pairs[i].value);
        }
    }

    int result = submit_exam_question(exam_question_id, answer_id);
    char response[2048];
    char timestamp[50];
    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", localtime(&now));

    if (result == 0)
    {
        snprintf(response, sizeof(response), "NOTIFICATION SUBMIT_EXAM_QUESTION_FAILURE %s\n{\"message\": \"Failed to submit exam question\"}", timestamp);
    }
    else
    {
        snprintf(response, sizeof(response), "NOTIFICATION SUBMIT_EXAM_QUESTION_SUCCESS %s\n{\"message\": \"Exam question submitted successfully\"}", timestamp);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);
}

void handle_submit_exam(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 10);

    int exam_id = -1;

    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "exam_id") == 0)
        {
            exam_id = atoi(pairs[i].value);
        }
    }

    int total_questions = 0, answered_questions = 0, correct_answers = 0, incorrect_answers = 0;
    int result = submit_exam(exam_id, &total_questions, &answered_questions, &correct_answers, &incorrect_answers);
    char response[2048];
    char timestamp[50];
    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", localtime(&now));

    if (result == 0)
    {
        snprintf(response, sizeof(response), "NOTIFICATION SUBMIT_EXAM_FAILURE %s\n{\"message\": \"Failed to submit exam\"}", timestamp);
    }
    else
    {
        cJSON *json_response = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_response, "total_questions", total_questions);
        cJSON_AddNumberToObject(json_response, "answered_questions", answered_questions);
        cJSON_AddNumberToObject(json_response, "correct_answers", correct_answers);
        cJSON_AddNumberToObject(json_response, "incorrect_answers", incorrect_answers);
        char *json_string = cJSON_Print(json_response);
        snprintf(response, sizeof(response), "NOTIFICATION SUBMIT_EXAM_SUCCESS %s\n%s", timestamp, json_string);
        free(json_string);
        cJSON_Delete(json_response);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);
}

void handle_user_start_exam(int client_socket, ControlMessage *msg)
{
    KeyValuePair pairs[10];
    int pair_count = parse_json(msg->body, pairs, 10);

    int room_id = -1, user_id = -1;

    for (int i = 0; i < pair_count; i++)
    {
        if (strcmp(pairs[i].key, "room_id") == 0)
        {
            room_id = atoi(pairs[i].value);
        }
        else if (strcmp(pairs[i].key, "user_id") == 0)
        {
            user_id = atoi(pairs[i].value);
        }
    }

    int exam_id = -1;
    char *result = user_start_exam(room_id, user_id, &exam_id);
    char response[8192];
    char timestamp[50];
    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", localtime(&now));

    if (result == 0)
    {
        snprintf(response, sizeof(response), "NOTIFICATION USER_START_EXAM_FAILURE %s\n{\"message\": \"Failed to start exam\"}", timestamp);
    }
    else
    {
        size_t response_size = strlen(result) + 256;
        char *response = (char *)malloc(response_size);
        snprintf(response, sizeof(response), "DATA JSON USER_START_EXAM\n{\n\"room_id\": %d,\n\"user_id\": %d\n\"questions\": %s}", room_id, user_id, result);
        free(result);
    }

    write(client_socket, response, strlen(response));
    close(client_socket);
}