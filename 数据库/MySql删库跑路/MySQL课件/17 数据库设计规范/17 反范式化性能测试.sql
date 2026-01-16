DROP TABLE IF EXISTS student;
-- 学生表
CREATE TABLE student(
    sid INT PRIMARY KEY AUTO_INCREMENT COMMENT '学生ID',
    sname VARCHAR(32) NOT NULL COMMENT '学生姓名',
    create_time DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT '注册时间'
);

-- 满足第三范式的评论表
CREATE TABLE course_comment(
	cid INT PRIMARY KEY AUTO_INCREMENT COMMENT '评论ID',
  course_id INT NOT NULL COMMENT '课程ID',
  content TEXT NOT NULL COMMENT '评论内容',
  create_time DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT '评论时间',
  sid INT NOT NULL COMMENT '学生ID'
);

-- 反范式化的评论表
CREATE TABLE course_comment_de(
	cid INT PRIMARY KEY AUTO_INCREMENT COMMENT '评论ID',
  course_id INT NOT NULL COMMENT '课程ID',
  content TEXT NOT NULL COMMENT '评论内容',
  create_time DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT '评论时间',
  sid INT NOT NULL COMMENT '学生ID',
  sname VARCHAR(32) NOT NULL COMMENT '学生姓名'
);

## 学生数据
CREATE PROCEDURE insert_stu_data(IN n INT)
BEGIN
  DECLARE i INT DEFAULT n;
  START TRANSACTION;
  WHILE i>0 DO
    INSERT INTO student(sname,create_time) VALUES(CONCAT('maye',RAND()*1000),NOW());
    SET i = i-1;
  END WHILE;
  COMMIT;
END;

CALL insert_stu_data(1000000);

#评论表1数据
CREATE PROCEDURE insert_comment_data(IN n INT)
BEGIN
  DECLARE i INT DEFAULT n;
  START TRANSACTION;
  WHILE i>0 DO
    INSERT INTO course_comment(course_id,content,create_time,sid) VALUES(i,CONCAT('哇！你好厉害',RAND()*1000),NOW(),rand()*1000000%1000000);
    SET i = i-1;
  END WHILE;
  COMMIT;
END;

CALL insert_comment_data(1000000);

#评论表2数据
CREATE PROCEDURE insert_comment_de_data(IN n INT)
BEGIN
  DECLARE i INT DEFAULT n;
  DECLARE _sid INT DEFAULT 0;
  DECLARE _sname VARCHAR(32);
    
  START TRANSACTION;
  
  WHILE i>0 DO
    SET _sid = rand()*1000000%1000000;
    SELECT sname INTO _sname FROM student WHERE sid = _sid;
    
    INSERT INTO course_comment_de(course_id,content,create_time,sid,sname) 
    VALUES(i,CONCAT('哇！哥哥好棒！',RAND()*1000),NOW(),_sid,_sname);
    SET i = i-1;
    
  END WHILE;
  COMMIT;
END;

CALL insert_comment_de_data(1000000);

SELECT * FROM student LIMIT 1000;
SELECT * FROM course_comment LIMIT 1000;
SELECT * FROM course_comment_de LIMIT 1000;

-- 范式化效率 0.005s
SELECT p.content, p.create_time, s.sname 
FROM course_comment AS p LEFT JOIN student AS s
ON p.sid = s.sid 
-- WHERE stu.id BETWEEN 100000 AND 200000
WHERE s.sname LIKE 'maye8%'
ORDER BY p.cid DESC
-- LIMIT 1000; 

-- 反范式化效率 0.001s
SELECT content, create_time, sname 
FROM course_comment_de
-- WHERE stu_id BETWEEN 100000 AND 200000
WHERE sname LIKE 'maye8%'
ORDER BY cid DESC
-- LIMIT 1000; 

