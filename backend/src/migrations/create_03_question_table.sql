CREATE TABLE IF NOT EXISTS question (
    id INT AUTO_INCREMENT PRIMARY KEY,
    difficulty INT NOT NULL,
    content VARCHAR(255),
    room_id INT NOT NULL,
    FOREIGN KEY (room_id) REFERENCES room(id)
);