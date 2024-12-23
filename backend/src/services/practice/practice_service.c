#include "practice_service.h"
#include "../../db/connect-db.h"
#include "../../utils/mysql_utils.h"
#include "../../utils/random_array_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "../../data_structures/index.h"

int add_question_to_practice(int practice_id)
{
    MYSQL *conn = get_db_connection();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return 0;
    }

    // Get the room_id from the practice_session table
    char query[256];
    snprintf(query, sizeof(query), "SELECT room_id FROM practice_session WHERE id = %d", practice_id);
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
    if (row == NULL)
    {
        fprintf(stderr, "No practice session found with id: %d\n", practice_id);
        mysql_free_result(res);
        return 0;
    }

    int room_id = atoi(row[0]);
    mysql_free_result(res);

    // Get the number of questions from the room table
    snprintf(query, sizeof(query), "SELECT number_of_easy_question, number_of_medium_question, number_of_hard_question FROM room WHERE id = %d", room_id);
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
    if (row == NULL)
    {
        fprintf(stderr, "No room found with id: %d\n", room_id);
        mysql_free_result(res);
        return 0;
    }

    int easyQuestions = atoi(row[0]);
    int mediumQuestions = atoi(row[1]);
    int hardQuestions = atoi(row[2]);
    mysql_free_result(res);

    // Retrieve questions from the room
    snprintf(query, sizeof(query), "SELECT id, difficulty FROM question WHERE room_id = %d", room_id);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *question_res = mysql_store_result(conn);
    if (question_res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        return 0;
    }

    int num_questions = mysql_num_rows(question_res);
    MYSQL_ROW question_row;

    int *easy_question_ids = malloc(num_questions * sizeof(int));
    int *medium_question_ids = malloc(num_questions * sizeof(int));
    int *hard_question_ids = malloc(num_questions * sizeof(int));

    int easy_count = 0, medium_count = 0, hard_count = 0;

    while ((question_row = mysql_fetch_row(question_res)))
    {
        int question_id = atoi(question_row[0]);
        int difficulty = atoi(question_row[1]);

        if (difficulty == 1)
        {
            easy_question_ids[easy_count++] = question_id;
        }
        else if (difficulty == 2)
        {
            medium_question_ids[medium_count++] = question_id;
        }
        else if (difficulty == 3)
        {
            hard_question_ids[hard_count++] = question_id;
        }
    }
    mysql_free_result(question_res);

    // Randomly select questions for the practice session
    int *random_easy_questions = getRandomSubset(easy_question_ids, easy_count, easyQuestions);
    int *random_medium_questions = getRandomSubset(medium_question_ids, medium_count, mediumQuestions);
    int *random_hard_questions = getRandomSubset(hard_question_ids, hard_count, hardQuestions);

    // Insert selected questions into practice_question table
    for (int i = 0; i < easyQuestions && i < easy_count; i++)
    {
        snprintf(query, sizeof(query), "INSERT INTO practice_question (practice_session_id, question_id) VALUES (%d, %d)", practice_id, random_easy_questions[i]);
        if (mysql_query(conn, query))
        {
            fprintf(stderr, "Query failed 1. Error: %s\n", mysql_error(conn));
            return 0;
        }
    }

    for (int i = 0; i < mediumQuestions && i < medium_count; i++)
    {
        snprintf(query, sizeof(query), "INSERT INTO practice_question (practice_session_id, question_id) VALUES (%d, %d)", practice_id, random_medium_questions[i]);
        if (mysql_query(conn, query))
        {
            fprintf(stderr, "Query failed 2. Error: %s\n", mysql_error(conn));
            return 0;
        }
    }

    for (int i = 0; i < hardQuestions && i < hard_count; i++)
    {
        snprintf(query, sizeof(query), "INSERT INTO practice_question (practice_session_id, question_id) VALUES (%d, %d)", practice_id, random_hard_questions[i]);
        if (mysql_query(conn, query))
        {
            fprintf(stderr, "Query failed 3. Error: %s\n", mysql_error(conn));
            return 0;
        }
    }

    free(random_easy_questions);
    free(random_medium_questions);
    free(random_hard_questions);
    free(easy_question_ids);
    free(medium_question_ids);
    free(hard_question_ids);

    return 1;
}

