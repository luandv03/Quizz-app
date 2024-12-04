#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../message_types/index.h"

void handle_request(int client_socket);
void handle_signup(int client_socket, const char *email, const char *password, const char *username);
void handle_login(int client_socket, ControlMessage *msg);

#endif // CONTROLLER_H