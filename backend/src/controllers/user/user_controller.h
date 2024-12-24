#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "../../data_structures/index.h"

void handle_get_user_exam_result(int client_socket, ControlMessage *msg);
void handle_get_user_practice_result(int client_socket, ControlMessage *msg);
void handle_get_user_profile(int client_socket, ControlMessage *msg);
void handle_update_user_by_id(int client_socket, ControlMessage *msg);

#endif // USER_CONTROLLER_H