#ifndef ROOM_SERVICE_H
#define ROOM_SERVICE_H

char *get_all_room();
int user_enter_room(int user_id, int room_id);
int start_exam(int room_id);
char *get_room_detail(int room_id);
char *get_user_in_room(int room_id);
char *get_user_not_in_room(int room_id);
char *get_room_question(int room_id);
char *get_exam_result_of_room(int room_id);
int create_room(const char *subject, const char *description, int number_of_easy_question, int number_of_medium_question, int number_of_hard_question, int time_limit, const char *start, const char *end);
char *get_statistic_by_room_id(int room_id);
int end_exam(int room_id);

#endif // ROOM_SERVICE_H