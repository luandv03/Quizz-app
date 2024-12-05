#ifndef SERVICE_H
#define SERVICE_H

char *fetch_questions_json();
int signup(const char *email, const char *password, const char *username, const char *dob);
int login(const char *email, const char *password);
char *get_all_room();

#endif // SERVICE_H