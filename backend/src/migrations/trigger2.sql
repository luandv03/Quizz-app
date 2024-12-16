CREATE DEFINER=`quizz`@`localhost` 
TRIGGER `update_exam_score_after_update` 
AFTER UPDATE ON `exam_question` 
FOR EACH ROW 
BEGIN
    DECLARE old_score DECIMAL(5,2);
    DECLARE new_score DECIMAL(5,2);
    DECLARE correct_answer INT;
    DECLARE total_questions INT;

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

    -- Lấy tổng số câu hỏi
    SELECT COUNT(*)
    INTO total_questions
    FROM exam_question
    WHERE exam_id = NEW.exam_id;

    -- Kiểm tra và cập nhật điểm số
    IF OLD.user_answer = correct_answer THEN
        -- Nếu đáp án cũ đúng
        IF NEW.user_answer <> correct_answer THEN
            -- Đáp án mới sai => Trừ điểm
            UPDATE exam
            SET score = score - 100/total_questions
            WHERE id = NEW.exam_id;
        END IF;
    ELSE
        -- Nếu đáp án cũ sai
        IF NEW.user_answer = correct_answer THEN
            -- Đáp án mới đúng => Cộng điểm
            UPDATE exam
            SET score = score + 100/total_questions
            WHERE id = NEW.exam_id;
        END IF;
    END IF;
END;