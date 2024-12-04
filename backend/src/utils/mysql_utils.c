#include "mysql_utils.h"
#include <stdio.h>

void print_mysql_result(MYSQL_RES *res)
{
    if (res == NULL)
    {
        printf("No result set to print.\n");
        return;
    }

    int num_rows = mysql_num_rows(res);
    if (num_rows == 0)
    {
        printf("No query result.\n");
        return;
    }

    MYSQL_ROW row;
    MYSQL_FIELD *fields;
    unsigned int num_fields = mysql_num_fields(res);

    // Print column names
    fields = mysql_fetch_fields(res);
    for (unsigned int i = 0; i < num_fields; i++)
    {
        printf("%s\t", fields[i].name);
    }
    printf("\n");

    // Print rows
    while ((row = mysql_fetch_row(res)))
    {
        for (unsigned int i = 0; i < num_fields; i++)
        {
            printf("%s\t", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
}