#ifndef PRACTICE_SERVICE_H
#define PRACTICE_SERVICE_H

int submit_practice_question(int practice_question_id, int answer_id);
int submit_practice(int practice_id, int *total_questions, int *answered_questions, int *correct_answers, int *incorrect_answers);
char *user_start_practice(int room_id, int user_id, int *practice_id);
int add_question_to_practice(int practice_id);

#endif // PRACTICE_SERVICE_H