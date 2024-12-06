CREATE TABLE IF NOT EXISTS room (
    id INT AUTO_INCREMENT PRIMARY KEY,
    subject VARCHAR(255) NOT NULL,
    description VARCHAR(255),
    number_of_easy_question INT NOT NULL,
    number_of_medium_question INT NOT NULL,
    number_of_hard_question INT NOT NULL,
    time_limit INT NOT NULL,
    start DATETIME NOT NULL,
    end DATETIME NOT NULL
);
