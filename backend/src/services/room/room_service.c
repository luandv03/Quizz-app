#include "room_service.h"
#include "../../db/connect-db.h"
#include "../../utils/mysql_utils.h"
#include "../../utils/random_array_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "../../data_structures/index.h"

char *get_all_room()
{
    MYSQL *conn = get_db_connection();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return NULL;
    }

    const char *query = "SELECT r.id, r.subject, r.description, r.number_of_easy_question, r.number_of_medium_question, r.number_of_hard_question, r.time_limit, r.start, r.end, r.status, u.user_id "
                        "FROM room r LEFT JOIN user_in_room u ON r.id = u.room_id";
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
        return NULL;
    }

    MYSQL_ROW row;

    cJSON *json_array = cJSON_CreateArray();
    int current_room_id = -1;
    cJSON *current_room = NULL;
    cJSON *user_ids = NULL;

    while ((row = mysql_fetch_row(res)))
    {
        int room_id = atoi(row[0]);
        if (room_id != current_room_id)
        {
            if (current_room != NULL)
            {
                cJSON_AddItemToObject(current_room, "user_ids", user_ids);
                cJSON_AddItemToArray(json_array, current_room);
            }

            current_room_id = room_id;
            current_room = cJSON_CreateObject();
            user_ids = cJSON_CreateArray();

            cJSON_AddNumberToObject(current_room, "id", room_id);
            cJSON_AddStringToObject(current_room, "subject", row[1]);
            cJSON_AddStringToObject(current_room, "description", row[2]);
            cJSON_AddNumberToObject(current_room, "number_of_easy_question", atoi(row[3]));
            cJSON_AddNumberToObject(current_room, "number_of_medium_question", atoi(row[4]));
            cJSON_AddNumberToObject(current_room, "number_of_hard_question", atoi(row[5]));
            cJSON_AddNumberToObject(current_room, "time_limit", atoi(row[6]));
            cJSON_AddStringToObject(current_room, "start", row[7]);
            cJSON_AddStringToObject(current_room, "end", row[8]);
            cJSON_AddStringToObject(current_room, "status", row[9]);
        }

        if (row[10] != NULL)
        {
            cJSON_AddItemToArray(user_ids, cJSON_CreateNumber(atoi(row[10])));
        }
    }

    if (current_room != NULL)
    {
        cJSON_AddItemToObject(current_room, "user_ids", user_ids);
        cJSON_AddItemToArray(json_array, current_room);
    }

    mysql_free_result(res);

    char *json_string = cJSON_Print(json_array);
    cJSON_Delete(json_array);

    return json_string;
}

int user_enter_room(int user_id, int room_id)
{
    MYSQL *conn = get_db_connection();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO user_in_room (user_id, room_id) VALUES (%d, %d)", user_id, room_id);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}

char *get_room_detail(int room_id)
{
    MYSQL *conn = get_db_connection();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return strdup("{\"error\": \"Database connection failed.\"}");
    }

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT r.id, r.subject, r.description, r.number_of_easy_question, r.number_of_medium_question, r.number_of_hard_question, r.time_limit, r.start, r.end, r.status, u.user_id "
             "FROM room r LEFT JOIN user_in_room u ON r.id = u.room_id "
             "WHERE r.id = %d",
             room_id);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        char error_message[256];
        snprintf(error_message, sizeof(error_message), "{\"error\": \"Query failed. Error: %s\"}", mysql_error(conn));
        return strdup(error_message);
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        char error_message[256];
        snprintf(error_message, sizeof(error_message), "{\"error\": \"mysql_store_result() failed. Error: %s\"}", mysql_error(conn));
        return strdup(error_message);
    }

    MYSQL_ROW row;

    int num_rows = mysql_num_rows(res);
    if (num_rows == 0)
    {
        fprintf(stderr, "No data found for room_id: %d\n", room_id);
        mysql_free_result(res);
        char error_message[256];
        snprintf(error_message, sizeof(error_message), "{\"error\": \"No data found for room id: %d.\"}", room_id);
        return strdup(error_message);
    }

    cJSON *room_json = cJSON_CreateObject();
    cJSON *user_ids = cJSON_CreateArray();

    while ((row = mysql_fetch_row(res)))
    {
        if (cJSON_GetObjectItem(room_json, "id") == NULL)
        {
            cJSON_AddNumberToObject(room_json, "id", atoi(row[0]));
            cJSON_AddStringToObject(room_json, "subject", row[1]);
            cJSON_AddStringToObject(room_json, "description", row[2]);
            cJSON_AddNumberToObject(room_json, "number_of_easy_question", atoi(row[3]));
            cJSON_AddNumberToObject(room_json, "number_of_medium_question", atoi(row[4]));
            cJSON_AddNumberToObject(room_json, "number_of_hard_question", atoi(row[5]));
            cJSON_AddNumberToObject(room_json, "time_limit", atoi(row[6]));
            cJSON_AddStringToObject(room_json, "start", row[7]);
            cJSON_AddStringToObject(room_json, "end", row[8]);
            cJSON_AddStringToObject(room_json, "status", row[9]);
        }

        if (row[10] != NULL)
        {
            cJSON_AddItemToArray(user_ids, cJSON_CreateNumber(atoi(row[10])));
        }
    }

    cJSON_AddItemToObject(room_json, "user_ids", user_ids);

    mysql_free_result(res);

    char *json_string = cJSON_Print(room_json);
    cJSON_Delete(room_json);

    return json_string;
}

