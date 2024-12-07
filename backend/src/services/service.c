#include "service.h"
#include "../db/connect-db.h"
#include "../utils/mysql_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "../data_structures/index.h"

char *fetch_questions_json()
{
    MYSQL *conn = get_db_connection();
    if (mysql_query(conn, "SELECT * FROM questions"))
    {
        fprintf(stderr, "SELECT * FROM questions failed. Error: %s\n", mysql_error(conn));
        return NULL;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        return NULL;
    }

    int num_fields = mysql_num_fields(res);
    MYSQL_ROW row;

    cJSON *json_array = cJSON_CreateArray();

    while ((row = mysql_fetch_row(res)))
    {
        cJSON *json_row = cJSON_CreateObject();
        for (int i = 0; i < num_fields; i++)
        {
            cJSON_AddStringToObject(json_row, mysql_fetch_field_direct(res, i)->name, row[i] ? row[i] : "NULL");
        }
        cJSON_AddItemToArray(json_array, json_row);
    }

    mysql_free_result(res);

    char *json_string = cJSON_Print(json_array);
    cJSON_Delete(json_array);

    return json_string;
}

int signup(const char *email, const char *password, const char *username, const char *dob)
{
    MYSQL *conn = get_db_connection();
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO user (email, pass, name, dob) VALUES ('%s', '%s', '%s', '%s')", email, password, username, dob);
    // printf("Query: %s\n", query);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Signup failed. Error: %s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}

int login(const char *email, const char *password)
{
    int user_id;
    MYSQL *conn = get_db_connection();
    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM user WHERE email='%s' AND pass='%s'", email, password);
    // printf("Query: %s\n", query);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Login failed. Error: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        return 0;
    }

    int num_rows = mysql_num_rows(res);
    if (num_rows > 0)
    {
        MYSQL_ROW row = mysql_fetch_row(res);
        user_id = atoi(row[0]); // Assuming the first column is the user id
    }
    else
    {
        user_id = -1;
    }

    // print_mysql_result(res);
    mysql_free_result(res);

    return user_id;
}

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
    mysql_close(conn);

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

