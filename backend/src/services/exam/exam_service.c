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