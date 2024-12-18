CREATE DEFINER=`quizz`@`localhost` 
TRIGGER `update_exam_score_after_create` 
AFTER INSERT ON `exam_question` 
FOR EACH ROW 
BEGIN
    DECLARE correct_answer INT;
    DECLARE total_questions INT;

    -- Lấy ID câu trả lời đúng
    SELECT id 
    INTO correct_answer
    FROM answer_of_question
    WHERE question_id = NEW.question_id AND is_true = TRUE
    LIMIT 1;

    SELECT COUNT(*)
    INTO total_questions
    FROM exam_question
    WHERE exam_id = NEW.exam_id;

    -- Nếu user_answer trùng với câu trả lời đúng
    IF NEW.user_answer = correct_answer THEN
        -- Cập nhật điểm số của bài thi
        UPDATE exam
        SET score = score + 100/total_questions
        WHERE id = NEW.exam_id;
    END IF;
END