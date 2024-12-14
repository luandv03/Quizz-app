#include "user_service.h"
#include "../../db/connect-db.h"
#include "../../utils/mysql_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "../../data_structures/index.h"

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
        return NULL;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        return NULL;
    }
    MYSQL_ROW row;
    // Kiểm tra nếu có dữ liệu trả về từ cơ sở dữ liệu
    int num_rows = mysql_num_rows(res);
    if (num_rows == 0)
    {
        fprintf(stderr, "No data found for user_id: %d in room_id: %d\n", user_id, room_id);
        mysql_free_result(res);
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
        return NULL;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        return NULL;
    }

    MYSQL_ROW row; // Dòng dữ liệu từ kết quả truy vấn
    int num_rows = mysql_num_rows(res);
    if (num_rows == 0)
    {
        fprintf(stderr, "No data found for room_id: %d and user_id: %d\n", room_id, user_id);
        mysql_free_result(res);
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
