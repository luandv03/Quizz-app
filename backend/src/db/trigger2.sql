CREATE DEFINER=`quizz`@`localhost` 
TRIGGER `update_exam_score_after_update` 
AFTER UPDATE ON `exam_question` 
FOR EACH ROW 
BEGIN
    DECLARE old_score INT;
    DECLARE new_score INT;
    DECLARE correct_answer INT;

    -- Lấy câu trả lời đúng
    SELECT id 
    INTO correct_answer
    FROM answer_of_question
    WHERE question_id = NEW.question_id AND is_true = TRUE
    LIMIT 1;

    -- Lấy điểm số trước khi cập nhật
    SELECT score 
    INTO old_score
    FROM exam
    WHERE id = NEW.exam_id;

    -- Kiểm tra và cập nhật điểm số
    IF OLD.user_answer = correct_answer THEN
        -- Nếu đáp án cũ đúng
        IF NEW.user_answer <> correct_answer THEN
            -- Đáp án mới sai => Trừ điểm
            UPDATE exam
            SET score = score - 1
            WHERE id = NEW.exam_id;
        END IF;
    ELSE
        -- Nếu đáp án cũ sai
        IF NEW.user_answer = correct_answer THEN
            -- Đáp án mới đúng => Cộng điểm
            UPDATE exam
            SET score = score + 1
            WHERE id = NEW.exam_id;
        END IF;
    END IF;

    -- Lấy điểm số sau khi cập nhật
    SELECT score 
    INTO new_score
    FROM exam
    WHERE id = NEW.exam_id;

    -- Ghi log
    INSERT INTO debug_log (exam_id, old_answer, new_answer, correct_answer, old_score, new_score, message)
    VALUES (NEW.exam_id, OLD.user_answer, NEW.user_answer, correct_answer, old_score, new_score, 'Score updated in trigger');
END;
