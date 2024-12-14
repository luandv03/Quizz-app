CREATE DEFINER=`quizz`@`localhost` 
TRIGGER `update_exam_score_after_create` 
AFTER INSERT ON `exam_question` 
FOR EACH ROW 
BEGIN
    DECLARE correct_answer INT;

    -- Lấy ID câu trả lời đúng
    SELECT is_true 
    INTO correct_answer
    FROM answer_of_question
    WHERE question_id = NEW.question_id;

    -- Nếu user_answer trùng với câu trả lời đúng
    IF NEW.user_answer = correct_answer THEN
        -- Cập nhật điểm số của bài thi
        UPDATE exam
        SET score = score + 1
        WHERE id = NEW.exam_id;
    END IF;
END
