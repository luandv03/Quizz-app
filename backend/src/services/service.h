#ifndef SERVICE_H
#define SERVICE_H

char *fetch_questions_json();
int signup(const char *email, const char *password, const char *username);
int login(const char *email, const char *password);

#endif // SERVICE_H