char *get_user_exam_result(int user_id, int room_id)
{
    MYSQL *conn = get_db_connection(); // Kết nối đến cơ sở dữ liệu
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return NULL;
    }
    // Truy vấn SQL lấy tất cả bài thi của người dùng trong phòng thi
    char query[512];
    snprintf(query, sizeof(query),
             "SELECT e.id AS exam_id, "
             "COUNT(DISTINCT eq.question_id) AS total_questions, "
             "COUNT(DISTINCT CASE WHEN eq.user_answer IS NOT NULL THEN eq.question_id END) AS answered_questions, "
             "COUNT(DISTINCT CASE WHEN a.is_true = 1 AND eq.user_answer = a.id THEN eq.question_id END) AS correct_answers "
             "FROM  exam e "
             " JOIN  exam_question eq ON e.id = eq.exam_id "
             "LEFT JOIN answer_of_question a ON eq.user_answer = a.id "
             "WHERE e.user_id = %d AND e.room_id = %d "
             "GROUP BY e.id "
             "ORDER BY e.id ASC; ",
             user_id, room_id);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }
    MYSQL_ROW row;
    // Kiểm tra nếu có dữ liệu trả về từ cơ sở dữ liệu
    int num_rows = mysql_num_rows(res);
    if (num_rows == 0)
    {
        fprintf(stderr, "No data found for user_id: %d in room_id: %d\n", user_id, room_id);
        mysql_free_result(res);
        mysql_close(conn);
        return NULL;
    }

    // Khởi tạo mảng JSON cho kết quả thi
    cJSON *result_json = cJSON_CreateObject();
    cJSON *exam_results = cJSON_CreateArray();
    cJSON *exam_result = cJSON_CreateObject();
    while ((row = mysql_fetch_row(res)))
    {
        if (row == NULL)
        {
            continue; // Bỏ qua nếu không có dữ liệu
        }
        cJSON_AddNumberToObject(exam_result, "exam_id", atoi(row[0]));
        cJSON_AddNumberToObject(exam_result, "score", atoi(row[3]) * 100.0 / atoi(row[2]));
        cJSON_AddNumberToObject(exam_result, "total_questions", atoi(row[1]));
        cJSON_AddNumberToObject(exam_result, "answered_questions", atoi(row[2]));
        cJSON_AddNumberToObject(exam_result, "correct_answers", atoi(row[3]));
        cJSON_AddItemToArray(exam_results, exam_result);
    }
    cJSON_AddItemToObject(result_json, "exam_results", exam_results);
    char *json_string = cJSON_Print(result_json);

    cJSON_Delete(result_json);
    mysql_free_result(res);

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
        mysql_close(conn);
        return NULL;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    MYSQL_ROW row;

    int num_rows = mysql_num_rows(res);
    if (num_rows == 0)
    {
        fprintf(stderr, "No data found for room_id: %d\n", room_id);
        mysql_free_result(res);
        mysql_close(conn);
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

char *get_user_practice_result(int room_id, int user_id)
{
    MYSQL *conn = get_db_connection(); // Kết nối đến cơ sở dữ liệu
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
        return NULL;
    }

    // Truy vấn SQL lấy tất cả bài thi của phòng thi và người thi
    char query[512];

    snprintf(query, sizeof(query),
             "SELECT u.id, u.name, r.id AS room_id, r.subject, p.start_time, p.end_time, p.score "
             "FROM practice_session p "
             "JOIN user u ON p.user_id = u.id "
             "JOIN room r ON p.room_id = r.id "
             "WHERE p.room_id = %d AND p.user_id = %d "
             "ORDER BY p.id ASC;",
             room_id, user_id);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    MYSQL_ROW row; // Dòng dữ liệu từ kết quả truy vấn
    int num_rows = mysql_num_rows(res);
    if (num_rows == 0)
    {
        fprintf(stderr, "No data found for room_id: %d and user_id: %d\n", room_id, user_id);
        mysql_free_result(res);
        mysql_close(conn);
        return NULL;
    }

    cJSON *result_json = cJSON_CreateObject();
    cJSON *practice_results = cJSON_CreateArray();

    // Lặp qua các dòng dữ liệu trong kết quả truy vấn
    while ((row = mysql_fetch_row(res)))
    {
        cJSON *practice_result = cJSON_CreateObject();

        cJSON_AddNumberToObject(practice_result, "user_id", atoi(row[0]));
        cJSON_AddStringToObject(practice_result, "username", row[1]);
        cJSON_AddNumberToObject(practice_result, "room_id", atoi(row[2]));
        cJSON_AddStringToObject(practice_result, "subject", row[3]);
        cJSON_AddStringToObject(practice_result, "start_time", row[4]);
        cJSON_AddStringToObject(practice_result, "end_time", row[5]);
        cJSON_AddNumberToObject(practice_result, "score", atoi(row[6]));

        cJSON_AddItemToArray(practice_results, practice_result);
    }

    cJSON_AddItemToObject(result_json, "practice_results", practice_results);
    char *json_string = cJSON_Print(result_json);
    cJSON_Delete(result_json);
    mysql_free_result(res);
    return json_string;
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
        mysql_close(conn);
        return strdup(error_message);
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        char error_message[256];
        snprintf(error_message, sizeof(error_message), "{\"error\": \"mysql_store_result() failed. Error: %s\"}", mysql_error(conn));
        mysql_close(conn);
        return strdup(error_message);
    }

    MYSQL_ROW row;

    int num_rows = mysql_num_rows(res);
    if (num_rows == 0)
    {
        fprintf(stderr, "No data found for room_id: %d\n", room_id);
        mysql_free_result(res);
        mysql_close(conn);
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
    mysql_close(conn);

    char *json_string = cJSON_Print(room_json);
    cJSON_Delete(room_json);

    return json_string;
}