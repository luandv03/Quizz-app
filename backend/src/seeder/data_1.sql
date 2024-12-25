INSERT INTO user (email, pass, name, dob) VALUES
('siu@gmail.com', '1', 'Faker', '2002-01-15'),
('john.doe@example.com', '1', 'John Doe', '2002-01-15'),
('jane.smith@example.com', '1', 'Jane Smith', '2003-02-20'),
('michael.johnson@example.com', '1', 'Michael Johnson', '2004-03-25'),
('emily.davis@example.com', '1', 'Emily Davis', '2005-04-30'),
('william.brown@example.com', '1', 'William Brown', '2006-05-05'),
('olivia.jones@example.com', '1', 'Olivia Jones', '2007-06-10'),
('james.garcia@example.com', '1', 'James Garcia', '2008-07-15'),
('isabella.martinez@example.com', '1', 'Isabella Martinez', '2009-08-20'),
('benjamin.rodriguez@example.com', '1', 'Benjamin Rodriguez', '2010-09-25'),
('sophia.hernandez@example.com', '1', 'Sophia Hernandez', '2011-10-30'),
('admin@gmail.com', '1', 'Admin', '2003-08-28');

INSERT INTO room (subject, description, number_of_easy_question, number_of_medium_question, number_of_hard_question, time_limit, start, end, status) VALUES
('Math', 'Math exam for grade 10', 10, 5, 5, 60, '2023-11-01 09:00:00', '2025-11-01 10:00:00', 'Not started'),
('Science', 'Science exam for grade 10', 10, 5, 5, 60, '2023-11-02 09:00:00', '2025-11-02 10:00:00', 'Not started'),
('Geography', 'Geography exam for grade 10', 10, 5, 5, 60, '2023-11-04 09:00:00', '2025-11-04 10:00:00', 'Not started'),
('History', 'History exam for grade 10', 10, 5, 5, 60, '2023-11-03 09:00:00', '2023-11-03 10:00:00', 'Finished'),
('English', 'English exam for grade 10', 10, 5, 5, 60, '2023-11-05 09:00:00', '2023-11-05 10:00:00', 'Finished'),
('Physics', 'Physics exam for grade 10', 10, 5, 5, 60, '2023-11-06 09:00:00', '2023-11-06 10:00:00', 'Finished');

-- Insert users into user_in_room for History Room (Room ID 4)
INSERT INTO user_in_room (room_id, user_id) VALUES
(1, 1),
(2, 2),
(4, 1),
(4, 2);

-- Insert users into user_in_room for English Room (Room ID 5)
INSERT INTO user_in_room (room_id, user_id) VALUES
(5, 3),
(5, 4),
(5, 1),
(5, 2),
(5, 5),
(5, 6),
(5, 7),
(5, 8),
(5, 9),
(5, 10),
(5, 11);

-- Insert users into user_in_room for Physics Room (Room ID 6)
INSERT INTO user_in_room (room_id, user_id) VALUES
(6, 5),
(6, 6);
