#ifndef EXAM_SERVICE_H
#define EXAM_SERVICE_H

int submit_exam_question(int exam_question_id, int answer_id);
int submit_exam(int exam_id, int *total_questions, int *answered_questions, int *correct_answers, int *incorrect_answers);

#endif // EXAM_SERVICE_H