#ifndef ROOM_CONTROLLER_H
#define ROOM_CONTROLLER_H

#include "../../data_structures/index.h"

void handle_get_room_list(int client_socket, ControlMessage *msg);
void handle_user_enter_room(int client_socket, ControlMessage *msg);
void handle_get_exam_result_of_room(int client_socket, ControlMessage *msg);
void handle_get_room_by_id(int client_socket, ControlMessage *msg);
void handle_start_exam(int client_socket, ControlMessage *msg);
void handle_create_room(int client_socket, ControlMessage *msg);
void handle_get_room_question(int client_socket, ControlMessage *msg);
void handle_get_user_in_room(int client_socket, ControlMessage *msg);
void handle_get_user_not_in_room(int client_socket, ControlMessage *msg);

#endif // ROOM_CONTROLLER_H