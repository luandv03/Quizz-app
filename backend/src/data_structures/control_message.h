#ifndef CONTROL_MESSAGE_H
#define CONTROL_MESSAGE_H

// Control Types
#define CREATE_ROOM "CREATE_ROOM"
#define GET_ROOM_LIST "GET_ROOM_LIST"
#define LOGIN "LOGIN"
#define SIGN_UP "SIGN_UP"
#define USER_ENTER_ROOM "USER_ENTER_ROOM"
#define GET_USER_EXAM_RESULT "GET_USER_EXAM_RESULT"
// Struct Definition
typedef struct
{
    char type[50];
    char body[1024];
} ControlMessage;

#endif // CONTROL_MESSAGE_H