char *get_exam_result_of_room(int room_id)
{

    MYSQL *conn = get_db_connection(); // Kết nối đến cơ sở dữ liệu
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return NULL;
    }

    // Truy vấn SQL lấy tất cả bài thi của phòng thi
    char query[512];
    snprintf(query, sizeof(query),
             "SELECT r.id AS room_id, r.subject, u.name, e.score "
             "FROM exam e "
             "JOIN user u ON e.user_id = u.id "
             "JOIN room r ON e.room_id = r.id "
             "WHERE e.room_id = %d "
             "ORDER BY e.id ASC;",
             room_id);

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

    MYSQL_ROW row;

    int num_rows = mysql_num_rows(res);
    if (num_rows == 0)
    {
        fprintf(stderr, "No data found for room_id: %d\n", room_id);
        mysql_free_result(res);
        return NULL;
    }

    cJSON *result_json = cJSON_CreateObject();
    cJSON *exam_results = cJSON_CreateArray();

    // Lặp qua các dòng dữ liệu trong kết quả truy vấn
    while ((row = mysql_fetch_row(res)))
    {
        cJSON *exam_result = cJSON_CreateObject();
        cJSON_AddNumberToObject(exam_result, "room_id", atoi(row[0]));
        cJSON_AddStringToObject(exam_result, "subject", row[1]);
        cJSON_AddStringToObject(exam_result, "username", row[2]);
        cJSON_AddNumberToObject(exam_result, "score", atoi(row[3]));
        cJSON_AddItemToArray(exam_results, exam_result);
    }

    cJSON_AddItemToObject(result_json, "exam_results", exam_results);
    char *json_string = cJSON_Print(result_json);
    cJSON_Delete(result_json);
    mysql_free_result(res);
    return json_string;
}

int start_exam(int room_id)
{
    MYSQL *conn = get_db_connection();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return 0;
    }

    // Get the number of questions from the room table
    char query[256];
    snprintf(query, sizeof(query), "SELECT number_of_easy_question, number_of_medium_question, number_of_hard_question FROM room WHERE id = %d", room_id);
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
        fprintf(stderr, "No room found with id: %d\n", room_id);
        mysql_free_result(res);
        return 0;
    }

    int easyQuestions = atoi(row[0]);
    int mediumQuestions = atoi(row[1]);
    int hardQuestions = atoi(row[2]);
    mysql_free_result(res);

    // Room question

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

    //

    // Get all users in the room
    snprintf(query, sizeof(query), "SELECT user_id FROM user_in_room WHERE room_id = %d", room_id);
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

    while ((row = mysql_fetch_row(res)))
    {
        int user_id = atoi(row[0]);

        // Create an exam session for the user
        snprintf(query, sizeof(query), "INSERT INTO exam (user_id, room_id, start_time, end_time, score) VALUES (%d, %d, NOW(), NULL, 0)", user_id, room_id);
        if (mysql_query(conn, query))
        {
            fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
            return 0;
        }

        int exam_id = mysql_insert_id(conn);

        // printf("user_id: %d\n", user_id);
        // printf("exam_id: %d\n", exam_id);

        int *random_easy_questions = getRandomSubset(easy_question_ids, easy_count, easyQuestions);
        int *random_medium_questions = getRandomSubset(medium_question_ids, medium_count, mediumQuestions);
        int *random_hard_questions = getRandomSubset(hard_question_ids, hard_count, hardQuestions);

        // Insert selected questions into exam_question table
        for (int i = 0; i < easyQuestions && i < easy_count; i++)
        {
            snprintf(query, sizeof(query), "INSERT INTO exam_question (exam_id, question_id) VALUES (%d, %d)", exam_id, random_easy_questions[i]);
            if (mysql_query(conn, query))
            {
                fprintf(stderr, "Query failed 1. Error: %s\n", mysql_error(conn));
                return 0;
            }
        }

        for (int i = 0; i < mediumQuestions && i < medium_count; i++)
        {
            snprintf(query, sizeof(query), "INSERT INTO exam_question (exam_id, question_id) VALUES (%d, %d)", exam_id, random_medium_questions[i]);
            if (mysql_query(conn, query))
            {
                fprintf(stderr, "Query failed 2. Error: %s\n", mysql_error(conn));
                return 0;
            }
        }

        for (int i = 0; i < hardQuestions && i < hard_count; i++)
        {
            snprintf(query, sizeof(query), "INSERT INTO exam_question (exam_id, question_id) VALUES (%d, %d)", exam_id, random_hard_questions[i]);
            if (mysql_query(conn, query))
            {
                fprintf(stderr, "Query failed 3. Error: %s\n", mysql_error(conn));
                return 0;
            }
        }

        free(random_easy_questions);
        free(random_medium_questions);
        free(random_hard_questions);
    }

    free(easy_question_ids);
    free(medium_question_ids);
    free(hard_question_ids);

    mysql_free_result(res);

    // Update room status to 'Ongoing'
    snprintf(query, sizeof(query), "UPDATE room SET status = 'Ongoing' WHERE id = %d", room_id);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Failed to update room status. Error: %s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}
