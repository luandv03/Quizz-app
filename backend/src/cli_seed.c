#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "db/connect-db.h"

void run_migration(MYSQL *conn, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Could not open file %s\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *query = malloc(length + 1);
    fread(query, 1, length, file);
    query[length] = '\0';

    char *stmt = strtok(query, ";");
    while (stmt != NULL)
    {
        // Skip empty statements
        while (*stmt == ' ' || *stmt == '\n' || *stmt == '\t')
        {
            stmt++;
        }
        if (*stmt != '\0')
        {
            if (mysql_query(conn, stmt))
            {
                fprintf(stderr, "Seed failed. Error: %s\n", mysql_error(conn));
                free(query);
                fclose(file);
                return;
            }
        }
        stmt = strtok(NULL, ";");
    }

    printf("Seed %s executed successfully.\n", filename);

    free(query);
    fclose(file);
}

void migrate(const char *migration_file)
{
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        return;
    }

    if (mysql_real_connect(conn, "localhost", "quizz", "Quizz2003@", "quizz_db", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return;
    }

    run_migration(conn, migration_file);

    mysql_close(conn);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <migration_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    migrate(argv[1]);

    return EXIT_SUCCESS;
}