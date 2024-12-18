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

    return 1;
}