INSERT INTO room (subject, description, number_of_easy_question, number_of_medium_question, number_of_hard_question, time_limit, start, end, status) VALUES
('Thực hành Lập trình mạng', 'TH LTM', 1, 1, 1, 5, '2023-11-01 09:00:00', '2026-11-01 10:00:00', 'Not started');

INSERT INTO user_in_room (user_id, room_id) VALUES
(1, 7),
(2, 7),
(3, 7),
(4, 7);

INSERT INTO question (difficulty, content, room_id) VALUES
(1, 'Easy Question 1', 7),
(2, 'Medium Question 2', 7),
(3, 'Hard Question 3', 7);

INSERT INTO answer_of_question (content, is_true, question_id) VALUES
('Answer 1', FALSE, 181),
('Answer 2', TRUE, 181),
('Answer 3', FALSE, 181),
('Answer 4', FALSE, 181),
('Answer 1', FALSE, 182),
('Answer 2', TRUE, 182),
('Answer 3', FALSE, 182),
('Answer 4', FALSE, 182),
('Answer 1', FALSE, 183),
('Answer 2', TRUE, 183),
('Answer 3', FALSE, 183),
('Answer 4', FALSE, 183);