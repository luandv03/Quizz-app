#!/bin/bash

DB_NAME="quizz_db"
DB_USER="quizz"
DB_PASS="Quizz2003@"

# Drop the database
mysql -u$DB_USER -p$DB_PASS -e "DROP DATABASE IF EXISTS $DB_NAME;"

# Create the database
mysql -u$DB_USER -p$DB_PASS -e "CREATE DATABASE $DB_NAME;"

# Run migrations
make migrate

# Run seeds
make seed