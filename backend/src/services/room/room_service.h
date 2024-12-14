#ifndef ROOM_SERVICE_H
#define ROOM_SERVICE_H

char *get_all_room();
int user_enter_room(int user_id, int room_id);
int start_exam(int room_id);
char *get_room_detail(int room_id);
char *get_exam_result_of_room(int room_id);

#endif // ROOM_SERVICE_H