char *user_start_practice(int room_id, int user_id, int *practice_id)
{
    MYSQL *conn = get_db_connection();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return NULL;
    }

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT id FROM practice_session WHERE room_id = %d AND user_id = %d AND end_time IS NULL", room_id, user_id);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        return NULL;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        return NULL;
    }

    int num_rows = mysql_num_rows(res);
    if (num_rows == 0)
    {
        // No existing practice session, create a new one
        mysql_free_result(res);
        snprintf(query, sizeof(query),
                 "INSERT INTO practice_session (user_id, room_id, start_time) VALUES (%d, %d, NOW())", user_id, room_id);
        if (mysql_query(conn, query))
        {
            fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
            return NULL;
        }
        *practice_id = mysql_insert_id(conn);
        int added = add_question_to_practice(*practice_id);
        if (!added)
        {
            fprintf(stderr, "Failed to add questions to practice session.\n");
            return NULL;
        }
    }
    else
    {
        // Use existing practice session
        MYSQL_ROW row = mysql_fetch_row(res);
        *practice_id = atoi(row[0]);
        mysql_free_result(res);
    }

    // Get practice session details and questions
    snprintf(query, sizeof(query),
             "SELECT ps.id, ps.start_time, r.time_limit, q.id, q.content, a.id, a.content, a.is_true, pq.user_answer "
             "FROM practice_session ps "
             "JOIN room r ON ps.room_id = r.id "
             "JOIN practice_question pq ON ps.id = pq.practice_session_id "
             "JOIN question q ON pq.question_id = q.id "
             "JOIN answer_of_question a ON q.id = a.question_id "
             "WHERE ps.id = %d",
             *practice_id);
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

    cJSON *json_response = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_response, "room_id", room_id);
    cJSON_AddNumberToObject(json_response, "user_id", user_id);

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row != NULL)
    {
        cJSON_AddNumberToObject(json_response, "practice_session_id", atoi(row[0]));
        cJSON_AddStringToObject(json_response, "start_time", row[1]);
        cJSON_AddNumberToObject(json_response, "time_limit", atoi(row[2]));
    }

    cJSON *json_questions = cJSON_CreateArray();
    cJSON_AddItemToObject(json_response, "questions", json_questions);

    int current_question_id = -1;
    cJSON *current_question = NULL;

    do
    {
        int question_id = atoi(row[3]);
        if (question_id != current_question_id)
        {
            if (current_question != NULL)
            {
                cJSON_AddItemToArray(json_questions, current_question);
            }
            current_question = cJSON_CreateObject();
            cJSON_AddNumberToObject(current_question, "question_id", question_id);
            cJSON_AddStringToObject(current_question, "content", row[4]);
            cJSON *answers_array = cJSON_CreateArray();
            cJSON_AddItemToObject(current_question, "answer_of_question", answers_array);
            cJSON_AddNumberToObject(current_question, "user_answer", row[8] ? atoi(row[8]) : -1); // Add user answer
            current_question_id = question_id;
        }

        cJSON *answer = cJSON_CreateObject();
        cJSON_AddNumberToObject(answer, "answer_id", atoi(row[5]));
        cJSON_AddStringToObject(answer, "content", row[6]);
        cJSON_AddBoolToObject(answer, "is_true", atoi(row[7])); // Add is_true field
        cJSON_AddItemToArray(cJSON_GetObjectItem(current_question, "answer_of_question"), answer);
    } while ((row = mysql_fetch_row(res)));

    if (current_question != NULL)
    {
        cJSON_AddItemToArray(json_questions, current_question);
    }

    char *json_string = cJSON_Print(json_response);
    cJSON_Delete(json_response);
    mysql_free_result(res);

    return json_string;
}
int submit_practice_question(int practice_question_id, int answer_id)
{
    MYSQL *conn = get_db_connection();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query),
             "UPDATE practice_question SET user_answer = %d WHERE id = %d",
             answer_id, practice_question_id);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}
int submit_practice(int practice_id, int *total_questions, int *answered_questions, int *correct_answers, int *incorrect_answers)
{
    MYSQL *conn = get_db_connection();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return 0;
    }

    char query[256];

    // Get total number of questions
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM practice_question WHERE practice_session_id = %d", practice_id);
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
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM practice_question WHERE practice_session_id = %d AND user_answer IS NOT NULL", practice_id);
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
             "SELECT COUNT(*) FROM practice_question pq "
             "JOIN answer_of_question aoq ON pq.user_answer = aoq.id "
             "WHERE pq.practice_session_id = %d AND aoq.is_true = TRUE",
             practice_id);
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
    snprintf(query, sizeof(query), "UPDATE practice_session SET end_time = NOW() WHERE id = %d", practice_id);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}