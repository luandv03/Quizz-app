CREATE TABLE IF NOT EXISTS practice_question (
    id INT AUTO_INCREMENT PRIMARY KEY,
    practice_session_id INT NOT NULL,
    question_id INT NOT NULL,
    user_answer INT,
    FOREIGN KEY (practice_session_id) REFERENCES practice_session(id),
    FOREIGN KEY (question_id) REFERENCES question(id)
);