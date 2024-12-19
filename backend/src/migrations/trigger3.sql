CREATE DEFINER=`quizz`@`localhost` 
TRIGGER `update_practice_score_after_create` 
AFTER INSERT ON `practice_question` 
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

    -- Lấy tổng số câu hỏi từ bảng room
    SELECT (number_of_easy_question + number_of_medium_question + number_of_hard_question)
    INTO total_questions
    FROM room
    WHERE id = (SELECT room_id FROM practice_session WHERE id = NEW.practice_session_id);

    -- Nếu user_answer trùng với câu trả lời đúng
    IF NEW.user_answer = correct_answer THEN
        -- Cập nhật điểm số của bài thi
        UPDATE practice_session
        SET score = score + 100/total_questions
        WHERE id = NEW.practice_session_id;
    END IF;
END
