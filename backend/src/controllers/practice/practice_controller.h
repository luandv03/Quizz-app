#ifndef PRACTICE_CONTROLLER_H
#define PRACTICE_CONTROLLER_H

#include "../../data_structures/index.h"

void handle_user_start_practice(int client_socket, ControlMessage *msg);
void handle_submit_practice_question(int client_socket, ControlMessage *msg);
void handle_submit_practice(int client_socket, ControlMessage *msg);

#endif // PRACTICE_CONTROLLER_H