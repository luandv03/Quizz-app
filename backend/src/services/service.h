#ifndef SERVICE_H
#define SERVICE_H

char *fetch_questions_json();
int signup(const char *email, const char *password, const char *username, const char *dob);
int login(const char *email, const char *password);
char *get_all_room();
int user_enter_room(int user_id, int room_id);
char *get_user_exam_result(int user_id, int room_id);
char *get_exam_result_of_room(int room_id);
char *get_user_practice_result(int room_id, int user_id);

#endif // SERVICE_H