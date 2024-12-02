## Backend
- Huong dan chay migrate
> gcc cli_migrate.c db/connect-db.c -o cli_migrate -lmysqlclient -I include <br>

> ./cli_migrate migrations/001_create_questions_table.sql

## Fix makefile with error missing seperate
> perl -pi -e 's/^  */\t/' Makefile
