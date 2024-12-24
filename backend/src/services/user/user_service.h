#ifndef USER_SERVICE_H
#define USER_SERVICE_H

char *get_user_exam_result(int user_id, int room_id);
char *get_user_practice_result(int room_id, int user_id);
char *get_user_profile_by_id(int user_id);
int update_user_by_id(int user_id, const char *email, const char *name, const char *dob);

#endif // USER_SERVICE_H