#ifndef CONTROL_MESSAGE_H
#define CONTROL_MESSAGE_H

// Control Types
#define CREATE_ROOM "CREATE_ROOM"
#define GET_ROOM_LIST "GET_ROOM_LIST"
#define LOGIN "LOGIN"
#define SIGN_UP "SIGN_UP"

// Struct Definition
typedef struct
{
    char control_type[50];
    char body[1024];
} ControlMessage;

#endif // CONTROL_MESSAGE_H