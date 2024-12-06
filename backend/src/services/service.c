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

char* mysql_time_to_str(MYSQL_TIME *time) {
    char *str = (char *)malloc(20);  // Cấp phát bộ nhớ cho chuỗi ngày tháng
    snprintf(str, 20, "%04d-%02d-%02d %02d:%02d:%02d", 
             time->year, time->month, time->day, 
             time->hour, time->minute, time->second);
    return str;
}

char *get_user_exam_result(int user_id, int room_id) {
    MYSQL *conn = get_db_connection();  // Kết nối đến cơ sở dữ liệu
    if (conn == NULL) {
        fprintf(stderr, "Database connection failed.\n");
        return NULL;
    }

    // Truy vấn SQL lấy tất cả bài thi của người dùng trong phòng thi
    char query[512];
    snprintf(query, sizeof(query),
             "SELECT e.id AS exam_id, e.score, eq.question_id, eq.user_answer, a.id AS answer_id, a.content AS answer "
             "FROM exam e "
             "JOIN exam_question eq ON e.id = eq.exam_id "
             "JOIN answer_of_question a ON eq.user_answer = a.id "
             "WHERE e.user_id = %d AND e.room_id = %d "
             "ORDER BY e.id ASC;", user_id, room_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    MYSQL_ROW row;

    // Kiểm tra nếu có dữ liệu trả về từ cơ sở dữ liệu
    int num_rows = mysql_num_rows(res);
    if (num_rows == 0) {
        fprintf(stderr, "No data found for user_id: %d in room_id: %d\n", user_id, room_id);
        mysql_free_result(res);
        mysql_close(conn);
        return NULL;
    }

    // Khởi tạo mảng JSON cho kết quả thi
    cJSON *result_json = cJSON_CreateObject();
    cJSON *exam_results = cJSON_CreateArray();

    int total_questions = 0;
    int correct_answers = 0;
    int exam_id = -1;  // Khai báo exam_id ở đây

    // Lặp qua các dòng dữ liệu trong kết quả truy vấn
    cJSON *questions_json = cJSON_CreateArray();
    cJSON *exam_result = cJSON_CreateObject();
    cJSON *question_json = cJSON_CreateObject();
    while ((row = mysql_fetch_row(res))) {
        if (row == NULL) {
            continue;  // Bỏ qua nếu không có dữ liệu
        }
        //reset question_json
        question_json = cJSON_CreateObject();
        if(exam_id == -1) {
            exam_id = atoi(row[0]);
            exam_result = cJSON_CreateObject();
            questions_json = cJSON_CreateArray();
            total_questions = 0;
            correct_answers = 0;
        }else 
        if (exam_id != atoi(row[0])) {
            cJSON_AddNumberToObject(exam_result, "exam_id", exam_id);
            if(total_questions > 0) {
                cJSON_AddNumberToObject(exam_result, "score", correct_answers * 100 / total_questions);
            }
            cJSON_AddNumberToObject(exam_result, "total_questions", total_questions);
            cJSON_AddNumberToObject(exam_result, "correct_answers", correct_answers);
            cJSON_AddItemToObject(exam_result, "questions", questions_json);
            cJSON_AddItemToArray(exam_results, exam_result);
            exam_id = atoi(row[0]);
            exam_result = cJSON_CreateObject();
            questions_json = cJSON_CreateArray();
            total_questions = 0;
            correct_answers = 0;
        }
            int question_id = row[2] ? atoi(row[2]) : 0;  // Kiểm tra nếu row[2] là NULL
            int user_answer = row[3] ? atoi(row[3]) : 0;
            int answer_id = row[4] ? atoi(row[4]) : 0;
        // Tính số câu đúng
        if (user_answer == answer_id) {
            correct_answers++;
        }
        total_questions++;
        cJSON_AddNumberToObject(question_json, "question_id", question_id);
        cJSON_AddNumberToObject(question_json, "answer_id", answer_id);
        cJSON_AddNumberToObject(question_json, "user_selected", user_answer);
        cJSON_AddItemToArray(questions_json, question_json);
    }
    if(exam_id != -1) {
        cJSON_AddNumberToObject(exam_result, "exam_id", exam_id);
        if(total_questions > 0) {
            cJSON_AddNumberToObject(exam_result, "score", correct_answers * 100 / total_questions);
        }
        cJSON_AddNumberToObject(exam_result, "total_questions", total_questions);
        cJSON_AddNumberToObject(exam_result, "correct_answers", correct_answers);
        cJSON_AddItemToObject(exam_result, "questions", questions_json);
        cJSON_AddItemToArray(exam_results, exam_result);
    }
    cJSON_AddItemToObject(result_json, "exam_results", exam_results);
    char *json_string = cJSON_Print(result_json);


    cJSON_Delete(result_json);
    mysql_free_result(res);
    mysql_close(conn);

    return json_string;
}
