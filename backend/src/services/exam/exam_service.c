#include "exam_service.h"
#include "../../db/connect-db.h"
#include "../../utils/mysql_utils.h"
#include "../../utils/random_array_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "../../data_structures/index.h"

int submit_exam_question(int exam_question_id, int answer_id)
{
    MYSQL *conn = get_db_connection();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query),
             "UPDATE exam_question SET user_answer = %d WHERE id = %d",
             answer_id, exam_question_id);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}

int submit_exam(int exam_id, int *total_questions, int *answered_questions, int *correct_answers, int *incorrect_answers)
{
    MYSQL *conn = get_db_connection();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return 0;
    }

    char query[256];

    // Get total number of questions
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM exam_question WHERE exam_id = %d", exam_id);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        return 0;
    }
    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        return 0;
    }
    MYSQL_ROW row = mysql_fetch_row(res);
    *total_questions = atoi(row[0]);
    mysql_free_result(res);

    // Get number of answered questions
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM exam_question WHERE exam_id = %d AND user_answer IS NOT NULL", exam_id);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        return 0;
    }
    res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        return 0;
    }
    row = mysql_fetch_row(res);
    *answered_questions = atoi(row[0]);
    mysql_free_result(res);

    // Get number of correct answers
    snprintf(query, sizeof(query),
             "SELECT COUNT(*) FROM exam_question eq "
             "JOIN answer_of_question aoq ON eq.user_answer = aoq.id "
             "WHERE eq.exam_id = %d AND aoq.is_true = TRUE",
             exam_id);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        return 0;
    }
    res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        return 0;
    }
    row = mysql_fetch_row(res);
    *correct_answers = atoi(row[0]);
    mysql_free_result(res);

    // Calculate number of incorrect answers
    *incorrect_answers = *answered_questions - *correct_answers;

    // Update end time to now
    snprintf(query, sizeof(query), "UPDATE exam SET end_time = NOW() WHERE id = %d", exam_id);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}

char *user_start_exam(int room_id, int user_id, int *exam_id)
{
    MYSQL *conn = get_db_connection();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT id FROM exam WHERE room_id = %d AND user_id = %d AND end_time IS NULL", room_id, user_id);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        return 0;
    }

    int num_rows = mysql_num_rows(res);
    if (num_rows == 0)
    {
        fprintf(stderr, "No exam found for room_id: %d and user_id: %d\n", room_id, user_id);
        mysql_free_result(res);
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    *exam_id = atoi(row[0]);
    mysql_free_result(res);

    // Get questions
    snprintf(query, sizeof(query),
             "SELECT q.id, q.content, a.id, a.content, a.is_true "
             "FROM exam_question eq "
             "JOIN question q ON eq.question_id = q.id "
             "JOIN answer_of_question a ON q.id = a.question_id "
             "WHERE eq.exam_id = %d",
             *exam_id);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        return NULL;
    }

    res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        return NULL;
    }

    cJSON *json_array = cJSON_CreateArray();
    int current_question_id = -1;
    cJSON *current_question = NULL;

    while ((row = mysql_fetch_row(res)))
    {
        int question_id = atoi(row[0]);
        if (question_id != current_question_id)
        {
            if (current_question != NULL)
            {
                cJSON_AddItemToArray(json_array, current_question);
            }
            current_question = cJSON_CreateObject();
            cJSON_AddNumberToObject(current_question, "question_id", question_id);
            cJSON_AddStringToObject(current_question, "content", row[1]);
            cJSON *answers_array = cJSON_CreateArray();
            cJSON_AddItemToObject(current_question, "answer_of_question", answers_array);
            current_question_id = question_id;
        }

        cJSON *answer = cJSON_CreateObject();
        cJSON_AddNumberToObject(answer, "answer_id", atoi(row[2]));
        cJSON_AddStringToObject(answer, "content", row[3]);
        cJSON_AddItemToArray(cJSON_GetObjectItem(current_question, "answer_of_question"), answer);
    }

    if (current_question != NULL)
    {
        cJSON_AddItemToArray(json_array, current_question);
    }

    char *json_string = cJSON_Print(json_array);
    cJSON_Delete(json_array);
    mysql_free_result(res);

    return json_string;
}