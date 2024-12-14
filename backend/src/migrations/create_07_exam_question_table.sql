CREATE TABLE IF NOT EXISTS exam_question (
    id INT AUTO_INCREMENT PRIMARY KEY,
    question_id INT NOT NULL,
    exam_id INT NOT NULL,
    user_answer INT,
    FOREIGN KEY (question_id) REFERENCES question(id),
    FOREIGN KEY (exam_id) REFERENCES exam(id)
);