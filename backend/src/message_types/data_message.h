#ifndef DATA_MESSAGE_H
#define DATA_MESSAGE_H

// Data Types
#define ANSWER_SUBMISSION "ANSWER_SUBMISSION"
#define EXAM_QUESTION "EXAM_QUESTION"
#define PRACTICE_QUESTION "PRACTICE_QUESTION"

// Struct Definition
typedef struct
{
    char msg_type[50];
    char data_type[50];
    int data_size;
    char body[1024];
} DataMessage;

#endif // DATA_MESSAGE_H