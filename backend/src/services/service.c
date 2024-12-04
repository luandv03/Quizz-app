#include "service.h"
#include "../db/connect-db.h"
#include "../utils/mysql_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

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

int signup(const char *email, const char *password, const char *username)
{
    MYSQL *conn = get_db_connection();
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (email, password, username) VALUES ('%s', '%s', '%s')", email, password, username);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Signup failed. Error: %s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}

int login(const char *email, const char *password)
{
    MYSQL *conn = get_db_connection();
    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM user WHERE gmail='%s' AND pass='%s'", email, password);
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

    // print_mysql_result(res);

    mysql_free_result(res);

    return num_rows > 0;
}