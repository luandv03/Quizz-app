#ifndef EXAM_CONTROLLER_H
#define EXAM_CONTROLLER_H

#include "../../data_structures/index.h"

void handle_submit_exam_question(int client_socket, ControlMessage *msg);
void handle_submit_exam(int client_socket, ControlMessage *msg);

#endif // EXAM_CONTROLLER_H