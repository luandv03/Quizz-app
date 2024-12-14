CREATE DEFINER=`quizz`@`localhost` 
TRIGGER `update_exam_score_after_update` 
AFTER UPDATE ON `exam_question` 
FOR EACH ROW 
BEGIN
    DECLARE old_answer INT;
    DECLARE new_answer INT;
    DECLARE correct_answer INT;

    -- Lấy câu trả lời đúng
    SELECT is_true 
    INTO correct_answer
    FROM answer_of_question
    WHERE question_id = NEW.question_id;

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
END