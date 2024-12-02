#ifndef CONTROLLER_H
#define CONTROLLER_H

void handle_request(int client_socket);
void handle_signup(int client_socket, const char* email, const char* password, const char* username);
void handle_signin(int client_socket, const char* email, const char* password);

#endif // CONTROLLER_H