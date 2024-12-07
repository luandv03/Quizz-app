#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../data_structures/index.h"

void handle_request(int client_socket);
void handle_signup(int client_socket, ControlMessage *msg);
void handle_login(int client_socket, ControlMessage *msg);
void handle_get_room_list(int client_socket, ControlMessage *msg);
void handle_user_enter_room(int client_socket, ControlMessage *msg);
void handle_get_user_exam_result(int client_socket, ControlMessage *msg);
void handle_get_exam_result_of_room(int client_socket, ControlMessage *msg);
void handle_get_user_practice_result(int client_socket, ControlMessage *msg);
void handle_get_room_by_id(int client_socket, ControlMessage *msg);

#endif // CONTROLLER_H