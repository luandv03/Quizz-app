-- Insert exam results for students in History Room (Room ID 4)
INSERT INTO practice_session (user_id, room_id, start_time, end_time) VALUES
(1, 4, '2023-11-03 09:00:00', '2023-11-03 10:00:00'),
(2, 4, '2023-11-03 09:00:00', '2023-11-03 10:00:00');

-- Insert exam results for students in English Room (Room ID 5)
INSERT INTO practice_session (user_id, room_id, start_time, end_time) VALUES
(3, 5, '2023-11-05 09:00:00', '2023-11-05 10:00:00'),
(4, 5, '2023-11-05 09:00:00', '2023-11-05 10:00:00');

-- Insert exam results for students in Physics Room (Room ID 6)
INSERT INTO practice_session (user_id, room_id, start_time, end_time) VALUES
(5, 6, '2023-11-06 09:00:00', '2023-11-06 10:00:00'),
(6, 6, '2023-11-06 09:00:00', '2023-11-06 10:00:00');

-- Insert exam questions for History Room (Room ID 4)
INSERT INTO practice_question (question_id, practice_session_id, user_answer) VALUES
(91,1,362),
(92,1,366),
(93,1,370),
(94,1,374),
(95,1,378),
(96,1,382),
(97,1,386),
(98,1,390),
(99,1,394),
(100,1,398),
(101,1,402),
(102,1,406),
(103,1,410),
(104,1,414),
(105,1,418),
(106,1,422),
(107,1,426),
(108,1,430),
(109,1,434),
(110,1,438);

-- Insert exam questions for English Room (Room ID 5)
INSERT INTO practice_question (question_id, practice_session_id, user_answer) VALUES
(121,3,482),
(122,3,486),
(123,3,490),
(124,3,494),
(125,3,498),
(126,3,502),
(127,3,506),
(128,3,510),
(129,3,514),
(130,3,518),
(131,3,522),
(132,3,526),
(133,3,530),
(134,3,534),
(135,3,538),
(136,3,542),
(137,3,546),
(138,3,550),
(139,3,554),
(140,3,558);

-- Insert exam questions for Physics Room (Room ID 6)
INSERT INTO practice_question (question_id, practice_session_id, user_answer) VALUES
(151,5,602),
(152,5,606),
(153,5,610),
(154,5,614),
(155,5,618),
(156,5,622),
(157,5,626),
(158,5,630),
(159,5,634),
(160,5,638),
(161,5,642),
(162,5,646),
(163,5,650),
(164,5,654),
(165,5,658),
(166,5,662),
(167,5,666),
(168,5,670),
(169,5,674),
(170,5,678);

-- Insert exam questions for History Room (Room ID 4)
INSERT INTO practice_question (question_id, practice_session_id) VALUES
(91, 2),
(92, 2),
(93, 2),
(94, 2),
(95, 2),
(96, 2),
(97, 2),
(98, 2),
(99, 2),
(100, 2),
(101, 2),
(102, 2),
(103, 2),
(104, 2),
(105, 2),
(106, 2),
(107, 2),
(108, 2),
(109, 2),
(110, 2);

-- Insert exam questions for English Room (Room ID 5)
INSERT INTO practice_question (question_id, practice_session_id) VALUES
(121, 4),
(122, 4),
(123, 4),
(124, 4),
(125, 4),
(126, 4),
(127, 4),
(128, 4),
(129, 4),
(130, 4),
(131, 4),
(132, 4),
(133, 4),
(134, 4),
(135, 4),
(136, 4),
(137, 4),
(138, 4),
(139, 4),
(140, 4);

-- Insert exam questions for Physics Room (Room ID 6)
INSERT INTO practice_question (question_id, practice_session_id) VALUES
(151, 6),
(152, 6),
(153, 6),
(154, 6),
(155, 6),
(156, 6),
(157, 6),
(158, 6),
(159, 6),
(160, 6),
(161, 6),
(162, 6),
(163, 6),
(164, 6),
(165, 6),
(166, 6),
(167, 6),
(168, 6),
(169, 6),
(170, 6);

